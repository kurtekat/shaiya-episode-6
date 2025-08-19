using Microsoft.AspNetCore.Mvc;
using MonsterDropWebAPI.Models;
using MonsterDropWebAPI.Services;
using MonsterDropWebAPI.Hubs;

namespace MonsterDropWebAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class SystemController : ControllerBase
    {
        private readonly MemoryService _memoryService;
        private readonly NotificationService _notificationService;
        private readonly ILogger<SystemController> _logger;

        public SystemController(
            MemoryService memoryService,
            NotificationService notificationService,
            ILogger<SystemController> logger)
        {
            _memoryService = memoryService;
            _notificationService = notificationService;
            _logger = logger;
        }

        /// <summary>
        /// Get current system status
        /// </summary>
        [HttpGet("status")]
        public ActionResult<ApiResponse<SystemStatusDto>> GetStatus()
        {
            try
            {
                var status = _memoryService.GetSystemStatus();
                
                return Ok(new ApiResponse<SystemStatusDto>
                {
                    Success = true,
                    Data = status,
                    Message = "System status retrieved successfully"
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error retrieving system status");
                return BadRequest(new ApiResponse<SystemStatusDto>
                {
                    Success = false,
                    Message = "Error retrieving system status",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Get list of available Shaiya processes
        /// </summary>
        [HttpGet("processes")]
        public ActionResult<ApiResponse<List<ProcessInfoDto>>> GetProcesses()
        {
            try
            {
                var processes = _memoryService.GetAvailableProcesses();
                
                return Ok(new ApiResponse<List<ProcessInfoDto>>
                {
                    Success = true,
                    Data = processes,
                    Message = $"Found {processes.Count} Shaiya process(es)"
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error retrieving processes");
                return BadRequest(new ApiResponse<List<ProcessInfoDto>>
                {
                    Success = false,
                    Message = "Error retrieving processes",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Attach to a specific process
        /// </summary>
        [HttpPost("attach/{processId}")]
        public async Task<ActionResult<ApiResponse<SystemStatusDto>>> AttachToProcess(int processId)
        {
            try
            {
                bool success = await _memoryService.AttachToProcessAsync(processId);
                
                if (success)
                {
                    var status = _memoryService.GetSystemStatus();
                    
                    await _notificationService.SendSuccessAsync(
                        "Process Attached", 
                        $"Successfully attached to {status.ProcessName} (PID: {status.ProcessId})");

                    return Ok(new ApiResponse<SystemStatusDto>
                    {
                        Success = true,
                        Data = status,
                        Message = $"Successfully attached to process {processId}"
                    });
                }

                return BadRequest(new ApiResponse<SystemStatusDto>
                {
                    Success = false,
                    Message = $"Failed to attach to process {processId}"
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"Error attaching to process {processId}");
                
                await _notificationService.SendErrorAsync(
                    "Attach Failed", 
                    $"Failed to attach to process {processId}: {ex.Message}");

                return BadRequest(new ApiResponse<SystemStatusDto>
                {
                    Success = false,
                    Message = "Error attaching to process",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Detach from current process
        /// </summary>
        [HttpPost("detach")]
        public async Task<ActionResult<ApiResponse<SystemStatusDto>>> DetachFromProcess()
        {
            try
            {
                var currentStatus = _memoryService.GetSystemStatus();
                string processName = currentStatus.ProcessName;
                
                _memoryService.DetachFromProcess();
                
                await _notificationService.SendInfoAsync(
                    "Process Detached", 
                    $"Detached from {processName}");

                var newStatus = _memoryService.GetSystemStatus();
                
                return Ok(new ApiResponse<SystemStatusDto>
                {
                    Success = true,
                    Data = newStatus,
                    Message = $"Successfully detached from {processName}"
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error detaching from process");
                return BadRequest(new ApiResponse<SystemStatusDto>
                {
                    Success = false,
                    Message = "Error detaching from process",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Scan for mobs in memory
        /// </summary>
        [HttpPost("scan")]
        public async Task<ActionResult<ApiResponse<List<MobInfoDto>>>> ScanForMobs()
        {
            try
            {
                if (!_memoryService.IsAttached)
                {
                    return BadRequest(new ApiResponse<List<MobInfoDto>>
                    {
                        Success = false,
                        Message = "No process attached. Please attach to a Shaiya process first."
                    });
                }

                await _notificationService.SendInfoAsync(
                    "Scan Started", 
                    "Scanning memory for mob structures... This may take a few moments.");

                var mobs = await _memoryService.ScanForMobsAsync();

                await _notificationService.SendSuccessAsync(
                    "Scan Complete", 
                    $"Found {mobs.Count} mobs in memory");

                return Ok(new ApiResponse<List<MobInfoDto>>
                {
                    Success = true,
                    Data = mobs,
                    Message = $"Scan completed. Found {mobs.Count} mobs."
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error scanning for mobs");
                
                await _notificationService.SendErrorAsync(
                    "Scan Failed", 
                    $"Memory scan failed: {ex.Message}");

                return BadRequest(new ApiResponse<List<MobInfoDto>>
                {
                    Success = false,
                    Message = "Error scanning for mobs",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Save all changes to memory
        /// </summary>
        [HttpPost("save")]
        public async Task<ActionResult<ApiResponse<int>>> SaveChanges()
        {
            try
            {
                if (!_memoryService.IsAttached)
                {
                    return BadRequest(new ApiResponse<int>
                    {
                        Success = false,
                        Message = "No process attached. Cannot save changes."
                    });
                }

                int savedCount = await _memoryService.SaveAllChangesAsync();

                if (savedCount > 0)
                {
                    await _notificationService.SendSuccessAsync(
                        "Changes Saved", 
                        $"Successfully saved {savedCount} modified mobs to memory");
                }
                else
                {
                    await _notificationService.SendInfoAsync(
                        "No Changes", 
                        "No changes to save");
                }

                return Ok(new ApiResponse<int>
                {
                    Success = true,
                    Data = savedCount,
                    Message = savedCount > 0 ? $"Saved {savedCount} changes" : "No changes to save"
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error saving changes");
                
                await _notificationService.SendErrorAsync(
                    "Save Failed", 
                    $"Failed to save changes: {ex.Message}");

                return BadRequest(new ApiResponse<int>
                {
                    Success = false,
                    Message = "Error saving changes",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Export mob data
        /// </summary>
        [HttpPost("export")]
        public async Task<ActionResult> ExportData([FromBody] ExportRequest request)
        {
            try
            {
                // Get mobs to export
                var mobRequest = new MobSearchRequest { PageSize = int.MaxValue };
                var allMobs = _memoryService.GetMobs(mobRequest);
                
                var mobsToExport = request.ExportAll ? 
                    allMobs.Data : 
                    allMobs.Data.Where(m => request.MobIds?.Contains(m.MobId) == true).ToList();

                if (mobsToExport.Count == 0)
                {
                    return BadRequest(new ApiResponse<object>
                    {
                        Success = false,
                        Message = "No mobs selected for export"
                    });
                }

                // Generate export data based on format
                string exportData;
                string contentType;
                string fileName;

                switch (request.Format.ToLower())
                {
                    case "json":
                        exportData = System.Text.Json.JsonSerializer.Serialize(mobsToExport, new System.Text.Json.JsonSerializerOptions 
                        { 
                            WriteIndented = true 
                        });
                        contentType = "application/json";
                        fileName = $"monster_drops_{DateTime.Now:yyyyMMdd_HHmmss}.json";
                        break;

                    case "csv":
                        exportData = GenerateCsvData(mobsToExport);
                        contentType = "text/csv";
                        fileName = $"monster_drops_{DateTime.Now:yyyyMMdd_HHmmss}.csv";
                        break;

                    default:
                        return BadRequest(new ApiResponse<object>
                        {
                            Success = false,
                            Message = "Unsupported export format. Use 'json' or 'csv'."
                        });
                }

                await _notificationService.SendSuccessAsync(
                    "Export Complete", 
                    $"Exported {mobsToExport.Count} mobs in {request.Format.ToUpper()} format");

                return File(System.Text.Encoding.UTF8.GetBytes(exportData), contentType, fileName);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error exporting data");
                
                await _notificationService.SendErrorAsync(
                    "Export Failed", 
                    $"Failed to export data: {ex.Message}");

                return BadRequest(new ApiResponse<object>
                {
                    Success = false,
                    Message = "Error exporting data",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Health check endpoint
        /// </summary>
        [HttpGet("health")]
        public ActionResult<ApiResponse<object>> HealthCheck()
        {
            return Ok(new ApiResponse<object>
            {
                Success = true,
                Data = new 
                { 
                    Status = "Healthy",
                    Timestamp = DateTime.UtcNow,
                    Version = "1.0.0",
                    ProcessAttached = _memoryService.IsAttached
                },
                Message = "Service is healthy"
            });
        }

        private string GenerateCsvData(List<MobInfoDto> mobs)
        {
            var csv = new System.Text.StringBuilder();
            
            // Header
            csv.AppendLine("MobId,MobName,Level,Health,Drop0_Grade,Drop0_Rate,Drop1_Grade,Drop1_Rate,Drop2_Grade,Drop2_Rate,Drop3_Grade,Drop3_Rate,Drop4_Grade,Drop4_Rate,Drop5_Grade,Drop5_Rate,Drop6_Grade,Drop6_Rate,Drop7_Grade,Drop7_Rate,Drop8_Grade,Drop8_Rate,Drop9_Grade,Drop9_Rate,IsModified,LastModified");
            
            // Data rows
            foreach (var mob in mobs)
            {
                csv.Append($"{mob.MobId},\"{mob.MobName}\",{mob.Level},{mob.Health}");
                
                for (int i = 0; i < 10; i++)
                {
                    if (i < mob.DropInfo.Count)
                    {
                        csv.Append($",{mob.DropInfo[i].Grade},{mob.DropInfo[i].Rate}");
                    }
                    else
                    {
                        csv.Append(",0,0");
                    }
                }
                
                csv.AppendLine($",{mob.IsModified},{mob.LastModified:yyyy-MM-dd HH:mm:ss}");
            }
            
            return csv.ToString();
        }
    }
}