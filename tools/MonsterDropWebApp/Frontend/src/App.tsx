import React, { useEffect } from 'react'
import { Routes, Route } from 'react-router-dom'
import { Box, useToast } from '@chakra-ui/react'

import { Layout } from '@components/Layout'
import { useSignalR } from '@hooks/useSignalR'
import { NotificationDto } from '@types/index'

// Pages
import Dashboard from '@pages/Dashboard'
import MobList from '@pages/MobList'
import MobEditor from '@pages/MobEditor'
import SystemStatus from '@pages/SystemStatus'
import Settings from '@pages/Settings'
import NotFound from '@pages/NotFound'

function App() {
  const toast = useToast()
  const { startConnection, isConnected, onSignalREvent } = useSignalR()

  useEffect(() => {
    // Start SignalR connection when app loads
    startConnection().catch(error => {
      console.error('Failed to start SignalR connection:', error)
      toast({
        title: 'Connection Error',
        description: 'Failed to connect to the server. Some features may not work properly.',
        status: 'warning',
        duration: 6000,
        isClosable: true,
      })
    })

    // Handle notifications from server
    const handleNotification = (notification: NotificationDto) => {
      toast({
        title: notification.title,
        description: notification.message,
        status: notification.type === 'error' ? 'error' : 
               notification.type === 'warning' ? 'warning' :
               notification.type === 'success' ? 'success' : 'info',
        duration: notification.type === 'error' ? 8000 : 5000,
        isClosable: true,
      })
    }

    onSignalREvent('Notification', handleNotification)

    // Handle connection state changes
    const handleConnectionStateChange = (state: any) => {
      if (state.status === 'connected' && !isConnected) {
        toast({
          title: 'Connected',
          description: 'Successfully connected to the server',
          status: 'success',
          duration: 3000,
          isClosable: true,
        })
      } else if (state.status === 'disconnected' && isConnected) {
        toast({
          title: 'Disconnected',
          description: 'Lost connection to the server',
          status: 'error',
          duration: 5000,
          isClosable: true,
        })
      } else if (state.status === 'reconnecting') {
        toast({
          title: 'Reconnecting',
          description: 'Attempting to reconnect to the server...',
          status: 'info',
          duration: 3000,
          isClosable: true,
        })
      }
    }

    onSignalREvent('ConnectionStateChanged' as any, handleConnectionStateChange)
  }, [startConnection, toast, isConnected, onSignalREvent])

  return (
    <Box minH="100vh" bg="gray.50" _dark={{ bg: 'gray.900' }}>
      <Layout>
        <Routes>
          <Route path="/" element={<Dashboard />} />
          <Route path="/dashboard" element={<Dashboard />} />
          <Route path="/mobs" element={<MobList />} />
          <Route path="/mobs/:mobId" element={<MobEditor />} />
          <Route path="/system" element={<SystemStatus />} />
          <Route path="/settings" element={<Settings />} />
          <Route path="*" element={<NotFound />} />
        </Routes>
      </Layout>
    </Box>
  )
}

export default App