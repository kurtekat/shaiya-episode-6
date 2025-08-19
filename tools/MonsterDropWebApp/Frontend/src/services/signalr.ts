import { HubConnection, HubConnectionBuilder, HubConnectionState, LogLevel } from '@microsoft/signalr';
import { 
  NotificationDto, 
  SystemStatusDto, 
  MobInfoDto, 
  ProcessInfoDto, 
  SignalREvents, 
  ConnectionState 
} from '@types/index';

class SignalRService {
  private connection: HubConnection | null = null;
  private connectionState: ConnectionState = { status: 'disconnected' };
  private eventListeners = new Map<keyof SignalREvents, Function[]>();
  private reconnectAttempts = 0;
  private maxReconnectAttempts = 5;
  private reconnectDelay = 1000; // Start with 1 second
  private reconnectTimer?: NodeJS.Timeout;

  constructor() {
    this.initializeConnection();
  }

  private initializeConnection(): void {
    const hubUrl = `${window.location.origin}/hubs/monsterdrop`;
    
    this.connection = new HubConnectionBuilder()
      .withUrl(hubUrl, {
        skipNegotiation: false,
        transport: 1 | 2 | 4, // WebSockets, ServerSentEvents, LongPolling
      })
      .withAutomaticReconnect({
        nextRetryDelayInMilliseconds: (retryContext) => {
          // Exponential backoff: 1s, 2s, 4s, 8s, 16s, then 30s
          if (retryContext.previousRetryCount < 5) {
            return Math.pow(2, retryContext.previousRetryCount) * 1000;
          }
          return 30000; // Max 30 seconds
        }
      })
      .configureLogging(LogLevel.Information)
      .build();

    this.setupEventHandlers();
  }

  private setupEventHandlers(): void {
    if (!this.connection) return;

    // Connection state events
    this.connection.onclose((error) => {
      console.log('SignalR connection closed', error);
      this.updateConnectionState('disconnected', error?.message);
      this.notifyStateChange();
    });

    this.connection.onreconnecting((error) => {
      console.log('SignalR reconnecting', error);
      this.updateConnectionState('reconnecting', error?.message);
      this.notifyStateChange();
    });

    this.connection.onreconnected((connectionId) => {
      console.log('SignalR reconnected', connectionId);
      this.updateConnectionState('connected');
      this.notifyStateChange();
      this.reconnectAttempts = 0;
      
      // Re-join default group
      this.joinGroup('DropEditors');
    });

    // Server events
    this.connection.on('SystemStatusUpdate', (status: SystemStatusDto) => {
      console.log('📊 System status update received', status);
      this.emit('SystemStatusUpdate', status);
    });

    this.connection.on('MobUpdated', (mob: MobInfoDto) => {
      console.log('🐉 Mob updated', mob.displayName);
      this.emit('MobUpdated', mob);
    });

    this.connection.on('Notification', (notification: NotificationDto) => {
      console.log(`🔔 ${notification.type.toUpperCase()}: ${notification.title}`);
      this.emit('Notification', notification);
    });

    this.connection.on('ProcessListUpdate', (processes: ProcessInfoDto[]) => {
      console.log('🔄 Process list updated', processes.length);
      this.emit('ProcessListUpdate', processes);
    });
  }

  private updateConnectionState(status: ConnectionState['status'], errorMessage?: string): void {
    this.connectionState = {
      status,
      lastConnected: status === 'connected' ? new Date() : this.connectionState.lastConnected,
      errorMessage: status === 'error' ? errorMessage : undefined,
    };
  }

  private notifyStateChange(): void {
    // Emit connection state change to listeners
    this.emit('ConnectionStateChanged' as keyof SignalREvents, this.connectionState as any);
  }

  async startConnection(): Promise<void> {
    if (!this.connection) {
      throw new Error('SignalR connection not initialized');
    }

    if (this.connection.state === HubConnectionState.Connected) {
      console.log('SignalR already connected');
      return;
    }

    try {
      this.updateConnectionState('connecting');
      this.notifyStateChange();

      console.log('🔌 Starting SignalR connection...');
      await this.connection.start();
      
      console.log('✅ SignalR connection established');
      this.updateConnectionState('connected');
      this.notifyStateChange();
      
      // Join default group
      await this.joinGroup('DropEditors');
      
      // Request initial system status
      await this.requestSystemStatus();
      
    } catch (error) {
      console.error('❌ Failed to start SignalR connection:', error);
      this.updateConnectionState('error', (error as Error).message);
      this.notifyStateChange();
      
      // Attempt to reconnect
      this.scheduleReconnect();
      throw error;
    }
  }

  async stopConnection(): Promise<void> {
    if (this.reconnectTimer) {
      clearTimeout(this.reconnectTimer);
      this.reconnectTimer = undefined;
    }

    if (this.connection && this.connection.state !== HubConnectionState.Disconnected) {
      console.log('🔌 Stopping SignalR connection...');
      await this.connection.stop();
      this.updateConnectionState('disconnected');
      this.notifyStateChange();
    }
  }

  private scheduleReconnect(): void {
    if (this.reconnectAttempts >= this.maxReconnectAttempts) {
      console.log('❌ Max reconnection attempts reached');
      this.updateConnectionState('error', 'Maximum reconnection attempts exceeded');
      this.notifyStateChange();
      return;
    }

    this.reconnectAttempts++;
    const delay = Math.min(this.reconnectDelay * Math.pow(2, this.reconnectAttempts - 1), 30000);
    
    console.log(`🔄 Scheduling reconnect attempt ${this.reconnectAttempts} in ${delay}ms`);
    
    this.reconnectTimer = setTimeout(async () => {
      try {
        await this.startConnection();
      } catch (error) {
        console.error('Reconnection attempt failed:', error);
        this.scheduleReconnect();
      }
    }, delay);
  }

  async joinGroup(groupName: string): Promise<void> {
    if (this.isConnected()) {
      await this.connection!.invoke('JoinGroup', groupName);
      console.log(`👥 Joined group: ${groupName}`);
    }
  }

  async leaveGroup(groupName: string): Promise<void> {
    if (this.isConnected()) {
      await this.connection!.invoke('LeaveGroup', groupName);
      console.log(`👋 Left group: ${groupName}`);
    }
  }

  async requestSystemStatus(): Promise<void> {
    if (this.isConnected()) {
      await this.connection!.invoke('RequestSystemStatus');
    }
  }

  async requestProcessList(): Promise<void> {
    if (this.isConnected()) {
      await this.connection!.invoke('RequestProcessList');
    }
  }

  // Event subscription methods
  on<K extends keyof SignalREvents>(event: K, callback: SignalREvents[K]): void {
    if (!this.eventListeners.has(event)) {
      this.eventListeners.set(event, []);
    }
    this.eventListeners.get(event)!.push(callback);
  }

  off<K extends keyof SignalREvents>(event: K, callback: SignalREvents[K]): void {
    const listeners = this.eventListeners.get(event);
    if (listeners) {
      const index = listeners.indexOf(callback);
      if (index > -1) {
        listeners.splice(index, 1);
      }
    }
  }

  private emit<K extends keyof SignalREvents>(event: K, ...args: Parameters<SignalREvents[K]>): void {
    const listeners = this.eventListeners.get(event);
    if (listeners) {
      listeners.forEach(callback => {
        try {
          (callback as Function)(...args);
        } catch (error) {
          console.error(`Error in ${event} event listener:`, error);
        }
      });
    }
  }

  // Utility methods
  isConnected(): boolean {
    return this.connection?.state === HubConnectionState.Connected;
  }

  getConnectionState(): ConnectionState {
    return { ...this.connectionState };
  }

  getConnectionId(): string | null {
    return this.connection?.connectionId || null;
  }

  // Cleanup
  dispose(): void {
    this.stopConnection();
    this.eventListeners.clear();
    if (this.reconnectTimer) {
      clearTimeout(this.reconnectTimer);
    }
  }
}

// Create singleton instance
export const signalRService = new SignalRService();

// Export methods for easier importing
export const {
  startConnection,
  stopConnection,
  on: onSignalREvent,
  off: offSignalREvent,
  isConnected,
  getConnectionState,
  joinGroup,
  leaveGroup,
  requestSystemStatus,
  requestProcessList,
} = signalRService;

export default signalRService;