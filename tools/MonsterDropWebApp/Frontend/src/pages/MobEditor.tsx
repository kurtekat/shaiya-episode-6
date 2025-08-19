import React from 'react'
import { Box, Heading, Text, Alert, AlertIcon } from '@chakra-ui/react'

const MobEditor: React.FC = () => {
  return (
    <Box>
      <Heading size="lg" mb={4}>Monster Editor</Heading>
      <Alert status="info">
        <AlertIcon />
        Monster editor page - Coming soon! This will allow editing individual monster drop rates.
      </Alert>
    </Box>
  )
}

export default MobEditor