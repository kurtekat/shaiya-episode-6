// API Types matching the backend models

export interface DropInfoDto {
  index: number;
  grade: number;
  rate: number;
  percentage: string;
  isActive: boolean;
  color: string;
}

export interface MobInfoDto {
  mobId: number;
  mobName: string;
  level: number;
  exp: number;
  health: number;
  money: number;
  moneyAdd: number;
  isModified: boolean;
  displayName: string;
  dropInfo: DropInfoDto[];
  lastModified: string;
  modifiedBy: string;
}

export interface UpdateDropRequest {
  mobId: number;
  dropIndex: number;
  grade: number;
  rate: number;
}

export interface MassEditRequest {
  mobIds: number[];
  fromGrade?: number;
  toGrade?: number;
  newRate: number;
  applyToAllGrades: boolean;
  modifiedBy?: string;
}

export interface ProcessInfoDto {
  name: string;
  id: number;
  isAttached: boolean;
  lastSeen: string;
  status: string;
}

export interface SystemStatusDto {
  isProcessAttached: boolean;
  processName: string;
  processId: number;
  mobCount: number;
  modifiedMobCount: number;
  lastScanTime: string;
  recentActions: string[];
  hasUnsavedChanges: boolean;
}

export interface MobSearchRequest {
  searchTerm?: string;
  minLevel?: number;
  maxLevel?: number;
  modifiedOnly?: boolean;
  page: number;
  pageSize: number;
  sortBy: string;
  sortDescending: boolean;
}

export interface PagedResponse<T> {
  data: T[];
  totalCount: number;
  page: number;
  pageSize: number;
  totalPages: number;
  hasNextPage: boolean;
  hasPreviousPage: boolean;
}

export interface ApiResponse<T> {
  success: boolean;
  data?: T;
  message: string;
  errors: string[];
  timestamp: string;
}

export interface NotificationDto {
  type: 'info' | 'warning' | 'error' | 'success';
  title: string;
  message: string;
  timestamp: string;
  data?: any;
}

export interface DashboardStatsDto {
  totalMobs: number;
  modifiedMobs: number;
  activeProcesses: number;
  lastScanTime: string;
  uptime: string;
  recentActivity: RecentActivityDto[];
  mobsByLevel: Record<string, number>;
  dropsByGrade: Record<string, number>;
}

export interface RecentActivityDto {
  action: string;
  details: string;
  timestamp: string;
  user: string;
}

export interface ExportRequest {
  mobIds?: number[];
  exportAll: boolean;
  format: 'json' | 'csv';
  includeOriginalValues: boolean;
}

// UI State Types
export interface AppState {
  isConnected: boolean;
  systemStatus: SystemStatusDto | null;
  selectedMobs: number[];
  isLoading: boolean;
  error: string | null;
}

export interface MobFilters {
  searchTerm: string;
  minLevel: number | null;
  maxLevel: number | null;
  modifiedOnly: boolean;
  sortBy: string;
  sortOrder: 'asc' | 'desc';
}

export interface MassEditFormData {
  targetMobs: 'selected' | 'all' | 'filtered';
  editType: 'specific-grades' | 'all-drops';
  fromGrade: number;
  toGrade: number;
  newRate: number;
}

export interface ConnectionState {
  status: 'disconnected' | 'connecting' | 'connected' | 'reconnecting' | 'error';
  lastConnected?: Date;
  errorMessage?: string;
}

// Table column definitions
export interface TableColumn<T = any> {
  id: keyof T | string;
  header: string;
  accessorKey?: keyof T;
  cell?: (props: { row: { original: T } }) => React.ReactNode;
  sortable?: boolean;
  width?: string | number;
  minWidth?: number;
  maxWidth?: number;
}

// Form validation schemas
export interface DropEditFormData {
  grade: number;
  rate: number;
}

export interface ProcessConnectionFormData {
  processId: number;
}

// Theme and UI types
export interface ThemeColors {
  primary: string;
  secondary: string;
  success: string;
  warning: string;
  error: string;
  info: string;
}

export interface Toast {
  id: string;
  type: NotificationDto['type'];
  title: string;
  message: string;
  duration?: number;
  isClosable?: boolean;
}

// SignalR Connection Events
export interface SignalREvents {
  'SystemStatusUpdate': (status: SystemStatusDto) => void;
  'MobUpdated': (mob: MobInfoDto) => void;
  'Notification': (notification: NotificationDto) => void;
  'ProcessListUpdate': (processes: ProcessInfoDto[]) => void;
}

// Utility types
export type Optional<T, K extends keyof T> = Omit<T, K> & Partial<Pick<T, K>>;
export type RequiredFields<T, K extends keyof T> = T & Required<Pick<T, K>>;

// Component prop types
export interface BaseComponentProps {
  className?: string;
  children?: React.ReactNode;
}

export interface LoadingProps extends BaseComponentProps {
  isLoading: boolean;
  loadingText?: string;
  size?: 'sm' | 'md' | 'lg';
}

export interface ErrorBoundaryState {
  hasError: boolean;
  error?: Error;
  errorInfo?: React.ErrorInfo;
}

// Hook return types
export interface UseApiResult<T> {
  data: T | null;
  isLoading: boolean;
  error: string | null;
  refetch: () => Promise<void>;
}

export interface UseSignalRResult {
  connection: any; // SignalR connection
  isConnected: boolean;
  connectionState: ConnectionState;
  startConnection: () => Promise<void>;
  stopConnection: () => Promise<void>;
}

export interface UseMobDataResult {
  mobs: PagedResponse<MobInfoDto>;
  isLoading: boolean;
  error: string | null;
  refetch: () => Promise<void>;
  updateMob: (mobId: number, dropIndex: number, grade: number, rate: number) => Promise<boolean>;
  massEdit: (request: MassEditRequest) => Promise<number>;
  resetMob: (mobId: number) => Promise<boolean>;
}

// Route parameters
export interface RouteParams {
  mobId?: string;
}

// Menu and navigation types
export interface MenuItem {
  id: string;
  label: string;
  icon: React.ComponentType;
  path: string;
  badge?: string | number;
  disabled?: boolean;
}

export interface BreadcrumbItem {
  label: string;
  path?: string;
  isCurrentPage?: boolean;
}