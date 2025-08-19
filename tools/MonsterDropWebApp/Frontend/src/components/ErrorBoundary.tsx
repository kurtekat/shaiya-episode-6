import React from 'react'
import { 
  Box, 
  Button, 
  Heading, 
  Text, 
  VStack, 
  Alert, 
  AlertIcon, 
  AlertTitle, 
  AlertDescription 
} from '@chakra-ui/react'
import { ErrorBoundaryState } from '@types/index'

interface Props {
  children: React.ReactNode
}

export class ErrorBoundary extends React.Component<Props, ErrorBoundaryState> {
  constructor(props: Props) {
    super(props)
    this.state = { hasError: false }
  }

  static getDerivedStateFromError(error: Error): ErrorBoundaryState {
    return { 
      hasError: true, 
      error 
    }
  }

  componentDidCatch(error: Error, errorInfo: React.ErrorInfo) {
    console.error('Error caught by boundary:', error, errorInfo)
    this.setState({ 
      hasError: true, 
      error, 
      errorInfo 
    })
  }

  handleReset = () => {
    this.setState({ hasError: false, error: undefined, errorInfo: undefined })
  }

  render() {
    if (this.state.hasError) {
      return (
        <Box 
          minH="100vh" 
          display="flex" 
          alignItems="center" 
          justifyContent="center"
          bg="gray.50"
          _dark={{ bg: 'gray.900' }}
          p={4}
        >
          <VStack spacing={6} maxW="md" textAlign="center">
            <Alert status="error" flexDirection="column" textAlign="center" rounded="lg">
              <AlertIcon boxSize="40px" mr={0} />
              <AlertTitle mt={4} mb={1} fontSize="lg">
                Something went wrong!
              </AlertTitle>
              <AlertDescription>
                The application encountered an unexpected error.
              </AlertDescription>
            </Alert>

            <VStack spacing={4}>
              <Heading size="md" color="gray.600" _dark={{ color: 'gray.400' }}>
                Monster Drop Editor Error
              </Heading>
              
              {this.state.error && (
                <Text fontSize="sm" color="gray.500" fontFamily="mono">
                  {this.state.error.message}
                </Text>
              )}

              <Button onClick={this.handleReset} colorScheme="blue">
                Try Again
              </Button>
              
              <Button 
                variant="ghost" 
                size="sm"
                onClick={() => window.location.reload()}
              >
                Reload Page
              </Button>
            </VStack>

            {import.meta.env.DEV && this.state.errorInfo && (
              <Box 
                as="details" 
                w="full" 
                bg="gray.100" 
                _dark={{ bg: 'gray.800' }} 
                p={4} 
                rounded="md"
                fontSize="xs"
              >
                <Text as="summary" cursor="pointer" fontWeight="bold">
                  Error Details (Development Only)
                </Text>
                <Text 
                  as="pre" 
                  mt={2} 
                  fontFamily="mono" 
                  fontSize="xs" 
                  whiteSpace="pre-wrap"
                  color="gray.600"
                  _dark={{ color: 'gray.400' }}
                >
                  {this.state.error?.stack}
                  {'\n\n'}
                  {this.state.errorInfo.componentStack}
                </Text>
              </Box>
            )}
          </VStack>
        </Box>
      )
    }

    return this.props.children
  }
}