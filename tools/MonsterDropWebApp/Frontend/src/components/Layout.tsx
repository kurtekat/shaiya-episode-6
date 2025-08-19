import React from 'react'
import {
  Box,
  Flex,
  HStack,
  VStack,
  Text,
  Button,
  useColorMode,
  useColorModeValue,
  IconButton,
  Menu,
  MenuButton,
  MenuList,
  MenuItem,
  Badge,
  Container,
  Divider,
} from '@chakra-ui/react'
import { Link as RouterLink, useLocation } from 'react-router-dom'
import { 
  FiHome, 
  FiList, 
  FiSettings, 
  FiActivity, 
  FiMoon, 
  FiSun,
  FiMenu,
  FiWifi,
  FiWifiOff
} from 'react-icons/fi'
import { useSignalR } from '@hooks/useSignalR'
import { BaseComponentProps } from '@types/index'

interface LayoutProps extends BaseComponentProps {}

export const Layout: React.FC<LayoutProps> = ({ children }) => {
  const { colorMode, toggleColorMode } = useColorMode()
  const { isConnected, connectionState } = useSignalR()
  const location = useLocation()
  
  const bg = useColorModeValue('white', 'gray.800')
  const borderColor = useColorModeValue('gray.200', 'gray.700')
  
  const navigationItems = [
    { path: '/', label: 'Dashboard', icon: FiHome },
    { path: '/mobs', label: 'Monsters', icon: FiList },
    { path: '/system', label: 'System', icon: FiActivity },
    { path: '/settings', label: 'Settings', icon: FiSettings },
  ]

  const getConnectionStatus = () => {
    switch (connectionState.status) {
      case 'connected':
        return { color: 'green', text: 'Connected' }
      case 'connecting':
        return { color: 'yellow', text: 'Connecting...' }
      case 'reconnecting':
        return { color: 'orange', text: 'Reconnecting...' }
      case 'disconnected':
        return { color: 'red', text: 'Disconnected' }
      case 'error':
        return { color: 'red', text: 'Connection Error' }
      default:
        return { color: 'gray', text: 'Unknown' }
    }
  }

  const connectionStatus = getConnectionStatus()

  return (
    <Flex minH="100vh" direction="column">
      {/* Header */}
      <Box
        bg={bg}
        borderBottom="1px"
        borderColor={borderColor}
        shadow="sm"
        position="sticky"
        top={0}
        zIndex={10}
      >
        <Container maxW="container.xl">
          <Flex h="16" alignItems="center" justifyContent="space-between">
            {/* Logo */}
            <HStack spacing={4}>
              <Text
                fontSize="xl"
                fontWeight="bold"
                bgGradient="linear(to-r, shaiya.500, purple.500)"
                bgClip="text"
              >
                Shaiya Drop Editor
              </Text>
              <Badge 
                colorScheme={connectionStatus.color} 
                variant="subtle"
                display={{ base: 'none', md: 'inline-flex' }}
              >
                <HStack spacing={1}>
                  {isConnected ? <FiWifi /> : <FiWifiOff />}
                  <Text>{connectionStatus.text}</Text>
                </HStack>
              </Badge>
            </HStack>

            {/* Desktop Navigation */}
            <HStack spacing={1} display={{ base: 'none', md: 'flex' }}>
              {navigationItems.map((item) => (
                <Button
                  key={item.path}
                  as={RouterLink}
                  to={item.path}
                  variant={location.pathname === item.path ? 'solid' : 'ghost'}
                  leftIcon={<item.icon />}
                  size="sm"
                >
                  {item.label}
                </Button>
              ))}
            </HStack>

            {/* Actions */}
            <HStack spacing={2}>
              <IconButton
                aria-label="Toggle color mode"
                icon={colorMode === 'light' ? <FiMoon /> : <FiSun />}
                variant="ghost"
                onClick={toggleColorMode}
              />
              
              {/* Mobile Menu */}
              <Menu>
                <MenuButton
                  as={IconButton}
                  aria-label="Navigation menu"
                  icon={<FiMenu />}
                  variant="ghost"
                  display={{ base: 'flex', md: 'none' }}
                />
                <MenuList>
                  {navigationItems.map((item) => (
                    <MenuItem
                      key={item.path}
                      as={RouterLink}
                      to={item.path}
                      icon={<item.icon />}
                    >
                      {item.label}
                    </MenuItem>
                  ))}
                  <Divider />
                  <MenuItem icon={isConnected ? <FiWifi /> : <FiWifiOff />}>
                    {connectionStatus.text}
                  </MenuItem>
                </MenuList>
              </Menu>
            </HStack>
          </Flex>
        </Container>
      </Box>

      {/* Main Content */}
      <Box flex={1}>
        <Container maxW="container.xl" py={6}>
          {children}
        </Container>
      </Box>

      {/* Footer */}
      <Box
        bg={bg}
        borderTop="1px"
        borderColor={borderColor}
        py={4}
      >
        <Container maxW="container.xl">
          <Flex
            direction={{ base: 'column', md: 'row' }}
            alignItems="center"
            justifyContent="space-between"
            textAlign={{ base: 'center', md: 'left' }}
          >
            <Text fontSize="sm" color="gray.600" _dark={{ color: 'gray.400' }}>
              © 2025 Shaiya Community • Monster Drop Editor v1.0
            </Text>
            <HStack spacing={4} mt={{ base: 2, md: 0 }}>
              <Text fontSize="xs" color="gray.500">
                Built with ❤️ for the Shaiya community
              </Text>
            </HStack>
          </Flex>
        </Container>
      </Box>
    </Flex>
  )
}