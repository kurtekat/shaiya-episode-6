@echo off
echo Building Shaiya Monster Drop Web Application...

REM Check if .NET 8 is installed
dotnet --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: .NET 8.0 SDK is required but not found.
    echo Please install .NET 8.0 SDK from: https://dotnet.microsoft.com/download
    pause
    exit /b 1
)

REM Check if Node.js is installed
node --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: Node.js is required but not found.
    echo Please install Node.js from: https://nodejs.org/
    pause
    exit /b 1
)

echo ===============================================
echo Building Backend (ASP.NET Core API)...
echo ===============================================

cd Backend

REM Clean previous builds
echo Cleaning previous builds...
if exist bin rmdir /s /q bin
if exist obj rmdir /s /q obj

REM Restore packages
echo Restoring NuGet packages...
dotnet restore
if %errorlevel% neq 0 (
    echo ERROR: Failed to restore backend packages
    pause
    exit /b 1
)

REM Build Release configuration
echo Building backend Release configuration...
dotnet build --configuration Release --no-restore
if %errorlevel% neq 0 (
    echo ERROR: Backend build failed
    pause
    exit /b 1
)

REM Publish backend
echo Publishing backend...
dotnet publish --configuration Release --runtime win-x64 --self-contained false --output publish
if %errorlevel% neq 0 (
    echo ERROR: Backend publish failed
    pause
    exit /b 1
)

echo Backend build completed successfully!

cd ..

echo ===============================================
echo Building Frontend (React Application)...
echo ===============================================

cd Frontend

REM Clean previous builds
echo Cleaning previous builds...
if exist dist rmdir /s /q dist
if exist node_modules\.cache rmdir /s /q node_modules\.cache

REM Install dependencies
echo Installing npm dependencies...
npm install
if %errorlevel% neq 0 (
    echo ERROR: Failed to install frontend dependencies
    pause
    exit /b 1
)

REM Build production version
echo Building frontend for production...
npm run build
if %errorlevel% neq 0 (
    echo ERROR: Frontend build failed
    pause
    exit /b 1
)

echo Frontend build completed successfully!

cd ..

echo ===============================================
echo Build Summary
echo ===============================================
echo.
echo ✅ Backend API built successfully
echo    Location: Backend\publish\
echo    Entry point: MonsterDropWebAPI.exe
echo.
echo ✅ Frontend built successfully  
echo    Location: Frontend\dist\
echo    Static files ready for web server
echo.
echo ===============================================
echo Deployment Instructions
echo ===============================================
echo.
echo 1. Backend Deployment:
echo    - Copy Backend\publish\ to your server
echo    - Run as Administrator: MonsterDropWebAPI.exe
echo    - API will be available at: http://localhost:5000
echo.
echo 2. Frontend Deployment:
echo    - Copy Frontend\dist\ to your web server
echo    - Configure web server to serve static files
echo    - Update API endpoint in production if needed
echo.
echo 3. Development Mode:
echo    - Backend: cd Backend ^&^& dotnet run
echo    - Frontend: cd Frontend ^&^& npm run dev
echo    - Access at: http://localhost:3000
echo.
echo 🎉 Build completed successfully!
echo Make sure to run as Administrator for memory access.
echo ===============================================
echo.
pause