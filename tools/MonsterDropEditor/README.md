# Shaiya Monster Drop Editor

A comprehensive tool for editing monster drop rates in Shaiya Episode 6 servers in real-time without requiring server restarts.

## 🎯 Features

### ✨ Core Features
- **Real-time Memory Editing** - Modify drop rates instantly without server restart
- **Process Attachment** - Automatically detect and attach to Shaiya server processes
- **Memory Scanner** - Intelligent scanning for MobInfo structures in memory
- **Live Preview** - See changes immediately as you make them
- **Backup & Restore** - Built-in backup system for safety

### 🛠️ Editing Capabilities  
- **Individual Drop Editing** - Edit specific mob drop rates one by one
- **Mass Editing** - Bulk edit multiple mobs or grade ranges at once
- **Grade-based Filtering** - Apply changes to specific item grade ranges
- **Search & Filter** - Find mobs by ID, name, or level
- **Undo/Reset** - Reset changes back to original values

### 💾 Data Management
- **Export/Import** - Save and load drop configurations
- **Backup System** - Automatic backup of original drop data
- **Change Tracking** - Visual indicators for modified entries
- **Validation** - Built-in checks to prevent invalid data

## 🏗️ Architecture

### Core Components

#### `MemoryManager`
- Handles process attachment and memory operations
- Implements Win32 API for reading/writing process memory
- Provides memory scanning capabilities for finding MobInfo structures
- Manages safe memory access with proper error handling

#### `MobStructures`
- Defines C# representations of C++ game structures
- `MobItemDropInfo` - Individual drop information (grade, rate)
- `MobInfo` - Complete mob information including drop arrays
- `MobEntry` - Wrapper class for tracking changes

#### `MainForm` 
- Complete Windows Forms GUI application
- Real-time data binding and updates
- Intuitive interface for all editing operations
- Built-in process management and status reporting

## 🚀 How It Works

### Understanding the Shaiya Drop System

Based on the Shaiya Episode 6 source code analysis:

1. **MobInfo Structure** (`0x10C` bytes)
   - Contains static information about each mob type
   - Located at offset `0xBC`: `Array<MobItemDropInfo, 10> dropInfo`
   - Each mob can have up to 10 different drop entries

2. **MobItemDropInfo Structure** (`0x8` bytes)
   ```cpp
   struct MobItemDropInfo {
       uint16_t grade;    // Item grade/quality (0-65535)
       PAD(2);           // 2 bytes padding
       uint32_t rate;    // Drop rate (0-4294967295)
   };
   ```

3. **CMob Runtime Structure**
   - Contains pointer to MobInfo at offset `0xD4`
   - Runtime mob instances reference static MobInfo data
   - Changes to MobInfo affect all instances of that mob type

### Memory Editing Process

1. **Process Discovery**
   - Scans for common Shaiya process names (`sdev`, `Game`, `shaiya`, etc.)
   - Displays available processes with PIDs

2. **Memory Attachment**
   - Opens process handle with `PROCESS_ALL_ACCESS`
   - Validates process access and memory permissions

3. **Structure Scanning**
   - Enumerates committed memory regions
   - Scans for valid MobInfo structure patterns
   - Validates found structures using heuristics:
     - MobId in reasonable range (1-10000)
     - Level between 1-255
     - Health values within expected bounds

4. **Real-time Editing**
   - Calculates exact memory addresses for drop data
   - Writes changes directly to process memory
   - Updates take effect immediately without server restart

## 📋 Usage Guide

### Getting Started

1. **Launch the Application**
   ```bash
   dotnet run
   ```

2. **Attach to Shaiya Process**
   - Click "Refresh" to update process list
   - Select your Shaiya server process
   - Click "Attach"

3. **Scan for Mobs** 
   - Click "Scan Mobs" after successful attachment
   - Wait for scanning to complete (may take 30-60 seconds)
   - Review found mobs in the list

### Editing Drop Rates

#### Individual Mob Editing
1. Select a mob from the list
2. View current drop information in the drop editor
3. Modify grade or rate values directly in the grid
4. Changes are marked and ready to save

#### Mass Editing
1. Select a mob to edit
2. In the "Mass Edit" panel:
   - Set grade range (From/To)
   - Set new drop rate
   - Click "Apply to Selected"
3. All drops within the grade range will be updated

#### Saving Changes
1. Click "Save All Changes" to write modifications to memory
2. Changes take effect immediately in the game
3. Players will see new drop rates on next mob kill

### Advanced Features

#### Search and Filtering
- Use the search box to find specific mobs
- Search by Mob ID, name, or level
- Results update automatically

#### Backup and Recovery
- Original drop data is automatically backed up
- Use "Reset Drops" to restore a mob to original values
- Export/Import functionality for configuration management

## 🛡️ Safety and Best Practices

### Memory Safety
- All memory operations include bounds checking
- Process handle management with proper cleanup
- Graceful error handling for access violations

### Recommended Usage
1. **Always backup your server data** before using the tool
2. **Test changes on a development server** first
3. **Use reasonable drop rate values** to maintain game balance
4. **Monitor server stability** after making changes

### Troubleshooting

#### Common Issues

**"Failed to attach to process"**
- Run as Administrator
- Ensure Shaiya process is running
- Check for antivirus interference

**"No mobs found during scan"**
- Verify correct process attached
- Ensure server is fully loaded
- Try scanning after spawning mobs

**"Cannot save changes"**
- Check process is still running
- Verify memory write permissions
- Restart tool if process was restarted

## 🔧 Technical Details

### System Requirements
- Windows 10 or later
- .NET 8.0 Runtime
- Administrative privileges (for memory access)
- Shaiya Episode 6 server process

### Memory Layout
```
MobInfo Structure (0x10C bytes total)
├── 0x00-0x21: Basic Info (ID, Name, Level, etc.)
├── 0x22-0xBB: Stats and Attributes  
└── 0xBC-0x10B: Drop Info Array (10 x 8-byte entries)
    ├── Entry 0: Grade(2) + Pad(2) + Rate(4)
    ├── Entry 1: Grade(2) + Pad(2) + Rate(4)
    └── ... (8 more entries)
```

### Performance Considerations
- Memory scanning can take 30-60 seconds for large processes
- Real-time updates have minimal performance impact
- Memory usage scales with number of mobs found

## 🤝 Contributing

This tool was created for the Shaiya community. Contributions welcome!

### Development Setup
```bash
# Clone the repository
git clone https://github.com/nonigagalac/shaiya-episode-6.git
cd shaiya-episode-6/tools/MonsterDropEditor

# Build the project
dotnet build

# Run the application
dotnet run
```

### Code Structure
- `Models/` - Data structures and game object representations
- `Core/` - Memory management and low-level operations  
- `Forms/` - User interface and application logic
- `Utils/` - Utility classes and helper functions

## 📄 License

This tool is provided as-is for educational and community purposes. Use responsibly and in accordance with your server's terms of service.

## 🙏 Credits

- **Original Shaiya Episode 6 Source**: [kurtekat/shaiya-episode-6](https://github.com/kurtekat/shaiya-episode-6)
- **Community Contributions**: Shaiya private server developers
- **Inspiration**: Various Shaiya editing tools and the community's need for better drop editing capabilities

---

*Happy drop editing! 🎮*