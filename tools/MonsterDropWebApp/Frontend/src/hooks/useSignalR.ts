import { useEffect, useRef, useCallback, useState } from 'react'
import { signalRService } from '@services/signalr'
import { ConnectionState, SignalREvents } from '@types/index'

export const useSignalR = () => {
  const [connectionState, setConnectionState] = useState<ConnectionState>({ status: 'disconnected' })
  const eventListenersRef = useRef<Map<keyof SignalREvents, Function[]>>(new Map())

  // Update connection state when it changes
  useEffect(() => {
    const updateConnectionState = () => {
      setConnectionState(signalRService.getConnectionState())
    }

    // Initial state
    updateConnectionState()

    // Listen for connection state changes
    signalRService.on('ConnectionStateChanged' as keyof SignalREvents, updateConnectionState as any)

    return () => {
      signalRService.off('ConnectionStateChanged' as keyof SignalREvents, updateConnectionState as any)
    }
  }, [])

  // Start connection
  const startConnection = useCallback(async () => {
    try {
      await signalRService.startConnection()
    } catch (error) {
      console.error('Failed to start SignalR connection:', error)
      throw error
    }
  }, [])

  // Stop connection
  const stopConnection = useCallback(async () => {
    try {
      await signalRService.stopConnection()
    } catch (error) {
      console.error('Failed to stop SignalR connection:', error)
      throw error
    }
  }, [])

  // Subscribe to SignalR events
  const onSignalREvent = useCallback(<K extends keyof SignalREvents>(
    event: K,
    callback: SignalREvents[K]
  ) => {
    // Add to local listeners map for cleanup
    if (!eventListenersRef.current.has(event)) {
      eventListenersRef.current.set(event, [])
    }
    eventListenersRef.current.get(event)!.push(callback)

    // Subscribe to SignalR service
    signalRService.on(event, callback)

    // Return unsubscribe function
    return () => {
      signalRService.off(event, callback)
      
      // Remove from local listeners
      const listeners = eventListenersRef.current.get(event)
      if (listeners) {
        const index = listeners.indexOf(callback)
        if (index > -1) {
          listeners.splice(index, 1)
        }
      }
    }
  }, [])

  // Unsubscribe from SignalR events
  const offSignalREvent = useCallback(<K extends keyof SignalREvents>(
    event: K,
    callback: SignalREvents[K]
  ) => {
    signalRService.off(event, callback)
    
    // Remove from local listeners
    const listeners = eventListenersRef.current.get(event)
    if (listeners) {
      const index = listeners.indexOf(callback)
      if (index > -1) {
        listeners.splice(index, 1)
      }
    }
  }, [])

  // Join group
  const joinGroup = useCallback(async (groupName: string) => {
    try {
      await signalRService.joinGroup(groupName)
    } catch (error) {
      console.error(`Failed to join group ${groupName}:`, error)
      throw error
    }
  }, [])

  // Leave group
  const leaveGroup = useCallback(async (groupName: string) => {
    try {
      await signalRService.leaveGroup(groupName)
    } catch (error) {
      console.error(`Failed to leave group ${groupName}:`, error)
      throw error
    }
  }, [])

  // Request system status
  const requestSystemStatus = useCallback(async () => {
    try {
      await signalRService.requestSystemStatus()
    } catch (error) {
      console.error('Failed to request system status:', error)
      throw error
    }
  }, [])

  // Request process list
  const requestProcessList = useCallback(async () => {
    try {
      await signalRService.requestProcessList()
    } catch (error) {
      console.error('Failed to request process list:', error)
      throw error
    }
  }, [])

  // Cleanup on unmount
  useEffect(() => {
    return () => {
      // Unsubscribe from all events
      eventListenersRef.current.forEach((listeners, event) => {
        listeners.forEach(callback => {
          signalRService.off(event, callback)
        })
      })
      eventListenersRef.current.clear()
    }
  }, [])

  return {
    // Connection management
    startConnection,
    stopConnection,
    
    // Connection state
    isConnected: connectionState.status === 'connected',
    connectionState,
    connectionId: signalRService.getConnectionId(),
    
    // Event subscription
    onSignalREvent,
    offSignalREvent,
    
    // Group management
    joinGroup,
    leaveGroup,
    
    // Server requests
    requestSystemStatus,
    requestProcessList,
  }
}

export default useSignalR