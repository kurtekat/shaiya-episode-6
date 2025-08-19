# Shaiya Monster Drop Web Application

A modern, responsive web application for editing Shaiya Episode 6 monster drop rates in real-time. Built with ASP.NET Core backend and React frontend.

## 🌟 Features

### 🎯 Core Capabilities
- **Real-time Memory Editing** - Modify drop rates instantly without server restart
- **Web-based Interface** - Access from any device with a modern web browser
- **Live Updates** - Real-time notifications and updates via SignalR
- **Responsive Design** - Works on desktop, tablet, and mobile devices
- **Dark/Light Mode** - Toggle between themes for better user experience

### 🛠️ Advanced Features
- **Process Management** - Attach/detach from Shaiya server processes
- **Memory Scanning** - Automatic detection of MobInfo structures in memory
- **Mass Editing** - Bulk operations for editing multiple monsters
- **Export/Import** - Save and load drop configurations
- **Statistics Dashboard** - Visual analytics and monitoring
- **Real-time Notifications** - Server-sent updates and alerts

### 🔒 Safety & Validation
- **Input Validation** - Prevent invalid or dangerous values
- **Memory Safety** - Safe memory access with error handling
- **Backup System** - Automatic backup of original values
- **Connection Monitoring** - Real-time connection status tracking

## 🏗️ Architecture

### Backend (ASP.NET Core 8.0)
```
Backend/
├── Controllers/          # API endpoints
│   ├── MobController.cs     # Monster management
│   └── SystemController.cs  # System operations
├── Services/             # Business logic
│   └── MemoryService.cs     # Memory operations
├── Hubs/                # SignalR hubs
│   └── MonsterDropHub.cs    # Real-time communication
├── Models/              # Data models
│   └── WebMobModels.cs      # API DTOs
└── Program.cs           # Application entry point
```

### Frontend (React 18 + TypeScript)
```
Frontend/
├── src/
│   ├── components/      # Reusable UI components
│   ├── pages/          # Page components
│   ├── hooks/          # Custom React hooks
│   ├── services/       # API and SignalR services
│   ├── types/          # TypeScript definitions
│   └── utils/          # Utility functions
├── package.json        # Dependencies and scripts
└── vite.config.ts      # Build configuration
```

## 🚀 Getting Started

### Prerequisites
- .NET 8.0 SDK
- Node.js 18+ and npm/yarn
- Modern web browser
- Shaiya Episode 6 server process (for testing)

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/nonigagalac/shaiya-episode-6.git
   cd shaiya-episode-6/tools/MonsterDropWebApp
   ```

2. **Backend Setup**
   ```bash
   cd Backend
   dotnet restore
   dotnet build
   ```

3. **Frontend Setup**
   ```bash
   cd Frontend
   npm install
   ```

### Development

1. **Start Backend API** (Terminal 1)
   ```bash
   cd Backend
   dotnet run
   ```
   API will be available at: `http://localhost:5000`

2. **Start Frontend Dev Server** (Terminal 2)
   ```bash
   cd Frontend
   npm run dev
   ```
   Web app will be available at: `http://localhost:3000`

3. **Open in Browser**
   Navigate to `http://localhost:3000` to access the application

### Production Build

1. **Build Backend**
   ```bash
   cd Backend
   dotnet publish -c Release -o ./publish
   ```

2. **Build Frontend**
   ```bash
   cd Frontend
   npm run build
   ```

3. **Deploy**
   Deploy the backend publish folder and frontend dist folder to your web server.

## 🎮 Usage Guide

### 1. Initial Setup
- Open the web application in your browser
- The dashboard will show connection status and system information

### 2. Connect to Shaiya Process
- Navigate to the System page
- View available Shaiya processes
- Click "Attach" on your target server process

### 3. Scan for Monsters
- After successful attachment, click "Scan for Mobs"
- Wait for the memory scan to complete (30-60 seconds)
- View discovered monsters in the Monster List

### 4. Edit Drop Rates
- **Individual Editing**: Select a monster and modify drop rates directly
- **Mass Editing**: Select multiple monsters for bulk operations
- **Real-time Updates**: Changes are reflected immediately
- **Save Changes**: Apply modifications to server memory

### 5. Monitor & Manage
- **Dashboard**: Monitor system status and statistics
- **Real-time Notifications**: Receive updates on operations
- **Export/Import**: Backup and restore configurations

## 📊 API Endpoints

### System Management
```
GET    /api/system/status          # Get system status
GET    /api/system/processes       # List available processes
POST   /api/system/attach/{id}     # Attach to process
POST   /api/system/detach          # Detach from process
POST   /api/system/scan            # Scan for mobs
POST   /api/system/save            # Save all changes
POST   /api/system/export          # Export data
```

### Monster Management
```
GET    /api/mob                    # Get monsters (paginated)
GET    /api/mob/{id}               # Get specific monster
PUT    /api/mob/{id}/drops/{index} # Update drop rate
POST   /api/mob/mass-edit          # Apply mass edits
POST   /api/mob/{id}/reset         # Reset to original values
GET    /api/mob/statistics         # Get statistics
```

### SignalR Hub
```
/hubs/monsterdrop                  # Real-time updates
```

## 🔧 Configuration

### Backend Configuration (appsettings.json)
```json
{
  "Logging": {
    "LogLevel": {
      "Default": "Information",
      "Microsoft.AspNetCore": "Warning"
    }
  },
  "AllowedHosts": "*"
}
```

### Frontend Configuration (vite.config.ts)
```typescript
export default defineConfig({
  server: {
    port: 3000,
    proxy: {
      '/api': 'http://localhost:5000',
      '/hubs': 'http://localhost:5000'
    }
  }
})
```

## 🔍 Troubleshooting

### Common Issues

**Backend won't start**
- Ensure .NET 8.0 SDK is installed
- Check if port 5000 is available
- Run as Administrator for memory access

**Frontend build fails**
- Ensure Node.js 18+ is installed
- Clear node_modules and reinstall: `rm -rf node_modules package-lock.json && npm install`

**Can't connect to Shaiya process**
- Run application as Administrator
- Ensure Shaiya server is running
- Check Windows Defender/Antivirus settings

**Real-time updates not working**
- Check browser console for SignalR connection errors
- Ensure WebSocket connections are allowed
- Verify proxy configuration for development

### Memory Access Issues
- **Administrator Rights**: Required for memory operations
- **Antivirus Software**: May block memory access
- **Process Protection**: Some processes may have protection enabled

## 🛡️ Security Considerations

### Production Deployment
- **HTTPS Only**: Always use HTTPS in production
- **Authentication**: Implement user authentication for sensitive operations
- **Authorization**: Restrict access to authorized users only
- **Rate Limiting**: Implement API rate limiting
- **Input Validation**: All inputs are validated on both client and server

### Memory Safety
- **Bounds Checking**: All memory operations include bounds checking
- **Process Validation**: Verify target process before attachment
- **Error Recovery**: Graceful handling of memory access errors

## 📈 Performance

### Optimization Features
- **Lazy Loading**: Components load on demand
- **Code Splitting**: Optimized bundle sizes
- **Caching**: Intelligent caching strategies
- **Real-time Updates**: Efficient SignalR communication
- **Memory Efficiency**: Optimized memory scanning algorithms

### Monitoring
- **Connection Status**: Real-time connection monitoring
- **Performance Metrics**: Built-in performance tracking
- **Error Reporting**: Comprehensive error logging
- **System Statistics**: Resource usage monitoring

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/amazing-feature`
3. Commit changes: `git commit -m 'Add amazing feature'`
4. Push to branch: `git push origin feature/amazing-feature`
5. Open a Pull Request

### Development Guidelines
- Follow TypeScript and C# coding standards
- Add tests for new features
- Update documentation for API changes
- Ensure responsive design for UI changes

## 📄 License

This project is provided as-is for educational and community purposes. Use responsibly and in accordance with your server's terms of service.

## 🙏 Credits

- **Original Concept**: Desktop Monster Drop Editor
- **Web Framework**: ASP.NET Core & React
- **UI Library**: Chakra UI
- **Real-time Communication**: SignalR
- **Community**: Shaiya private server developers

---

*Built with ❤️ for the Shaiya community*