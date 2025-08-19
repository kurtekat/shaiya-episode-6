import React from 'react'
import ReactDOM from 'react-dom/client'
import { ChakraProvider, ColorModeScript } from '@chakra-ui/react'
import { QueryClient, QueryClientProvider } from 'react-query'
import { ReactQueryDevtools } from 'react-query/devtools'
import { BrowserRouter } from 'react-router-dom'
import { Toaster } from 'react-hot-toast'

import App from './App'
import theme from './theme'
import { ErrorBoundary } from '@components/ErrorBoundary'

// Configure React Query
const queryClient = new QueryClient({
  defaultOptions: {
    queries: {
      retry: 3,
      retryDelay: (attemptIndex) => Math.min(1000 * 2 ** attemptIndex, 30000),
      staleTime: 5 * 60 * 1000, // 5 minutes
      cacheTime: 10 * 60 * 1000, // 10 minutes
      refetchOnWindowFocus: false,
      refetchOnReconnect: true,
    },
    mutations: {
      retry: 1,
    },
  },
})

// Remove loading screen
const removeLoadingScreen = () => {
  const loading = document.getElementById('loading')
  if (loading) {
    loading.style.opacity = '0'
    loading.style.transition = 'opacity 0.5s ease-out'
    setTimeout(() => loading.remove(), 500)
  }
}

// Initialize app
const root = ReactDOM.createRoot(document.getElementById('root') as HTMLElement)

root.render(
  <React.StrictMode>
    <ColorModeScript initialColorMode={theme.config.initialColorMode} />
    <ChakraProvider theme={theme}>
      <QueryClientProvider client={queryClient}>
        <BrowserRouter>
          <ErrorBoundary>
            <App />
            <Toaster
              position="top-right"
              toastOptions={{
                duration: 4000,
                style: {
                  background: '#2D3748',
                  color: '#F7FAFC',
                  borderRadius: '8px',
                  border: '1px solid #4A5568',
                },
                success: {
                  iconTheme: {
                    primary: '#48BB78',
                    secondary: '#F7FAFC',
                  },
                },
                error: {
                  iconTheme: {
                    primary: '#F56565',
                    secondary: '#F7FAFC',
                  },
                },
              }}
            />
          </ErrorBoundary>
        </BrowserRouter>
        {import.meta.env.DEV && <ReactQueryDevtools initialIsOpen={false} />}
      </QueryClientProvider>
    </ChakraProvider>
  </React.StrictMode>
)

// Remove loading screen after a short delay
setTimeout(removeLoadingScreen, 1000)

// Service Worker registration for PWA support
if ('serviceWorker' in navigator && import.meta.env.PROD) {
  window.addEventListener('load', () => {
    navigator.serviceWorker
      .register('/sw.js')
      .then((registration) => {
        console.log('SW registered: ', registration)
      })
      .catch((registrationError) => {
        console.log('SW registration failed: ', registrationError)
      })
  })
}