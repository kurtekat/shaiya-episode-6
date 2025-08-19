import { extendTheme, type ThemeConfig } from '@chakra-ui/react'

// Color mode config
const config: ThemeConfig = {
  initialColorMode: 'dark',
  useSystemColorMode: true,
}

// Custom colors
const colors = {
  brand: {
    50: '#E3F2FD',
    100: '#BBDEFB',
    200: '#90CAF9',
    300: '#64B5F6',
    400: '#42A5F5',
    500: '#2196F3',
    600: '#1E88E5',
    700: '#1976D2',
    800: '#1565C0',
    900: '#0D47A1',
  },
  shaiya: {
    50: '#F0F4FF',
    100: '#D9E2FF',
    200: '#B3C6FF',
    300: '#8AA9FF',
    400: '#618DFF',
    500: '#3970FF', // Primary Shaiya blue
    600: '#2E5BFF',
    700: '#1E47FF',
    800: '#0F33FF',
    900: '#001FFF',
  },
  success: {
    50: '#F0FFF4',
    100: '#C6F6D5',
    200: '#9AE6B4',
    300: '#68D391',
    400: '#48BB78',
    500: '#38A169',
    600: '#2F855A',
    700: '#276749',
    800: '#22543D',
    900: '#1C4532',
  },
  warning: {
    50: '#FFFBEB',
    100: '#FEF3C7',
    200: '#FDE68A',
    300: '#FCD34D',
    400: '#FBBF24',
    500: '#F59E0B',
    600: '#D97706',
    700: '#B45309',
    800: '#92400E',
    900: '#78350F',
  },
  danger: {
    50: '#FEF2F2',
    100: '#FEE2E2',
    200: '#FECACA',
    300: '#FCA5A5',
    400: '#F87171',
    500: '#EF4444',
    600: '#DC2626',
    700: '#B91C1C',
    800: '#991B1B',
    900: '#7F1D1D',
  },
}

// Typography
const fonts = {
  heading: "'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', Helvetica, Arial, sans-serif",
  body: "'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', Helvetica, Arial, sans-serif",
  mono: "'JetBrains Mono', 'Fira Code', 'Consolas', monospace",
}

// Global styles
const styles = {
  global: (props: any) => ({
    body: {
      bg: props.colorMode === 'dark' ? 'gray.900' : 'gray.50',
      color: props.colorMode === 'dark' ? 'gray.100' : 'gray.900',
    },
    '*': {
      borderColor: props.colorMode === 'dark' ? 'gray.700' : 'gray.200',
    },
    '::-webkit-scrollbar': {
      width: '8px',
    },
    '::-webkit-scrollbar-track': {
      bg: props.colorMode === 'dark' ? 'gray.800' : 'gray.100',
    },
    '::-webkit-scrollbar-thumb': {
      bg: props.colorMode === 'dark' ? 'gray.600' : 'gray.400',
      borderRadius: '4px',
    },
    '::-webkit-scrollbar-thumb:hover': {
      bg: props.colorMode === 'dark' ? 'gray.500' : 'gray.500',
    },
  }),
}

// Component overrides
const components = {
  Button: {
    defaultProps: {
      colorScheme: 'shaiya',
    },
    variants: {
      solid: (props: any) => ({
        bg: props.colorMode === 'dark' ? 'shaiya.600' : 'shaiya.500',
        color: 'white',
        _hover: {
          bg: props.colorMode === 'dark' ? 'shaiya.500' : 'shaiya.600',
          _disabled: {
            bg: props.colorMode === 'dark' ? 'shaiya.600' : 'shaiya.500',
          },
        },
        _active: {
          bg: props.colorMode === 'dark' ? 'shaiya.700' : 'shaiya.700',
        },
      }),
      ghost: (props: any) => ({
        color: props.colorMode === 'dark' ? 'shaiya.300' : 'shaiya.600',
        _hover: {
          bg: props.colorMode === 'dark' ? 'shaiya.800' : 'shaiya.50',
        },
        _active: {
          bg: props.colorMode === 'dark' ? 'shaiya.700' : 'shaiya.100',
        },
      }),
    },
  },
  Card: {
    baseStyle: (props: any) => ({
      container: {
        bg: props.colorMode === 'dark' ? 'gray.800' : 'white',
        borderColor: props.colorMode === 'dark' ? 'gray.700' : 'gray.200',
        shadow: props.colorMode === 'dark' ? 'dark-lg' : 'lg',
      },
    }),
  },
  Table: {
    variants: {
      simple: (props: any) => ({
        th: {
          borderColor: props.colorMode === 'dark' ? 'gray.600' : 'gray.200',
          color: props.colorMode === 'dark' ? 'gray.400' : 'gray.600',
          textTransform: 'uppercase',
          letterSpacing: 'wider',
          fontSize: 'xs',
          fontWeight: 'bold',
        },
        td: {
          borderColor: props.colorMode === 'dark' ? 'gray.700' : 'gray.200',
        },
        tbody: {
          tr: {
            _hover: {
              bg: props.colorMode === 'dark' ? 'gray.700' : 'gray.50',
            },
          },
        },
      }),
    },
  },
  Modal: {
    baseStyle: (props: any) => ({
      dialog: {
        bg: props.colorMode === 'dark' ? 'gray.800' : 'white',
      },
      overlay: {
        bg: 'blackAlpha.600',
      },
    }),
  },
  Input: {
    variants: {
      filled: (props: any) => ({
        field: {
          bg: props.colorMode === 'dark' ? 'gray.700' : 'gray.100',
          _hover: {
            bg: props.colorMode === 'dark' ? 'gray.600' : 'gray.200',
          },
          _focus: {
            bg: props.colorMode === 'dark' ? 'gray.600' : 'gray.200',
            borderColor: 'shaiya.500',
          },
        },
      }),
    },
  },
  Select: {
    variants: {
      filled: (props: any) => ({
        field: {
          bg: props.colorMode === 'dark' ? 'gray.700' : 'gray.100',
          _hover: {
            bg: props.colorMode === 'dark' ? 'gray.600' : 'gray.200',
          },
          _focus: {
            bg: props.colorMode === 'dark' ? 'gray.600' : 'gray.200',
            borderColor: 'shaiya.500',
          },
        },
      }),
    },
  },
  Badge: {
    variants: {
      solid: (props: any) => {
        const { colorScheme } = props
        return {
          bg: `${colorScheme}.500`,
          color: 'white',
        }
      },
      subtle: (props: any) => {
        const { colorScheme } = props
        return {
          bg: props.colorMode === 'dark' ? `${colorScheme}.800` : `${colorScheme}.100`,
          color: props.colorMode === 'dark' ? `${colorScheme}.200` : `${colorScheme}.800`,
        }
      },
    },
  },
}

// Breakpoints
const breakpoints = {
  base: '0em',
  sm: '30em',   // 480px
  md: '48em',   // 768px
  lg: '62em',   // 992px
  xl: '80em',   // 1280px
  '2xl': '96em', // 1536px
}

// Create theme
const theme = extendTheme({
  config,
  colors,
  fonts,
  styles,
  components,
  breakpoints,
  shadows: {
    'dark-lg': '0 10px 15px -3px rgba(0, 0, 0, 0.3), 0 4px 6px -2px rgba(0, 0, 0, 0.2)',
  },
})

export default theme