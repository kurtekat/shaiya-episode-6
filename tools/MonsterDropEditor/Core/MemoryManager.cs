using System.Diagnostics;
using System.Runtime.InteropServices;
using MonsterDropEditor.Models;

namespace MonsterDropEditor.Core
{
    /// <summary>
    /// Handles memory operations for the Shaiya server process
    /// </summary>
    public class MemoryManager : IDisposable
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

        private IntPtr processHandle = IntPtr.Zero;
        private Process? targetProcess = null;
        private bool disposed = false;

        public bool IsAttached => processHandle != IntPtr.Zero && targetProcess != null && !targetProcess.HasExited;

        /// <summary>
        /// Attach to the Shaiya server process
        /// </summary>
        /// <param name="processName">Name of the process (e.g., "sdev", "Game")</param>
        /// <returns>True if successfully attached</returns>
        public bool AttachToProcess(string processName)
        {
            try
            {
                Process[] processes = Process.GetProcessesByName(processName);
                if (processes.Length == 0)
                {
                    return false;
                }

                targetProcess = processes[0]; // Take the first one found
                processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, targetProcess.Id);
                
                return processHandle != IntPtr.Zero;
            }
            catch (Exception)
            {
                return false;
            }
        }

        /// <summary>
        /// Get list of available Shaiya processes
        /// </summary>
        /// <returns>List of process names and IDs</returns>
        public List<(string Name, int Id)> GetShaiyaProcesses()
        {
            var processes = new List<(string, int)>();
            
            // Common Shaiya process names
            string[] processNames = { "sdev", "Game", "shaiya", "Shaiya", "ps_game" };
            
            foreach (string name in processNames)
            {
                try
                {
                    Process[] procs = Process.GetProcessesByName(name);
                    foreach (var proc in procs)
                    {
                        processes.Add((proc.ProcessName, proc.Id));
                    }
                }
                catch { /* Ignore access denied */ }
            }
            
            return processes;
        }

        /// <summary>
        /// Read memory from the target process
        /// </summary>
        /// <param name="address">Memory address to read from</param>
        /// <param name="size">Number of bytes to read</param>
        /// <returns>Byte array of read data, null if failed</returns>
        public byte[]? ReadMemory(IntPtr address, int size)
        {
            if (!IsAttached) return null;

            byte[] buffer = new byte[size];
            bool success = ReadProcessMemory(processHandle, address, buffer, size, out int bytesRead);
            
            return success && bytesRead == size ? buffer : null;
        }

        /// <summary>
        /// Write memory to the target process
        /// </summary>
        /// <param name="address">Memory address to write to</param>
        /// <param name="data">Data to write</param>
        /// <returns>True if successful</returns>
        public bool WriteMemory(IntPtr address, byte[] data)
        {
            if (!IsAttached) return false;

            return WriteProcessMemory(processHandle, address, data, data.Length, out int bytesWritten) 
                   && bytesWritten == data.Length;
        }

        /// <summary>
        /// Read a structure from memory
        /// </summary>
        /// <typeparam name="T">Structure type</typeparam>
        /// <param name="address">Memory address</param>
        /// <returns>Structure instance, null if failed</returns>
        public T? ReadStructure<T>(IntPtr address) where T : struct
        {
            int size = Marshal.SizeOf<T>();
            byte[]? data = ReadMemory(address, size);
            
            if (data == null) return null;

            GCHandle handle = GCHandle.Alloc(data, GCHandleType.Pinned);
            try
            {
                return Marshal.PtrToStructure<T>(handle.AddrOfPinnedObject());
            }
            finally
            {
                handle.Free();
            }
        }

        /// <summary>
        /// Write a structure to memory
        /// </summary>
        /// <typeparam name="T">Structure type</typeparam>
        /// <param name="address">Memory address</param>
        /// <param name="structure">Structure to write</param>
        /// <returns>True if successful</returns>
        public bool WriteStructure<T>(IntPtr address, T structure) where T : struct
        {
            int size = Marshal.SizeOf<T>();
            byte[] data = new byte[size];
            
            GCHandle handle = GCHandle.Alloc(data, GCHandleType.Pinned);
            try
            {
                Marshal.StructureToPtr(structure, handle.AddrOfPinnedObject(), false);
                return WriteMemory(address, data);
            }
            finally
            {
                handle.Free();
            }
        }

        /// <summary>
        /// Scan memory for MobInfo structures
        /// </summary>
        /// <returns>List of found mob entries</returns>
        public List<MobEntry> ScanForMobs()
        {
            var mobs = new List<MobEntry>();
            
            if (!IsAttached) return mobs;

            try
            {
                // Get memory regions
                var regions = GetMemoryRegions();
                
                foreach (var region in regions)
                {
                    // Skip if region is too small or not readable
                    if (region.RegionSize.ToInt64() < Marshal.SizeOf<MobInfo>() ||
                        !IsReadableMemory(region.Protect))
                        continue;

                    // Scan this region for MobInfo structures
                    ScanRegionForMobs(region, mobs);
                }
            }
            catch (Exception ex)
            {
                // Log error if needed
                System.Diagnostics.Debug.WriteLine($"Error scanning for mobs: {ex.Message}");
            }

            return mobs;
        }

        private List<MEMORY_BASIC_INFORMATION> GetMemoryRegions()
        {
            var regions = new List<MEMORY_BASIC_INFORMATION>();
            IntPtr address = IntPtr.Zero;
            
            while (address.ToInt64() < 0x7FFFFFFF) // Stay within user space
            {
                if (VirtualQueryEx(processHandle, address, out MEMORY_BASIC_INFORMATION mbi, 
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
                    address = new IntPtr(address.ToInt64() + 0x1000); // Move to next page
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

        private void ScanRegionForMobs(MEMORY_BASIC_INFORMATION region, List<MobEntry> mobs)
        {
            const int mobInfoSize = 0x10C; // Size of MobInfo structure
            long regionSize = region.RegionSize.ToInt64();
            IntPtr baseAddress = region.BaseAddress;
            
            // Read the entire region in chunks
            const int chunkSize = 0x10000; // 64KB chunks
            
            for (long offset = 0; offset < regionSize; offset += chunkSize)
            {
                int readSize = (int)Math.Min(chunkSize, regionSize - offset);
                IntPtr currentAddress = new IntPtr(baseAddress.ToInt64() + offset);
                
                byte[]? data = ReadMemory(currentAddress, readSize);
                if (data == null) continue;
                
                // Scan for potential MobInfo structures
                for (int i = 0; i <= data.Length - mobInfoSize; i += 4) // Align to 4-byte boundary
                {
                    if (IsValidMobInfo(data, i))
                    {
                        IntPtr mobAddress = new IntPtr(currentAddress.ToInt64() + i);
                        MobInfo? mobInfo = ReadStructure<MobInfo>(mobAddress);
                        
                        if (mobInfo.HasValue)
                        {
                            mobs.Add(new MobEntry(mobAddress, mobInfo.Value));
                        }
                    }
                }
            }
        }

        private bool IsValidMobInfo(byte[] data, int offset)
        {
            if (offset + 0x10C > data.Length) return false;
            
            // Check MobId (should be reasonable range)
            ushort mobId = BitConverter.ToUInt16(data, offset);
            if (mobId == 0 || mobId > 10000) return false;
            
            // Check Level (should be 1-255)
            ushort level = BitConverter.ToUInt16(data, offset + 0x22);
            if (level == 0 || level > 255) return false;
            
            // Check Health (should be reasonable)
            uint health = BitConverter.ToUInt32(data, offset + 0x30);
            if (health == 0 || health > 1000000) return false;
            
            return true;
        }

        public void Dispose()
        {
            if (!disposed)
            {
                if (processHandle != IntPtr.Zero)
                {
                    CloseHandle(processHandle);
                    processHandle = IntPtr.Zero;
                }
                targetProcess = null;
                disposed = true;
            }
        }
    }
}