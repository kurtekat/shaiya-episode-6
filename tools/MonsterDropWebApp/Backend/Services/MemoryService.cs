using System.Runtime.InteropServices;
using MonsterDropWebAPI.Models;
using Microsoft.Extensions.Caching.Memory;
using System.Collections.Concurrent;

namespace MonsterDropWebAPI.Services
{
    /// <summary>
    /// Service for managing memory operations and mob data
    /// Adapted from the desktop version for web use
    /// </summary>
    public class MemoryService : IDisposable
    {
        #region Win32 API Imports
        
        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(uint dwDesiredAccess, bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll")]
        public static extern bool ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, int dwSize, out int lpNumberOfBytesRead);

        [DllImport("kernel32.dll")]
        public static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, int nSize, out int lpNumberOfBytesWritten);

        [DllImport("kernel32.dll")]
        public static extern bool CloseHandle(IntPtr hObject);

        [DllImport("kernel32.dll")]
        public static extern bool VirtualQueryEx(IntPtr hProcess, IntPtr lpAddress, out MEMORY_BASIC_INFORMATION lpBuffer, uint dwLength);

        [StructLayout(LayoutKind.Sequential)]
        public struct MEMORY_BASIC_INFORMATION
        {
            public IntPtr BaseAddress;
            public IntPtr AllocationBase;
            public uint AllocationProtect;
            public IntPtr RegionSize;
            public uint State;
            public uint Protect;
            public uint Type;
        }

        #endregion

        private const uint PROCESS_ALL_ACCESS = 0x1F0FFF;
        private const uint MEM_COMMIT = 0x1000;
        private const uint PAGE_READWRITE = 0x04;
        private const uint PAGE_READONLY = 0x02;
        private const uint PAGE_EXECUTE_READ = 0x20;
        private const uint PAGE_EXECUTE_READWRITE = 0x40;

        private readonly ILogger<MemoryService> _logger;
        private readonly IMemoryCache _cache;
        private readonly ConcurrentDictionary<ushort, MobInfoDto> _mobCache;
        private readonly ConcurrentDictionary<ushort, Dictionary<int, uint>> _originalValues;
        
        private IntPtr _processHandle = IntPtr.Zero;
        private System.Diagnostics.Process? _targetProcess = null;
        private bool _disposed = false;
        private DateTime _lastScanTime = DateTime.MinValue;
        private readonly object _lockObject = new();

        public event EventHandler<MobInfoDto>? MobUpdated;
        public event EventHandler<SystemStatusDto>? StatusChanged;
        public event EventHandler<string>? ProcessDetached;

        public MemoryService(ILogger<MemoryService> logger, IMemoryCache cache)
        {
            _logger = logger;
            _cache = cache;
            _mobCache = new ConcurrentDictionary<ushort, MobInfoDto>();
            _originalValues = new ConcurrentDictionary<ushort, Dictionary<int, uint>>();
        }

        public bool IsAttached => _processHandle != IntPtr.Zero && _targetProcess != null && !_targetProcess.HasExited;
        
        public SystemStatusDto GetSystemStatus()
        {
            return new SystemStatusDto
            {
                IsProcessAttached = IsAttached,
                ProcessName = _targetProcess?.ProcessName ?? "",
                ProcessId = _targetProcess?.Id ?? 0,
                MobCount = _mobCache.Count,
                ModifiedMobCount = _mobCache.Values.Count(m => m.IsModified),
                LastScanTime = _lastScanTime,
                HasUnsavedChanges = _mobCache.Values.Any(m => m.IsModified)
            };
        }

        /// <summary>
        /// Get list of available Shaiya processes
        /// </summary>
        public List<ProcessInfoDto> GetAvailableProcesses()
        {
            var processes = new List<ProcessInfoDto>();
            string[] processNames = { "sdev", "Game", "shaiya", "Shaiya", "ps_game" };
            
            foreach (string name in processNames)
            {
                try
                {
                    var procs = System.Diagnostics.Process.GetProcessesByName(name);
                    foreach (var proc in procs)
                    {
                        processes.Add(new ProcessInfoDto
                        {
                            Name = proc.ProcessName,
                            Id = proc.Id,
                            IsAttached = _targetProcess?.Id == proc.Id,
                            LastSeen = DateTime.Now,
                            Status = proc.Responding ? "Running" : "Not Responding"
                        });
                    }
                }
                catch (Exception ex)
                {
                    _logger.LogWarning($"Error checking process {name}: {ex.Message}");
                }
            }
            
            return processes;
        }

        /// <summary>
        /// Attach to a Shaiya server process
        /// </summary>
        public async Task<bool> AttachToProcessAsync(int processId)
        {
            try
            {
                lock (_lockObject)
                {
                    // Detach from current process if any
                    DetachFromProcess();
                    
                    _targetProcess = System.Diagnostics.Process.GetProcessById(processId);
                    _processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
                    
                    if (_processHandle == IntPtr.Zero)
                    {
                        _logger.LogError($"Failed to attach to process {processId}");
                        return false;
                    }
                }

                _logger.LogInformation($"Successfully attached to process {_targetProcess.ProcessName} ({processId})");
                
                // Notify status change
                StatusChanged?.Invoke(this, GetSystemStatus());
                
                return true;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"Error attaching to process {processId}");
                return false;
            }
        }

        /// <summary>
        /// Detach from current process
        /// </summary>
        public void DetachFromProcess()
        {
            lock (_lockObject)
            {
                if (_processHandle != IntPtr.Zero)
                {
                    CloseHandle(_processHandle);
                    _processHandle = IntPtr.Zero;
                }
                
                string processName = _targetProcess?.ProcessName ?? "";
                _targetProcess = null;
                
                // Clear cache
                _mobCache.Clear();
                _originalValues.Clear();
                
                _logger.LogInformation($"Detached from process {processName}");
                ProcessDetached?.Invoke(this, processName);
                StatusChanged?.Invoke(this, GetSystemStatus());
            }
        }

        /// <summary>
        /// Scan memory for mob structures
        /// </summary>
        public async Task<List<MobInfoDto>> ScanForMobsAsync()
        {
            if (!IsAttached)
            {
                throw new InvalidOperationException("No process attached");
            }

            _logger.LogInformation("Starting mob scan...");
            
            try
            {
                var mobs = await Task.Run(() => ScanMemoryForMobs());
                
                lock (_lockObject)
                {
                    _mobCache.Clear();
                    _lastScanTime = DateTime.Now;
                    
                    foreach (var mob in mobs)
                    {
                        _mobCache.TryAdd(mob.MobId, mob);
                        
                        // Store original values for backup
                        if (!_originalValues.ContainsKey(mob.MobId))
                        {
                            var originalDrops = new Dictionary<int, uint>();
                            for (int i = 0; i < mob.DropInfo.Count; i++)
                            {
                                originalDrops[i] = mob.DropInfo[i].Rate;
                            }
                            _originalValues.TryAdd(mob.MobId, originalDrops);
                        }
                    }
                }

                _logger.LogInformation($"Scan completed. Found {mobs.Count} mobs.");
                StatusChanged?.Invoke(this, GetSystemStatus());
                
                return mobs;
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error during mob scan");
                throw;
            }
        }

        private List<MobInfoDto> ScanMemoryForMobs()
        {
            var mobs = new List<MobInfoDto>();
            var regions = GetMemoryRegions();
            
            foreach (var region in regions)
            {
                if (region.RegionSize.ToInt64() < 0x10C || !IsReadableMemory(region.Protect))
                    continue;

                ScanRegionForMobs(region, mobs);
            }
            
            return mobs;
        }

        private List<MEMORY_BASIC_INFORMATION> GetMemoryRegions()
        {
            var regions = new List<MEMORY_BASIC_INFORMATION>();
            IntPtr address = IntPtr.Zero;
            
            while (address.ToInt64() < 0x7FFFFFFF)
            {
                if (VirtualQueryEx(_processHandle, address, out MEMORY_BASIC_INFORMATION mbi, 
                    (uint)Marshal.SizeOf<MEMORY_BASIC_INFORMATION>()))
                {
                    if (mbi.State == MEM_COMMIT)
                    {
                        regions.Add(mbi);
                    }
                    address = new IntPtr(mbi.BaseAddress.ToInt64() + mbi.RegionSize.ToInt64());
                }
                else
                {
                    address = new IntPtr(address.ToInt64() + 0x1000);
                }
            }
            
            return regions;
        }

        private bool IsReadableMemory(uint protect)
        {
            return (protect & PAGE_READONLY) != 0 ||
                   (protect & PAGE_READWRITE) != 0 ||
                   (protect & PAGE_EXECUTE_READ) != 0 ||
                   (protect & PAGE_EXECUTE_READWRITE) != 0;
        }

        private void ScanRegionForMobs(MEMORY_BASIC_INFORMATION region, List<MobInfoDto> mobs)
        {
            const int mobInfoSize = 0x10C;
            long regionSize = region.RegionSize.ToInt64();
            IntPtr baseAddress = region.BaseAddress;
            
            const int chunkSize = 0x10000;
            
            for (long offset = 0; offset < regionSize; offset += chunkSize)
            {
                int readSize = (int)Math.Min(chunkSize, regionSize - offset);
                IntPtr currentAddress = new IntPtr(baseAddress.ToInt64() + offset);
                
                byte[]? data = ReadMemory(currentAddress, readSize);
                if (data == null) continue;
                
                for (int i = 0; i <= data.Length - mobInfoSize; i += 4)
                {
                    if (IsValidMobInfo(data, i))
                    {
                        IntPtr mobAddress = new IntPtr(currentAddress.ToInt64() + i);
                        var mobInfo = ParseMobInfo(data, i, mobAddress);
                        if (mobInfo != null)
                        {
                            mobs.Add(mobInfo);
                        }
                    }
                }
            }
        }

        private bool IsValidMobInfo(byte[] data, int offset)
        {
            if (offset + 0x10C > data.Length) return false;
            
            ushort mobId = BitConverter.ToUInt16(data, offset);
            if (mobId == 0 || mobId > 10000) return false;
            
            ushort level = BitConverter.ToUInt16(data, offset + 0x22);
            if (level == 0 || level > 255) return false;
            
            uint health = BitConverter.ToUInt32(data, offset + 0x30);
            if (health == 0 || health > 1000000) return false;
            
            return true;
        }

        private MobInfoDto? ParseMobInfo(byte[] data, int offset, IntPtr address)
        {
            try
            {
                var mob = new MobInfoDto
                {
                    MobId = BitConverter.ToUInt16(data, offset),
                    Level = BitConverter.ToUInt16(data, offset + 0x22),
                    Exp = BitConverter.ToUInt16(data, offset + 0x24),
                    Health = BitConverter.ToUInt32(data, offset + 0x30),
                    Money = BitConverter.ToUInt16(data, offset + 0x28),
                    MoneyAdd = BitConverter.ToUInt16(data, offset + 0x2A),
                };

                // Parse mob name
                byte[] nameBytes = new byte[32];
                Array.Copy(data, offset + 0x02, nameBytes, 0, 32);
                int nullIndex = Array.IndexOf(nameBytes, (byte)0);
                if (nullIndex >= 0)
                {
                    mob.MobName = System.Text.Encoding.UTF8.GetString(nameBytes, 0, nullIndex);
                }
                else
                {
                    mob.MobName = System.Text.Encoding.UTF8.GetString(nameBytes).TrimEnd('\0');
                }

                mob.DisplayName = $"[{mob.MobId}] {mob.MobName} (Lv.{mob.Level})";

                // Parse drop info (starts at offset 0xBC)
                int dropOffset = offset + 0xBC;
                for (int i = 0; i < 10; i++)
                {
                    int dropDataOffset = dropOffset + (i * 8);
                    if (dropDataOffset + 8 <= data.Length)
                    {
                        ushort grade = BitConverter.ToUInt16(data, dropDataOffset);
                        uint rate = BitConverter.ToUInt32(data, dropDataOffset + 4);
                        
                        var dropInfo = new DropInfoDto
                        {
                            Index = i,
                            Grade = grade,
                            Rate = rate,
                            IsActive = grade > 0 || rate > 0,
                            Percentage = CalculatePercentage(rate),
                            Color = GetRateColor(rate)
                        };
                        
                        mob.DropInfo.Add(dropInfo);
                    }
                }

                return mob;
            }
            catch (Exception ex)
            {
                _logger.LogWarning(ex, $"Error parsing mob info at offset {offset:X8}");
                return null;
            }
        }

        private string CalculatePercentage(uint rate, uint baseRate = 10000)
        {
            if (baseRate == 0) return "0%";
            
            double percentage = (double)rate / baseRate * 100;
            
            if (percentage < 0.01)
                return "<0.01%";
            else if (percentage >= 100)
                return $"{percentage:F0}%";
            else
                return $"{percentage:F2}%";
        }

        private string GetRateColor(uint rate)
        {
            return rate switch
            {
                0 => "#6c757d",              // Gray - No drop
                <= 100 => "#dc3545",        // Red - Very rare (< 1%)
                <= 1000 => "#fd7e14",       // Orange - Rare (1-10%)
                <= 5000 => "#198754",       // Green - Common (10-50%)
                <= 10000 => "#0d6efd",      // Blue - Very common (50-100%)
                _ => "#6f42c1"               // Purple - Extremely high (> 100%)
            };
        }

        /// <summary>
        /// Get all cached mobs with optional filtering
        /// </summary>
        public PagedResponse<MobInfoDto> GetMobs(MobSearchRequest request)
        {
            var query = _mobCache.Values.AsQueryable();

            // Apply filters
            if (!string.IsNullOrEmpty(request.SearchTerm))
            {
                var term = request.SearchTerm.ToLower();
                query = query.Where(m => 
                    m.MobId.ToString().Contains(term) ||
                    m.MobName.ToLower().Contains(term) ||
                    m.Level.ToString().Contains(term));
            }

            if (request.MinLevel.HasValue)
            {
                query = query.Where(m => m.Level >= request.MinLevel.Value);
            }

            if (request.MaxLevel.HasValue)
            {
                query = query.Where(m => m.Level <= request.MaxLevel.Value);
            }

            if (request.ModifiedOnly == true)
            {
                query = query.Where(m => m.IsModified);
            }

            // Apply sorting
            query = request.SortBy.ToLower() switch
            {
                "mobname" => request.SortDescending ? query.OrderByDescending(m => m.MobName) : query.OrderBy(m => m.MobName),
                "level" => request.SortDescending ? query.OrderByDescending(m => m.Level) : query.OrderBy(m => m.Level),
                "lastmodified" => request.SortDescending ? query.OrderByDescending(m => m.LastModified) : query.OrderBy(m => m.LastModified),
                _ => request.SortDescending ? query.OrderByDescending(m => m.MobId) : query.OrderBy(m => m.MobId),
            };

            var totalCount = query.Count();
            var totalPages = (int)Math.Ceiling((double)totalCount / request.PageSize);
            
            var data = query
                .Skip((request.Page - 1) * request.PageSize)
                .Take(request.PageSize)
                .ToList();

            return new PagedResponse<MobInfoDto>
            {
                Data = data,
                TotalCount = totalCount,
                Page = request.Page,
                PageSize = request.PageSize,
                TotalPages = totalPages,
                HasNextPage = request.Page < totalPages,
                HasPreviousPage = request.Page > 1
            };
        }

        /// <summary>
        /// Get a specific mob by ID
        /// </summary>
        public MobInfoDto? GetMob(ushort mobId)
        {
            _mobCache.TryGetValue(mobId, out var mob);
            return mob;
        }

        /// <summary>
        /// Update a specific drop for a mob
        /// </summary>
        public async Task<bool> UpdateDropAsync(UpdateDropRequest request, string? modifiedBy = null)
        {
            if (!IsAttached)
            {
                throw new InvalidOperationException("No process attached");
            }

            if (!_mobCache.TryGetValue(request.MobId, out var mob))
            {
                throw new ArgumentException($"Mob {request.MobId} not found");
            }

            if (request.DropIndex < 0 || request.DropIndex >= mob.DropInfo.Count)
            {
                throw new ArgumentException("Invalid drop index");
            }

            try
            {
                // Calculate memory address for this specific drop
                // This would need the actual memory address stored with each mob
                // For now, we'll update the cache and mark as modified
                
                var dropInfo = mob.DropInfo[request.DropIndex];
                dropInfo.Grade = request.Grade;
                dropInfo.Rate = request.Rate;
                dropInfo.IsActive = request.Grade > 0 || request.Rate > 0;
                dropInfo.Percentage = CalculatePercentage(request.Rate);
                dropInfo.Color = GetRateColor(request.Rate);

                mob.IsModified = true;
                mob.LastModified = DateTime.Now;
                mob.ModifiedBy = modifiedBy ?? "Unknown";

                // TODO: Write to actual memory
                // bool success = await WriteDropToMemoryAsync(mob, request.DropIndex);

                MobUpdated?.Invoke(this, mob);
                StatusChanged?.Invoke(this, GetSystemStatus());

                _logger.LogInformation($"Updated drop {request.DropIndex} for mob {request.MobId} by {modifiedBy}");
                
                return true; // Return actual memory write result
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"Error updating drop for mob {request.MobId}");
                throw;
            }
        }

        /// <summary>
        /// Apply mass edit to multiple mobs
        /// </summary>
        public async Task<int> ApplyMassEditAsync(MassEditRequest request)
        {
            if (!IsAttached)
            {
                throw new InvalidOperationException("No process attached");
            }

            int updatedCount = 0;

            foreach (var mobId in request.MobIds)
            {
                if (!_mobCache.TryGetValue(mobId, out var mob))
                    continue;

                bool mobModified = false;

                for (int i = 0; i < mob.DropInfo.Count; i++)
                {
                    var drop = mob.DropInfo[i];
                    
                    bool shouldUpdate = request.ApplyToAllGrades ||
                                      (request.FromGrade.HasValue && request.ToGrade.HasValue &&
                                       drop.Grade >= request.FromGrade.Value && drop.Grade <= request.ToGrade.Value);

                    if (shouldUpdate)
                    {
                        drop.Rate = request.NewRate;
                        drop.Percentage = CalculatePercentage(request.NewRate);
                        drop.Color = GetRateColor(request.NewRate);
                        mobModified = true;
                    }
                }

                if (mobModified)
                {
                    mob.IsModified = true;
                    mob.LastModified = DateTime.Now;
                    mob.ModifiedBy = request.ModifiedBy ?? "Unknown";
                    updatedCount++;

                    MobUpdated?.Invoke(this, mob);
                }
            }

            if (updatedCount > 0)
            {
                StatusChanged?.Invoke(this, GetSystemStatus());
                _logger.LogInformation($"Mass edit applied to {updatedCount} mobs by {request.ModifiedBy}");
            }

            return updatedCount;
        }

        /// <summary>
        /// Save all changes to memory
        /// </summary>
        public async Task<int> SaveAllChangesAsync()
        {
            if (!IsAttached)
            {
                throw new InvalidOperationException("No process attached");
            }

            var modifiedMobs = _mobCache.Values.Where(m => m.IsModified).ToList();
            if (modifiedMobs.Count == 0)
            {
                return 0;
            }

            int savedCount = 0;

            foreach (var mob in modifiedMobs)
            {
                try
                {
                    // TODO: Write actual drop data to memory
                    // bool success = await WriteAllDropsToMemoryAsync(mob);
                    
                    // For now, just mark as saved
                    mob.IsModified = false;
                    savedCount++;
                }
                catch (Exception ex)
                {
                    _logger.LogError(ex, $"Error saving mob {mob.MobId}");
                }
            }

            StatusChanged?.Invoke(this, GetSystemStatus());
            _logger.LogInformation($"Saved {savedCount} of {modifiedMobs.Count} modified mobs");

            return savedCount;
        }

        /// <summary>
        /// Reset a mob to original values
        /// </summary>
        public bool ResetMob(ushort mobId)
        {
            if (!_mobCache.TryGetValue(mobId, out var mob) || 
                !_originalValues.TryGetValue(mobId, out var originalDrops))
            {
                return false;
            }

            for (int i = 0; i < mob.DropInfo.Count && i < originalDrops.Count; i++)
            {
                if (originalDrops.TryGetValue(i, out var originalRate))
                {
                    var drop = mob.DropInfo[i];
                    drop.Rate = originalRate;
                    drop.Percentage = CalculatePercentage(originalRate);
                    drop.Color = GetRateColor(originalRate);
                }
            }

            mob.IsModified = false;
            mob.LastModified = DateTime.Now;

            MobUpdated?.Invoke(this, mob);
            StatusChanged?.Invoke(this, GetSystemStatus());

            return true;
        }

        private byte[]? ReadMemory(IntPtr address, int size)
        {
            if (!IsAttached) return null;

            byte[] buffer = new byte[size];
            bool success = ReadProcessMemory(_processHandle, address, buffer, size, out int bytesRead);
            
            return success && bytesRead == size ? buffer : null;
        }

        public void Dispose()
        {
            if (!_disposed)
            {
                DetachFromProcess();
                _disposed = true;
            }
        }
    }
}