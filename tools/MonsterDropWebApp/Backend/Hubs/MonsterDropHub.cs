using Microsoft.AspNetCore.SignalR;
using MonsterDropWebAPI.Models;
using MonsterDropWebAPI.Services;

namespace MonsterDropWebAPI.Hubs
{
    /// <summary>
    /// SignalR Hub for real-time communication with clients
    /// </summary>
    public class MonsterDropHub : Hub
    {
        private readonly MemoryService _memoryService;
        private readonly ILogger<MonsterDropHub> _logger;

        public MonsterDropHub(MemoryService memoryService, ILogger<MonsterDropHub> logger)
        {
            _memoryService = memoryService;
            _logger = logger;
        }

        public override async Task OnConnectedAsync()
        {
            _logger.LogInformation($"Client connected: {Context.ConnectionId}");
            
            // Send current system status to new client
            var status = _memoryService.GetSystemStatus();
            await Clients.Caller.SendAsync("SystemStatusUpdate", status);
            
            // Join default group
            await Groups.AddToGroupAsync(Context.ConnectionId, "DropEditors");
            
            await base.OnConnectedAsync();
        }

        public override async Task OnDisconnectedAsync(Exception? exception)
        {
            _logger.LogInformation($"Client disconnected: {Context.ConnectionId}");
            
            await Groups.RemoveFromGroupAsync(Context.ConnectionId, "DropEditors");
            
            if (exception != null)
            {
                _logger.LogError(exception, "Client disconnected with error");
            }
            
            await base.OnDisconnectedAsync(exception);
        }

        /// <summary>
        /// Join a specific group for targeted notifications
        /// </summary>
        public async Task JoinGroup(string groupName)
        {
            await Groups.AddToGroupAsync(Context.ConnectionId, groupName);
            _logger.LogDebug($"Client {Context.ConnectionId} joined group {groupName}");
        }

        /// <summary>
        /// Leave a specific group
        /// </summary>
        public async Task LeaveGroup(string groupName)
        {
            await Groups.RemoveFromGroupAsync(Context.ConnectionId, groupName);
            _logger.LogDebug($"Client {Context.ConnectionId} left group {groupName}");
        }

        /// <summary>
        /// Request current system status
        /// </summary>
        public async Task RequestSystemStatus()
        {
            var status = _memoryService.GetSystemStatus();
            await Clients.Caller.SendAsync("SystemStatusUpdate", status);
        }

        /// <summary>
        /// Request list of available processes
        /// </summary>
        public async Task RequestProcessList()
        {
            var processes = _memoryService.GetAvailableProcesses();
            await Clients.Caller.SendAsync("ProcessListUpdate", processes);
        }

        /// <summary>
        /// Broadcast notification to all clients in DropEditors group
        /// </summary>
        public async Task SendNotificationToAll(NotificationDto notification)
        {
            await Clients.Group("DropEditors").SendAsync("Notification", notification);
        }

        /// <summary>
        /// Send notification to specific client
        /// </summary>
        public async Task SendNotificationToClient(string connectionId, NotificationDto notification)
        {
            await Clients.Client(connectionId).SendAsync("Notification", notification);
        }
    }

    /// <summary>
    /// Service for managing SignalR notifications
    /// </summary>
    public class NotificationService
    {
        private readonly IHubContext<MonsterDropHub> _hubContext;
        private readonly ILogger<NotificationService> _logger;

        public NotificationService(IHubContext<MonsterDropHub> hubContext, ILogger<NotificationService> logger)
        {
            _hubContext = hubContext;
            _logger = logger;
        }

        /// <summary>
        /// Send notification to all connected clients
        /// </summary>
        public async Task SendToAllAsync(NotificationDto notification)
        {
            try
            {
                await _hubContext.Clients.Group("DropEditors").SendAsync("Notification", notification);
                _logger.LogDebug($"Sent notification to all clients: {notification.Title}");
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error sending notification to all clients");
            }
        }

        /// <summary>
        /// Send notification to specific client
        /// </summary>
        public async Task SendToClientAsync(string connectionId, NotificationDto notification)
        {
            try
            {
                await _hubContext.Clients.Client(connectionId).SendAsync("Notification", notification);
                _logger.LogDebug($"Sent notification to client {connectionId}: {notification.Title}");
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, $"Error sending notification to client {connectionId}");
            }
        }

        /// <summary>
        /// Broadcast mob update to all clients
        /// </summary>
        public async Task BroadcastMobUpdateAsync(MobInfoDto mob)
        {
            try
            {
                await _hubContext.Clients.Group("DropEditors").SendAsync("MobUpdated", mob);
                _logger.LogDebug($"Broadcasted mob update: {mob.DisplayName}");
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error broadcasting mob update");
            }
        }

        /// <summary>
        /// Broadcast system status update to all clients
        /// </summary>
        public async Task BroadcastSystemStatusAsync(SystemStatusDto status)
        {
            try
            {
                await _hubContext.Clients.Group("DropEditors").SendAsync("SystemStatusUpdate", status);
                _logger.LogDebug("Broadcasted system status update");
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error broadcasting system status update");
            }
        }

        /// <summary>
        /// Broadcast process detachment to all clients
        /// </summary>
        public async Task BroadcastProcessDetachedAsync(string processName)
        {
            var notification = new NotificationDto
            {
                Type = "warning",
                Title = "Process Detached",
                Message = $"Lost connection to process: {processName}",
                Timestamp = DateTime.UtcNow
            };

            await SendToAllAsync(notification);
        }

        /// <summary>
        /// Send success notification
        /// </summary>
        public async Task SendSuccessAsync(string title, string message, object? data = null)
        {
            var notification = new NotificationDto
            {
                Type = "success",
                Title = title,
                Message = message,
                Data = data
            };

            await SendToAllAsync(notification);
        }

        /// <summary>
        /// Send error notification
        /// </summary>
        public async Task SendErrorAsync(string title, string message, object? data = null)
        {
            var notification = new NotificationDto
            {
                Type = "error",
                Title = title,
                Message = message,
                Data = data
            };

            await SendToAllAsync(notification);
        }

        /// <summary>
        /// Send warning notification
        /// </summary>
        public async Task SendWarningAsync(string title, string message, object? data = null)
        {
            var notification = new NotificationDto
            {
                Type = "warning",
                Title = title,
                Message = message,
                Data = data
            };

            await SendToAllAsync(notification);
        }

        /// <summary>
        /// Send info notification
        /// </summary>
        public async Task SendInfoAsync(string title, string message, object? data = null)
        {
            var notification = new NotificationDto
            {
                Type = "info",
                Title = title,
                Message = message,
                Data = data
            };

            await SendToAllAsync(notification);
        }
    }
}