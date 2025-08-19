using System.Runtime.InteropServices;
using System.ComponentModel.DataAnnotations;

namespace MonsterDropWebAPI.Models
{
    /// <summary>
    /// Web-friendly version of MobItemDropInfo for API responses
    /// </summary>
    public class DropInfoDto
    {
        public int Index { get; set; }
        
        [Range(0, 65535)]
        public ushort Grade { get; set; }
        
        [Range(0, uint.MaxValue)]
        public uint Rate { get; set; }
        
        public string Percentage { get; set; } = "0%";
        
        public bool IsActive { get; set; }
        
        public string Color { get; set; } = "#666666";
    }

    /// <summary>
    /// Web-friendly version of MobInfo for API responses
    /// </summary>
    public class MobInfoDto
    {
        public ushort MobId { get; set; }
        public string MobName { get; set; } = "";
        public ushort Level { get; set; }
        public ushort Exp { get; set; }
        public uint Health { get; set; }
        public ushort Money { get; set; }
        public ushort MoneyAdd { get; set; }
        public bool IsModified { get; set; }
        public string DisplayName { get; set; } = "";
        public List<DropInfoDto> DropInfo { get; set; } = new();
        public DateTime LastModified { get; set; }
        public string ModifiedBy { get; set; } = "";
    }

    /// <summary>
    /// Request model for updating drop rates
    /// </summary>
    public class UpdateDropRequest
    {
        [Required]
        public ushort MobId { get; set; }
        
        [Required]
        [Range(0, 9)]
        public int DropIndex { get; set; }
        
        [Range(0, 65535)]
        public ushort Grade { get; set; }
        
        [Range(0, uint.MaxValue)]
        public uint Rate { get; set; }
    }

    /// <summary>
    /// Request model for mass editing drops
    /// </summary>
    public class MassEditRequest
    {
        public List<ushort> MobIds { get; set; } = new();
        
        [Range(0, 65535)]
        public ushort? FromGrade { get; set; }
        
        [Range(0, 65535)]
        public ushort? ToGrade { get; set; }
        
        [Range(0, uint.MaxValue)]
        public uint NewRate { get; set; }
        
        public bool ApplyToAllGrades { get; set; } = false;
        
        public string? ModifiedBy { get; set; }
    }

    /// <summary>
    /// Process information for frontend
    /// </summary>
    public class ProcessInfoDto
    {
        public string Name { get; set; } = "";
        public int Id { get; set; }
        public bool IsAttached { get; set; }
        public DateTime LastSeen { get; set; }
        public string Status { get; set; } = "";
    }

    /// <summary>
    /// System status information
    /// </summary>
    public class SystemStatusDto
    {
        public bool IsProcessAttached { get; set; }
        public string ProcessName { get; set; } = "";
        public int ProcessId { get; set; }
        public int MobCount { get; set; }
        public int ModifiedMobCount { get; set; }
        public DateTime LastScanTime { get; set; }
        public List<string> RecentActions { get; set; } = new();
        public bool HasUnsavedChanges { get; set; }
    }

    /// <summary>
    /// Search and filter parameters
    /// </summary>
    public class MobSearchRequest
    {
        public string? SearchTerm { get; set; }
        public ushort? MinLevel { get; set; }
        public ushort? MaxLevel { get; set; }
        public bool? ModifiedOnly { get; set; }
        public int Page { get; set; } = 1;
        public int PageSize { get; set; } = 50;
        public string SortBy { get; set; } = "MobId";
        public bool SortDescending { get; set; } = false;
    }

    /// <summary>
    /// Paginated response wrapper
    /// </summary>
    public class PagedResponse<T>
    {
        public List<T> Data { get; set; } = new();
        public int TotalCount { get; set; }
        public int Page { get; set; }
        public int PageSize { get; set; }
        public int TotalPages { get; set; }
        public bool HasNextPage { get; set; }
        public bool HasPreviousPage { get; set; }
    }

    /// <summary>
    /// API response wrapper
    /// </summary>
    public class ApiResponse<T>
    {
        public bool Success { get; set; }
        public T? Data { get; set; }
        public string Message { get; set; } = "";
        public List<string> Errors { get; set; } = new();
        public DateTime Timestamp { get; set; } = DateTime.UtcNow;
    }

    /// <summary>
    /// Export/Import models
    /// </summary>
    public class ExportRequest
    {
        public List<ushort>? MobIds { get; set; }
        public bool ExportAll { get; set; } = false;
        public string Format { get; set; } = "json"; // json, csv, xml
        public bool IncludeOriginalValues { get; set; } = false;
    }

    public class ImportRequest
    {
        [Required]
        public string Data { get; set; } = "";
        
        [Required]
        public string Format { get; set; } = "json";
        
        public bool OverwriteExisting { get; set; } = false;
        
        public string? ImportedBy { get; set; }
    }

    /// <summary>
    /// Backup information
    /// </summary>
    public class BackupInfoDto
    {
        public string Id { get; set; } = "";
        public string Name { get; set; } = "";
        public DateTime CreatedDate { get; set; }
        public long Size { get; set; }
        public int MobCount { get; set; }
        public string CreatedBy { get; set; } = "";
        public string Description { get; set; } = "";
    }

    /// <summary>
    /// Real-time notification model
    /// </summary>
    public class NotificationDto
    {
        public string Type { get; set; } = ""; // info, warning, error, success
        public string Title { get; set; } = "";
        public string Message { get; set; } = "";
        public DateTime Timestamp { get; set; } = DateTime.UtcNow;
        public object? Data { get; set; }
    }

    /// <summary>
    /// Validation result for web API
    /// </summary>
    public class ValidationResultDto
    {
        public bool IsValid { get; set; }
        public List<string> Errors { get; set; } = new();
        public List<string> Warnings { get; set; } = new();
        public List<string> Info { get; set; } = new();
    }

    /// <summary>
    /// Statistics for dashboard
    /// </summary>
    public class DashboardStatsDto
    {
        public int TotalMobs { get; set; }
        public int ModifiedMobs { get; set; }
        public int ActiveProcesses { get; set; }
        public DateTime LastScanTime { get; set; }
        public TimeSpan Uptime { get; set; }
        public List<RecentActivityDto> RecentActivity { get; set; } = new();
        public Dictionary<string, int> MobsByLevel { get; set; } = new();
        public Dictionary<string, int> DropsByGrade { get; set; } = new();
    }

    public class RecentActivityDto
    {
        public string Action { get; set; } = "";
        public string Details { get; set; } = "";
        public DateTime Timestamp { get; set; }
        public string User { get; set; } = "";
    }
}