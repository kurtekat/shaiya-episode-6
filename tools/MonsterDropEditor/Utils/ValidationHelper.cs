using MonsterDropEditor.Models;

namespace MonsterDropEditor.Utils
{
    /// <summary>
    /// Helper class for validating drop rate data and providing safety checks
    /// </summary>
    public static class ValidationHelper
    {
        /// <summary>
        /// Maximum reasonable drop rate (100% = 10000, allowing up to 1000% for special cases)
        /// </summary>
        public const uint MAX_REASONABLE_RATE = 100000;

        /// <summary>
        /// Maximum item grade based on typical Shaiya items
        /// </summary>
        public const ushort MAX_REASONABLE_GRADE = 30;

        /// <summary>
        /// Validate a single drop rate entry
        /// </summary>
        /// <param name="dropInfo">Drop info to validate</param>
        /// <returns>Validation result with any warnings or errors</returns>
        public static ValidationResult ValidateDropInfo(MobItemDropInfo dropInfo)
        {
            var result = new ValidationResult();

            // Check grade range
            if (dropInfo.Grade > MAX_REASONABLE_GRADE)
            {
                result.Warnings.Add($"Grade {dropInfo.Grade} is unusually high (typical range: 0-{MAX_REASONABLE_GRADE})");
            }

            // Check rate range
            if (dropInfo.Rate > MAX_REASONABLE_RATE)
            {
                result.Warnings.Add($"Rate {dropInfo.Rate} is very high (may cause balance issues)");
            }

            // Check for zero values (might be intentional)
            if (dropInfo.Grade == 0 && dropInfo.Rate > 0)
            {
                result.Warnings.Add("Grade is 0 but rate is set - this may not work as expected");
            }

            if (dropInfo.Rate == 0 && dropInfo.Grade > 0)
            {
                result.Info.Add("Rate is 0 - this drop will never occur");
            }

            return result;
        }

        /// <summary>
        /// Validate all drop info for a mob
        /// </summary>
        /// <param name="mobEntry">Mob entry to validate</param>
        /// <returns>Validation result</returns>
        public static ValidationResult ValidateMobDrops(MobEntry mobEntry)
        {
            var result = new ValidationResult();

            if (mobEntry.Info.DropInfo == null)
            {
                result.Errors.Add("Drop info is null");
                return result;
            }

            uint totalRate = 0;
            int activeDrops = 0;

            for (int i = 0; i < mobEntry.Info.DropInfo.Length; i++)
            {
                var drop = mobEntry.Info.DropInfo[i];
                
                if (drop.Grade > 0 || drop.Rate > 0)
                {
                    activeDrops++;
                    totalRate += drop.Rate;

                    var dropValidation = ValidateDropInfo(drop);
                    result.Merge(dropValidation, $"Drop {i + 1}: ");
                }
            }

            // Check total drop rate
            if (totalRate > MAX_REASONABLE_RATE)
            {
                result.Warnings.Add($"Total drop rate ({totalRate}) is very high - mob may drop too many items");
            }

            if (activeDrops == 0)
            {
                result.Info.Add("No active drops configured for this mob");
            }
            else
            {
                result.Info.Add($"Mob has {activeDrops} active drop(s) with total rate: {totalRate}");
            }

            return result;
        }

        /// <summary>
        /// Validate memory address for safety
        /// </summary>
        /// <param name="address">Memory address to validate</param>
        /// <returns>True if address appears safe to write to</returns>
        public static bool ValidateMemoryAddress(IntPtr address)
        {
            // Basic sanity checks for memory addresses
            long addr = address.ToInt64();

            // Should be in user space (below 0x80000000 for 32-bit, reasonable range for 64-bit)
            if (addr <= 0 || addr >= 0x7FFFFFFF000L)
                return false;

            // Should be aligned to at least 4-byte boundary
            if (addr % 4 != 0)
                return false;

            return true;
        }

        /// <summary>
        /// Get drop rate as percentage string for display
        /// </summary>
        /// <param name="rate">Raw drop rate value</param>
        /// <param name="baseRate">Base rate for percentage calculation (default 10000 = 100%)</param>
        /// <returns>Formatted percentage string</returns>
        public static string GetDropPercentage(uint rate, uint baseRate = 10000)
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

        /// <summary>
        /// Suggest reasonable drop rate based on mob level and item grade
        /// </summary>
        /// <param name="mobLevel">Mob level</param>
        /// <param name="itemGrade">Item grade</param>
        /// <returns>Suggested drop rate</returns>
        public static uint SuggestDropRate(ushort mobLevel, ushort itemGrade)
        {
            // Basic algorithm for suggesting drop rates
            // Higher grade items should be rarer
            // Higher level mobs can have better drops
            
            uint baseRate = 1000; // 10% base rate
            
            // Adjust for item grade (higher grade = lower rate)
            if (itemGrade > 0)
            {
                double gradeMultiplier = Math.Max(0.1, 1.0 / Math.Pow(itemGrade, 0.5));
                baseRate = (uint)(baseRate * gradeMultiplier);
            }
            
            // Adjust for mob level (higher level = slightly better rates)
            if (mobLevel > 1)
            {
                double levelMultiplier = 1.0 + (mobLevel - 1) * 0.01; // 1% increase per level
                baseRate = (uint)(baseRate * levelMultiplier);
            }
            
            // Ensure minimum and maximum bounds
            return Math.Max(1u, Math.Min(baseRate, MAX_REASONABLE_RATE));
        }

        /// <summary>
        /// Check if drop configuration looks like it needs attention
        /// </summary>
        /// <param name="mobEntry">Mob entry to check</param>
        /// <returns>True if configuration may need review</returns>
        public static bool NeedsReview(MobEntry mobEntry)
        {
            var validation = ValidateMobDrops(mobEntry);
            return validation.HasWarnings || validation.HasErrors;
        }

        /// <summary>
        /// Get color suggestion for UI based on drop rate
        /// </summary>
        /// <param name="rate">Drop rate</param>
        /// <returns>Color for UI display</returns>
        public static Color GetRateColor(uint rate)
        {
            if (rate == 0)
                return Color.Gray;
            else if (rate <= 100) // Very rare (< 1%)
                return Color.Red;
            else if (rate <= 1000) // Rare (1-10%)
                return Color.Orange;
            else if (rate <= 5000) // Common (10-50%)
                return Color.Green;
            else if (rate <= 10000) // Very common (50-100%)
                return Color.Blue;
            else // Extremely high (> 100%)
                return Color.Purple;
        }
    }

    /// <summary>
    /// Result of validation operations
    /// </summary>
    public class ValidationResult
    {
        public List<string> Errors { get; set; } = new List<string>();
        public List<string> Warnings { get; set; } = new List<string>();
        public List<string> Info { get; set; } = new List<string>();

        public bool HasErrors => Errors.Count > 0;
        public bool HasWarnings => Warnings.Count > 0;
        public bool HasInfo => Info.Count > 0;
        public bool IsValid => !HasErrors;

        /// <summary>
        /// Merge another validation result into this one
        /// </summary>
        /// <param name="other">Other validation result</param>
        /// <param name="prefix">Prefix to add to messages</param>
        public void Merge(ValidationResult other, string prefix = "")
        {
            foreach (var error in other.Errors)
                Errors.Add(prefix + error);
            
            foreach (var warning in other.Warnings)
                Warnings.Add(prefix + warning);
            
            foreach (var info in other.Info)
                Info.Add(prefix + info);
        }

        /// <summary>
        /// Get all messages as a single formatted string
        /// </summary>
        /// <returns>Formatted message string</returns>
        public string GetFormattedMessage()
        {
            var messages = new List<string>();

            if (HasErrors)
            {
                messages.Add("ERRORS:");
                messages.AddRange(Errors.Select(e => "  • " + e));
            }

            if (HasWarnings)
            {
                messages.Add("WARNINGS:");
                messages.AddRange(Warnings.Select(w => "  • " + w));
            }

            if (HasInfo)
            {
                messages.Add("INFO:");
                messages.AddRange(Info.Select(i => "  • " + i));
            }

            return string.Join(Environment.NewLine, messages);
        }
    }
}