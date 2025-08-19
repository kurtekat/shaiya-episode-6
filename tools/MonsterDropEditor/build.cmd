@echo off
echo Building Shaiya Monster Drop Editor...

REM Check if .NET 8 is installed
dotnet --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: .NET 8.0 SDK is required but not found.
    echo Please install .NET 8.0 SDK from: https://dotnet.microsoft.com/download
    pause
    exit /b 1
)

REM Clean previous builds
echo Cleaning previous builds...
if exist bin rmdir /s /q bin
if exist obj rmdir /s /q obj

REM Restore packages
echo Restoring NuGet packages...
dotnet restore
if %errorlevel% neq 0 (
    echo ERROR: Failed to restore packages
    pause
    exit /b 1
)

REM Build Release configuration
echo Building Release configuration...
dotnet build --configuration Release --no-restore
if %errorlevel% neq 0 (
    echo ERROR: Build failed
    pause
    exit /b 1
)

REM Publish self-contained executable
echo Publishing self-contained executable...
dotnet publish --configuration Release --runtime win-x64 --self-contained true --output publish
if %errorlevel% neq 0 (
    echo ERROR: Publish failed
    pause
    exit /b 1
)

echo.
echo ===============================================
echo Build completed successfully!
echo.
echo Executable location: publish\MonsterDropEditor.exe
echo.
echo You can now run the Monster Drop Editor.
echo Make sure to run as Administrator for memory access.
echo ===============================================
echo.
pause