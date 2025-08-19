using System.Text.Json;
using MonsterDropEditor.Models;

namespace MonsterDropEditor.Utils
{
    /// <summary>
    /// Handles configuration and data export/import operations
    /// </summary>
    public static class ConfigManager
    {
        /// <summary>
        /// Export drop configuration to JSON file
        /// </summary>
        /// <param name="mobEntries">List of mob entries to export</param>
        /// <param name="filePath">Target file path</param>
        /// <returns>True if successful</returns>
        public static bool ExportDropData(List<MobEntry> mobEntries, string filePath)
        {
            try
            {
                var exportData = mobEntries.Select(mob => new
                {
                    MobId = mob.Info.MobId,
                    MobName = mob.Info.GetMobName(),
                    Level = mob.Info.Level,
                    DropInfo = mob.Info.DropInfo?.Select(drop => new
                    {
                        Grade = drop.Grade,
                        Rate = drop.Rate
                    }).ToArray()
                }).ToList();

                var options = new JsonSerializerOptions
                {
                    WriteIndented = true,
                    PropertyNamingPolicy = JsonNamingPolicy.CamelCase
                };

                string json = JsonSerializer.Serialize(exportData, options);
                File.WriteAllText(filePath, json);
                
                return true;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Export failed: {ex.Message}");
                return false;
            }
        }

        /// <summary>
        /// Import drop configuration from JSON file
        /// </summary>
        /// <param name="filePath">Source file path</param>
        /// <param name="mobEntries">Current mob entries to update</param>
        /// <returns>Number of mobs updated, -1 if failed</returns>
        public static int ImportDropData(string filePath, List<MobEntry> mobEntries)
        {
            try
            {
                if (!File.Exists(filePath))
                    return -1;

                string json = File.ReadAllText(filePath);
                
                using JsonDocument document = JsonDocument.Parse(json);
                JsonElement root = document.RootElement;

                int updatedCount = 0;

                foreach (JsonElement mobElement in root.EnumerateArray())
                {
                    if (!mobElement.TryGetProperty("mobId", out JsonElement mobIdElement))
                        continue;

                    ushort mobId = mobIdElement.GetUInt16();
                    
                    // Find corresponding mob in current list
                    var mob = mobEntries.FirstOrDefault(m => m.Info.MobId == mobId);
                    if (mob == null)
                        continue;

                    if (mobElement.TryGetProperty("dropInfo", out JsonElement dropInfoElement))
                    {
                        var dropList = new List<MobItemDropInfo>();
                        
                        foreach (JsonElement dropElement in dropInfoElement.EnumerateArray())
                        {
                            if (dropElement.TryGetProperty("grade", out JsonElement gradeElement) &&
                                dropElement.TryGetProperty("rate", out JsonElement rateElement))
                            {
                                dropList.Add(new MobItemDropInfo(
                                    gradeElement.GetUInt16(),
                                    rateElement.GetUInt32()
                                ));
                            }
                        }

                        // Pad with empty entries if needed
                        while (dropList.Count < 10)
                        {
                            dropList.Add(new MobItemDropInfo(0, 0));
                        }

                        // Update mob drop info
                        mob.Info.DropInfo = dropList.Take(10).ToArray();
                        mob.IsModified = true;
                        updatedCount++;
                    }
                }

                return updatedCount;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Import failed: {ex.Message}");
                return -1;
            }
        }

        /// <summary>
        /// Save application settings to file
        /// </summary>
        /// <param name="settings">Settings to save</param>
        /// <returns>True if successful</returns>
        public static bool SaveSettings(AppSettings settings)
        {
            try
            {
                string appDataPath = Path.Combine(
                    Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
                    "ShaiyaDropEditor");

                if (!Directory.Exists(appDataPath))
                    Directory.CreateDirectory(appDataPath);

                string settingsPath = Path.Combine(appDataPath, "settings.json");

                var options = new JsonSerializerOptions
                {
                    WriteIndented = true
                };

                string json = JsonSerializer.Serialize(settings, options);
                File.WriteAllText(settingsPath, json);
                
                return true;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Save settings failed: {ex.Message}");
                return false;
            }
        }

        /// <summary>
        /// Load application settings from file
        /// </summary>
        /// <returns>Loaded settings or default settings if failed</returns>
        public static AppSettings LoadSettings()
        {
            try
            {
                string appDataPath = Path.Combine(
                    Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
                    "ShaiyaDropEditor");

                string settingsPath = Path.Combine(appDataPath, "settings.json");

                if (!File.Exists(settingsPath))
                    return new AppSettings();

                string json = File.ReadAllText(settingsPath);
                return JsonSerializer.Deserialize<AppSettings>(json) ?? new AppSettings();
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Load settings failed: {ex.Message}");
                return new AppSettings();
            }
        }

        /// <summary>
        /// Create backup of current drop data
        /// </summary>
        /// <param name="mobEntries">Mob entries to backup</param>
        /// <returns>Backup file path if successful, null if failed</returns>
        public static string? CreateBackup(List<MobEntry> mobEntries)
        {
            try
            {
                string appDataPath = Path.Combine(
                    Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
                    "ShaiyaDropEditor",
                    "Backups");

                if (!Directory.Exists(appDataPath))
                    Directory.CreateDirectory(appDataPath);

                string timestamp = DateTime.Now.ToString("yyyyMMdd_HHmmss");
                string backupPath = Path.Combine(appDataPath, $"backup_{timestamp}.json");

                if (ExportDropData(mobEntries, backupPath))
                {
                    return backupPath;
                }

                return null;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Create backup failed: {ex.Message}");
                return null;
            }
        }

        /// <summary>
        /// Get list of available backup files
        /// </summary>
        /// <returns>List of backup file info</returns>
        public static List<BackupInfo> GetAvailableBackups()
        {
            var backups = new List<BackupInfo>();

            try
            {
                string backupsPath = Path.Combine(
                    Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
                    "ShaiyaDropEditor",
                    "Backups");

                if (!Directory.Exists(backupsPath))
                    return backups;

                var files = Directory.GetFiles(backupsPath, "backup_*.json")
                    .OrderByDescending(f => File.GetCreationTime(f));

                foreach (string file in files)
                {
                    var fileInfo = new FileInfo(file);
                    backups.Add(new BackupInfo
                    {
                        FilePath = file,
                        FileName = Path.GetFileNameWithoutExtension(file),
                        CreatedDate = fileInfo.CreationTime,
                        Size = fileInfo.Length
                    });
                }
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine($"Get backups failed: {ex.Message}");
            }

            return backups;
        }
    }

    /// <summary>
    /// Application settings class
    /// </summary>
    public class AppSettings
    {
        public string LastProcessName { get; set; } = "";
        public bool AutoBackup { get; set; } = true;
        public bool ConfirmSave { get; set; } = true;
        public int MaxBackups { get; set; } = 10;
        public string DefaultExportPath { get; set; } = "";
        public bool ShowModifiedOnly { get; set; } = false;
    }

    /// <summary>
    /// Backup file information
    /// </summary>
    public class BackupInfo
    {
        public string FilePath { get; set; } = "";
        public string FileName { get; set; } = "";
        public DateTime CreatedDate { get; set; }
        public long Size { get; set; }

        public string DisplayName => 
            $"{FileName} ({CreatedDate:yyyy-MM-dd HH:mm}) - {Size / 1024:N0} KB";
    }
}