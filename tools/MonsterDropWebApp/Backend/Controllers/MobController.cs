using Microsoft.AspNetCore.Mvc;
using MonsterDropWebAPI.Models;
using MonsterDropWebAPI.Services;
using MonsterDropWebAPI.Hubs;

namespace MonsterDropWebAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class MobController : ControllerBase
    {
        private readonly MemoryService _memoryService;
        private readonly NotificationService _notificationService;
        private readonly ILogger<MobController> _logger;

        public MobController(
            MemoryService memoryService, 
            NotificationService notificationService,
            ILogger<MobController> logger)
        {
            _memoryService = memoryService;
            _notificationService = notificationService;
            _logger = logger;
        }

        /// <summary>
        /// Get all mobs with optional filtering and pagination
        /// </summary>
        [HttpGet]
        public ActionResult<ApiResponse<PagedResponse<MobInfoDto>>> GetMobs([FromQuery] MobSearchRequest request)
        {
            try
            {
                var result = _memoryService.GetMobs(request);
                
                return Ok(new ApiResponse<PagedResponse<MobInfoDto>>
                {
                    Success = true,
                    Data = result,
                    Message = $"Retrieved {result.Data.Count} mobs (Page {result.Page} of {result.TotalPages})"
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error retrieving mobs");
                return BadRequest(new ApiResponse<PagedResponse<MobInfoDto>>
                {
                    Success = false,
                    Message = "Error retrieving mobs",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Get a specific mob by ID
        /// </summary>
        [HttpGet("{mobId}")]
        public ActionResult<ApiResponse<MobInfoDto>> GetMob(ushort mobId)
        {
            try
            {
                var mob = _memoryService.GetMob(mobId);
                
                if (mob == null)
                {
                    return NotFound(new ApiResponse<MobInfoDto>
                    {
                        Success = false,
                        Message = $"Mob {mobId} not found"
                    });
                }

                return Ok(new ApiResponse<MobInfoDto>
                {
                    Success = true,
                    Data = mob,
                    Message = "Mob retrieved successfully"
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"Error retrieving mob {mobId}");
                return BadRequest(new ApiResponse<MobInfoDto>
                {
                    Success = false,
                    Message = "Error retrieving mob",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Update a specific drop for a mob
        /// </summary>
        [HttpPut("{mobId}/drops/{dropIndex}")]
        public async Task<ActionResult<ApiResponse<MobInfoDto>>> UpdateDrop(
            ushort mobId, 
            int dropIndex, 
            [FromBody] UpdateDropRequest request)
        {
            try
            {
                // Validate request
                if (mobId != request.MobId || dropIndex != request.DropIndex)
                {
                    return BadRequest(new ApiResponse<MobInfoDto>
                    {
                        Success = false,
                        Message = "Mob ID or drop index mismatch"
                    });
                }

                if (!ModelState.IsValid)
                {
                    var errors = ModelState.SelectMany(x => x.Value?.Errors ?? new Microsoft.AspNetCore.Mvc.ModelBinding.ModelErrorCollection())
                                          .Select(x => x.ErrorMessage)
                                          .ToList();
                    
                    return BadRequest(new ApiResponse<MobInfoDto>
                    {
                        Success = false,
                        Message = "Validation failed",
                        Errors = errors
                    });
                }

                string? userAgent = Request.Headers.UserAgent.FirstOrDefault();
                bool success = await _memoryService.UpdateDropAsync(request, userAgent);

                if (success)
                {
                    var updatedMob = _memoryService.GetMob(mobId);
                    
                    await _notificationService.SendSuccessAsync(
                        "Drop Updated", 
                        $"Successfully updated drop {dropIndex} for {updatedMob?.DisplayName}");

                    return Ok(new ApiResponse<MobInfoDto>
                    {
                        Success = true,
                        Data = updatedMob,
                        Message = "Drop updated successfully"
                    });
                }

                return BadRequest(new ApiResponse<MobInfoDto>
                {
                    Success = false,
                    Message = "Failed to update drop"
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"Error updating drop {dropIndex} for mob {mobId}");
                
                await _notificationService.SendErrorAsync(
                    "Update Failed", 
                    $"Failed to update drop: {ex.Message}");

                return BadRequest(new ApiResponse<MobInfoDto>
                {
                    Success = false,
                    Message = "Error updating drop",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Apply mass edit to multiple mobs
        /// </summary>
        [HttpPost("mass-edit")]
        public async Task<ActionResult<ApiResponse<int>>> ApplyMassEdit([FromBody] MassEditRequest request)
        {
            try
            {
                if (!ModelState.IsValid)
                {
                    var errors = ModelState.SelectMany(x => x.Value?.Errors ?? new Microsoft.AspNetCore.Mvc.ModelBinding.ModelErrorCollection())
                                          .Select(x => x.ErrorMessage)
                                          .ToList();
                    
                    return BadRequest(new ApiResponse<int>
                    {
                        Success = false,
                        Message = "Validation failed",
                        Errors = errors
                    });
                }

                if (request.MobIds.Count == 0)
                {
                    return BadRequest(new ApiResponse<int>
                    {
                        Success = false,
                        Message = "No mobs selected for mass edit"
                    });
                }

                string? userAgent = Request.Headers.UserAgent.FirstOrDefault();
                request.ModifiedBy = userAgent;
                
                int updatedCount = await _memoryService.ApplyMassEditAsync(request);

                await _notificationService.SendSuccessAsync(
                    "Mass Edit Complete", 
                    $"Successfully updated {updatedCount} mobs");

                return Ok(new ApiResponse<int>
                {
                    Success = true,
                    Data = updatedCount,
                    Message = $"Mass edit applied to {updatedCount} mobs"
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error applying mass edit");
                
                await _notificationService.SendErrorAsync(
                    "Mass Edit Failed", 
                    $"Failed to apply mass edit: {ex.Message}");

                return BadRequest(new ApiResponse<int>
                {
                    Success = false,
                    Message = "Error applying mass edit",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Reset a mob to original values
        /// </summary>
        [HttpPost("{mobId}/reset")]
        public async Task<ActionResult<ApiResponse<MobInfoDto>>> ResetMob(ushort mobId)
        {
            try
            {
                bool success = _memoryService.ResetMob(mobId);
                
                if (success)
                {
                    var mob = _memoryService.GetMob(mobId);
                    
                    await _notificationService.SendInfoAsync(
                        "Mob Reset", 
                        $"Reset {mob?.DisplayName} to original values");

                    return Ok(new ApiResponse<MobInfoDto>
                    {
                        Success = true,
                        Data = mob,
                        Message = "Mob reset to original values"
                    });
                }

                return NotFound(new ApiResponse<MobInfoDto>
                {
                    Success = false,
                    Message = $"Mob {mobId} not found or cannot be reset"
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"Error resetting mob {mobId}");
                return BadRequest(new ApiResponse<MobInfoDto>
                {
                    Success = false,
                    Message = "Error resetting mob",
                    Errors = new List<string> { ex.Message }
                });
            }
        }

        /// <summary>
        /// Get statistics for dashboard
        /// </summary>
        [HttpGet("statistics")]
        public ActionResult<ApiResponse<DashboardStatsDto>> GetStatistics()
        {
            try
            {
                var status = _memoryService.GetSystemStatus();
                var allMobs = _memoryService.GetMobs(new MobSearchRequest { PageSize = int.MaxValue });

                var stats = new DashboardStatsDto
                {
                    TotalMobs = status.MobCount,
                    ModifiedMobs = status.ModifiedMobCount,
                    ActiveProcesses = _memoryService.IsAttached ? 1 : 0,
                    LastScanTime = status.LastScanTime,
                    MobsByLevel = allMobs.Data
                        .GroupBy(m => $"Level {(m.Level / 10) * 10}-{(m.Level / 10) * 10 + 9}")
                        .ToDictionary(g => g.Key, g => g.Count()),
                    DropsByGrade = allMobs.Data
                        .SelectMany(m => m.DropInfo.Where(d => d.IsActive))
                        .GroupBy(d => $"Grade {d.Grade}")
                        .ToDictionary(g => g.Key, g => g.Count())
                };

                return Ok(new ApiResponse<DashboardStatsDto>
                {
                    Success = true,
                    Data = stats,
                    Message = "Statistics retrieved successfully"
                });
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error retrieving statistics");
                return BadRequest(new ApiResponse<DashboardStatsDto>
                {
                    Success = false,
                    Message = "Error retrieving statistics",
                    Errors = new List<string> { ex.Message }
                });
            }
        }
    }
}