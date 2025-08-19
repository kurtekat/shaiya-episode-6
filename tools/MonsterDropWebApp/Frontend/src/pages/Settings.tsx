import React from 'react'
import { Box, Heading, Text, Alert, AlertIcon } from '@chakra-ui/react'

const Settings: React.FC = () => {
  return (
    <Box>
      <Heading size="lg" mb={4}>Settings</Heading>
      <Alert status="info">
        <AlertIcon />
        Settings page - Coming soon! This will allow configuring application preferences.
      </Alert>
    </Box>
  )
}

export default Settings