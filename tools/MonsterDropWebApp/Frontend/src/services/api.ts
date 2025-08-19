import axios, { AxiosInstance, AxiosResponse } from 'axios';
import {
  ApiResponse,
  MobInfoDto,
  PagedResponse,
  MobSearchRequest,
  UpdateDropRequest,
  MassEditRequest,
  SystemStatusDto,
  ProcessInfoDto,
  DashboardStatsDto,
  ExportRequest,
} from '@types/index';

class ApiService {
  private api: AxiosInstance;

  constructor() {
    this.api = axios.create({
      baseURL: '/api',
      timeout: 30000,
      headers: {
        'Content-Type': 'application/json',
      },
    });

    // Request interceptor
    this.api.interceptors.request.use(
      (config) => {
        // Add timestamp to prevent caching
        if (config.method === 'get') {
          config.params = {
            ...config.params,
            _t: Date.now(),
          };
        }
        
        console.log(`🔄 API Request: ${config.method?.toUpperCase()} ${config.url}`);
        return config;
      },
      (error) => {
        console.error('❌ API Request Error:', error);
        return Promise.reject(error);
      }
    );

    // Response interceptor
    this.api.interceptors.response.use(
      (response) => {
        console.log(`✅ API Response: ${response.status} ${response.config.url}`);
        return response;
      },
      (error) => {
        console.error('❌ API Response Error:', error);
        
        if (error.response) {
          // Server responded with error
          const message = error.response.data?.message || 'Server error occurred';
          throw new Error(message);
        } else if (error.request) {
          // Request was made but no response
          throw new Error('No response from server. Please check your connection.');
        } else {
          // Something else happened
          throw new Error(error.message || 'An unexpected error occurred');
        }
      }
    );
  }

  // Helper method to extract data from API response
  private extractData<T>(response: AxiosResponse<ApiResponse<T>>): T {
    if (!response.data.success) {
      throw new Error(response.data.message || 'API request failed');
    }
    
    if (response.data.data === undefined) {
      throw new Error('No data received from API');
    }
    
    return response.data.data;
  }

  // System endpoints
  async getSystemStatus(): Promise<SystemStatusDto> {
    const response = await this.api.get<ApiResponse<SystemStatusDto>>('/system/status');
    return this.extractData(response);
  }

  async getProcesses(): Promise<ProcessInfoDto[]> {
    const response = await this.api.get<ApiResponse<ProcessInfoDto[]>>('/system/processes');
    return this.extractData(response);
  }

  async attachToProcess(processId: number): Promise<SystemStatusDto> {
    const response = await this.api.post<ApiResponse<SystemStatusDto>>(`/system/attach/${processId}`);
    return this.extractData(response);
  }

  async detachFromProcess(): Promise<SystemStatusDto> {
    const response = await this.api.post<ApiResponse<SystemStatusDto>>('/system/detach');
    return this.extractData(response);
  }

  async scanForMobs(): Promise<MobInfoDto[]> {
    const response = await this.api.post<ApiResponse<MobInfoDto[]>>('/system/scan');
    return this.extractData(response);
  }

  async saveChanges(): Promise<number> {
    const response = await this.api.post<ApiResponse<number>>('/system/save');
    return this.extractData(response);
  }

  async exportData(request: ExportRequest): Promise<Blob> {
    const response = await this.api.post('/system/export', request, {
      responseType: 'blob',
    });
    return response.data;
  }

  async healthCheck(): Promise<any> {
    const response = await this.api.get('/system/health');
    return response.data;
  }

  // Mob endpoints
  async getMobs(request: MobSearchRequest): Promise<PagedResponse<MobInfoDto>> {
    const response = await this.api.get<ApiResponse<PagedResponse<MobInfoDto>>>('/mob', {
      params: request,
    });
    return this.extractData(response);
  }

  async getMob(mobId: number): Promise<MobInfoDto> {
    const response = await this.api.get<ApiResponse<MobInfoDto>>(`/mob/${mobId}`);
    return this.extractData(response);
  }

  async updateDrop(request: UpdateDropRequest): Promise<MobInfoDto> {
    const response = await this.api.put<ApiResponse<MobInfoDto>>(
      `/mob/${request.mobId}/drops/${request.dropIndex}`,
      request
    );
    return this.extractData(response);
  }

  async applyMassEdit(request: MassEditRequest): Promise<number> {
    const response = await this.api.post<ApiResponse<number>>('/mob/mass-edit', request);
    return this.extractData(response);
  }

  async resetMob(mobId: number): Promise<MobInfoDto> {
    const response = await this.api.post<ApiResponse<MobInfoDto>>(`/mob/${mobId}/reset`);
    return this.extractData(response);
  }

  async getStatistics(): Promise<DashboardStatsDto> {
    const response = await this.api.get<ApiResponse<DashboardStatsDto>>('/mob/statistics');
    return this.extractData(response);
  }

  // Utility methods
  async ping(): Promise<boolean> {
    try {
      await this.healthCheck();
      return true;
    } catch {
      return false;
    }
  }

  // Download file helper
  downloadFile(blob: Blob, filename: string): void {
    const url = window.URL.createObjectURL(blob);
    const link = document.createElement('a');
    link.href = url;
    link.download = filename;
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
    window.URL.revokeObjectURL(url);
  }

  // Get API base URL for external use
  getBaseUrl(): string {
    return this.api.defaults.baseURL || '/api';
  }

  // Cancel all pending requests
  cancelAllRequests(): void {
    // This is a simplified version - in production you might want to track
    // individual request tokens for more granular control
    console.log('Cancelling all API requests...');
  }
}

// Create singleton instance
export const apiService = new ApiService();

// Export individual methods for easier importing
export const {
  getSystemStatus,
  getProcesses,
  attachToProcess,
  detachFromProcess,
  scanForMobs,
  saveChanges,
  exportData,
  healthCheck,
  getMobs,
  getMob,
  updateDrop,
  applyMassEdit,
  resetMob,
  getStatistics,
  ping,
  downloadFile,
} = apiService;

export default apiService;