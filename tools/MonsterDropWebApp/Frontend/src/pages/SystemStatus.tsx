import React from 'react'
import { Box, Heading, Text, Alert, AlertIcon } from '@chakra-ui/react'

const SystemStatus: React.FC = () => {
  return (
    <Box>
      <Heading size="lg" mb={4}>System Status</Heading>
      <Alert status="info">
        <AlertIcon />
        System status page - Coming soon! This will show detailed system information and process management.
      </Alert>
    </Box>
  )
}

export default SystemStatus