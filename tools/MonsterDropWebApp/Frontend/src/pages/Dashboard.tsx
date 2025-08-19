import React from 'react'
import {
  Box,
  Grid,
  Stat,
  StatLabel,
  StatNumber,
  StatHelpText,
  StatArrow,
  Card,
  CardBody,
  Heading,
  Text,
  VStack,
  HStack,
  Button,
  Alert,
  AlertIcon,
  AlertTitle,
  AlertDescription,
  Spinner,
  Badge,
  Progress,
} from '@chakra-ui/react'
import { useQuery } from 'react-query'
import { FiServer, FiDatabase, FiEdit, FiActivity } from 'react-icons/fi'
import { apiService } from '@services/api'
import { useSignalR } from '@hooks/useSignalR'

const Dashboard: React.FC = () => {
  const { isConnected } = useSignalR()
  
  const { data: systemStatus, isLoading: systemLoading } = useQuery(
    'systemStatus',
    () => apiService.getSystemStatus(),
    {
      refetchInterval: 5000, // Refresh every 5 seconds
      enabled: true,
    }
  )

  const { data: statistics, isLoading: statsLoading } = useQuery(
    'statistics', 
    () => apiService.getStatistics(),
    {
      refetchInterval: 10000, // Refresh every 10 seconds
      enabled: systemStatus?.isProcessAttached,
    }
  )

  const { data: processes } = useQuery(
    'processes',
    () => apiService.getProcesses(),
    {
      refetchInterval: 5000,
    }
  )

  if (systemLoading) {
    return (
      <VStack spacing={4} py={10}>
        <Spinner size="xl" />
        <Text>Loading dashboard...</Text>
      </VStack>
    )
  }

  return (
    <VStack spacing={6} align="stretch">
      {/* Page Header */}
      <Box>
        <Heading size="lg" mb={2}>Dashboard</Heading>
        <Text color="gray.600" _dark={{ color: 'gray.400' }}>
          Monitor your Shaiya Monster Drop Editor system status
        </Text>
      </Box>

      {/* Connection Status Alert */}
      {!isConnected && (
        <Alert status="warning">
          <AlertIcon />
          <AlertTitle>Connection Issue!</AlertTitle>
          <AlertDescription>
            Real-time updates are not available. Check your connection to the server.
          </AlertDescription>
        </Alert>
      )}

      {!systemStatus?.isProcessAttached && (
        <Alert status="info">
          <AlertIcon />
          <AlertTitle>No Process Attached</AlertTitle>
          <AlertDescription>
            Please attach to a Shaiya server process to start editing monster drops.
          </AlertDescription>
        </Alert>
      )}

      {/* System Overview Cards */}
      <Grid templateColumns={{ base: '1fr', md: 'repeat(2, 1fr)', lg: 'repeat(4, 1fr)' }} gap={6}>
        {/* Connection Status */}
        <Card>
          <CardBody>
            <Stat>
              <StatLabel>
                <HStack>
                  <FiServer />
                  <Text>Connection</Text>
                </HStack>
              </StatLabel>
              <StatNumber fontSize="2xl">
                <Badge 
                  colorScheme={isConnected ? 'green' : 'red'} 
                  fontSize="lg"
                  px={3}
                  py={1}
                >
                  {isConnected ? 'Online' : 'Offline'}
                </Badge>
              </StatNumber>
              <StatHelpText>
                SignalR Connection
              </StatHelpText>
            </Stat>
          </CardBody>
        </Card>

        {/* Process Status */}
        <Card>
          <CardBody>
            <Stat>
              <StatLabel>
                <HStack>
                  <FiActivity />
                  <Text>Process</Text>
                </HStack>
              </StatLabel>
              <StatNumber fontSize="2xl">
                {systemStatus?.isProcessAttached ? (
                  <Badge colorScheme="green" fontSize="lg" px={3} py={1}>
                    Attached
                  </Badge>
                ) : (
                  <Badge colorScheme="gray" fontSize="lg" px={3} py={1}>
                    None
                  </Badge>
                )}
              </StatNumber>
              <StatHelpText>
                {systemStatus?.processName || 'No process attached'}
              </StatHelpText>
            </Stat>
          </CardBody>
        </Card>

        {/* Monster Count */}
        <Card>
          <CardBody>
            <Stat>
              <StatLabel>
                <HStack>
                  <FiDatabase />
                  <Text>Monsters</Text>
                </HStack>
              </StatLabel>
              <StatNumber fontSize="2xl">
                {systemStatus?.mobCount || 0}
              </StatNumber>
              <StatHelpText>
                Found in memory
              </StatHelpText>
            </Stat>
          </CardBody>
        </Card>

        {/* Modified Count */}
        <Card>
          <CardBody>
            <Stat>
              <StatLabel>
                <HStack>
                  <FiEdit />
                  <Text>Modified</Text>
                </HStack>
              </StatLabel>
              <StatNumber fontSize="2xl" color="orange.500">
                {systemStatus?.modifiedMobCount || 0}
              </StatNumber>
              <StatHelpText>
                <StatArrow type={systemStatus?.hasUnsavedChanges ? 'increase' : undefined} />
                {systemStatus?.hasUnsavedChanges ? 'Unsaved changes' : 'All saved'}
              </StatHelpText>
            </Stat>
          </CardBody>
        </Card>
      </Grid>

      {/* Detailed Information */}
      <Grid templateColumns={{ base: '1fr', lg: 'repeat(2, 1fr)' }} gap={6}>
        {/* System Information */}
        <Card>
          <CardBody>
            <VStack align="stretch" spacing={4}>
              <Heading size="md">System Information</Heading>
              
              {systemStatus?.isProcessAttached ? (
                <VStack align="stretch" spacing={3}>
                  <HStack justify="space-between">
                    <Text>Process Name:</Text>
                    <Badge>{systemStatus.processName}</Badge>
                  </HStack>
                  <HStack justify="space-between">
                    <Text>Process ID:</Text>
                    <Text fontFamily="mono">{systemStatus.processId}</Text>
                  </HStack>
                  <HStack justify="space-between">
                    <Text>Last Scan:</Text>
                    <Text fontSize="sm">
                      {systemStatus.lastScanTime 
                        ? new Date(systemStatus.lastScanTime).toLocaleString()
                        : 'Never'
                      }
                    </Text>
                  </HStack>
                  <HStack justify="space-between">
                    <Text>Unsaved Changes:</Text>
                    <Badge colorScheme={systemStatus.hasUnsavedChanges ? 'orange' : 'green'}>
                      {systemStatus.hasUnsavedChanges ? 'Yes' : 'No'}
                    </Badge>
                  </HStack>
                </VStack>
              ) : (
                <Text color="gray.500" textAlign="center" py={4}>
                  No process information available
                </Text>
              )}
            </VStack>
          </CardBody>
        </Card>

        {/* Available Processes */}
        <Card>
          <CardBody>
            <VStack align="stretch" spacing={4}>
              <Heading size="md">Available Processes</Heading>
              
              {processes && processes.length > 0 ? (
                <VStack align="stretch" spacing={2}>
                  {processes.slice(0, 5).map((process) => (
                    <HStack key={process.id} justify="space-between" p={2} bg="gray.50" _dark={{ bg: 'gray.700' }} rounded="md">
                      <VStack align="start" spacing={0}>
                        <Text fontWeight="medium">{process.name}</Text>
                        <Text fontSize="sm" color="gray.500">PID: {process.id}</Text>
                      </VStack>
                      <Badge colorScheme={process.isAttached ? 'green' : 'gray'}>
                        {process.isAttached ? 'Attached' : process.status}
                      </Badge>
                    </HStack>
                  ))}
                  
                  {processes.length > 5 && (
                    <Text fontSize="sm" color="gray.500" textAlign="center">
                      ... and {processes.length - 5} more
                    </Text>
                  )}
                </VStack>
              ) : (
                <Text color="gray.500" textAlign="center" py={4}>
                  No Shaiya processes found
                </Text>
              )}
            </VStack>
          </CardBody>
        </Card>
      </Grid>

      {/* Statistics */}
      {statistics && (
        <Card>
          <CardBody>
            <VStack align="stretch" spacing={4}>
              <Heading size="md">Statistics</Heading>
              
              {statsLoading ? (
                <HStack justify="center" py={4}>
                  <Spinner />
                  <Text>Loading statistics...</Text>
                </HStack>
              ) : (
                <Grid templateColumns={{ base: '1fr', md: 'repeat(2, 1fr)' }} gap={6}>
                  {/* Monsters by Level */}
                  <Box>
                    <Text fontWeight="medium" mb={3}>Monsters by Level Range</Text>
                    <VStack align="stretch" spacing={2}>
                      {Object.entries(statistics.mobsByLevel).map(([range, count]) => (
                        <HStack key={range} justify="space-between">
                          <Text fontSize="sm">{range}</Text>
                          <HStack>
                            <Progress value={(count / statistics.totalMobs) * 100} size="sm" width="60px" />
                            <Text fontSize="sm" minW="30px">{count}</Text>
                          </HStack>
                        </HStack>
                      ))}
                    </VStack>
                  </Box>

                  {/* Drops by Grade */}
                  <Box>
                    <Text fontWeight="medium" mb={3}>Active Drops by Grade</Text>
                    <VStack align="stretch" spacing={2}>
                      {Object.entries(statistics.dropsByGrade).slice(0, 10).map(([grade, count]) => (
                        <HStack key={grade} justify="space-between">
                          <Text fontSize="sm">{grade}</Text>
                          <HStack>
                            <Progress 
                              value={(count / Object.values(statistics.dropsByGrade).reduce((a, b) => a + b, 0)) * 100} 
                              size="sm" 
                              width="60px" 
                            />
                            <Text fontSize="sm" minW="30px">{count}</Text>
                          </HStack>
                        </HStack>
                      ))}
                    </VStack>
                  </Box>
                </Grid>
              )}
            </VStack>
          </CardBody>
        </Card>
      )}
    </VStack>
  )
}

export default Dashboard