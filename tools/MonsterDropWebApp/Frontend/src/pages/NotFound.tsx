import React from 'react'
import { 
  Box, 
  Heading, 
  Text, 
  Button, 
  VStack,
  Alert,
  AlertIcon
} from '@chakra-ui/react'
import { Link as RouterLink } from 'react-router-dom'

const NotFound: React.FC = () => {
  return (
    <VStack spacing={6} textAlign="center" py={10}>
      <Alert status="error" maxW="md" flexDirection="column" textAlign="center">
        <AlertIcon boxSize="40px" mr={0} />
        <Heading size="lg" mt={4} mb={1}>
          404 - Page Not Found
        </Heading>
        <Text>
          The page you're looking for doesn't exist.
        </Text>
      </Alert>
      
      <Button as={RouterLink} to="/" colorScheme="blue">
        Go to Dashboard
      </Button>
    </VStack>
  )
}

export default NotFound