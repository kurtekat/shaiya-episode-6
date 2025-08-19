import React from 'react'
import { Box, Heading, Text, Alert, AlertIcon } from '@chakra-ui/react'

const MobList: React.FC = () => {
  return (
    <Box>
      <Heading size="lg" mb={4}>Monster List</Heading>
      <Alert status="info">
        <AlertIcon />
        Monster list page - Coming soon! This will show a table of all monsters with their drop rates.
      </Alert>
    </Box>
  )
}

export default MobList