@echo off
echo Building Web Server...

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake
cmake .. -G "Visual Studio 17 2022" -A x64

REM Build the project
cmake --build . --config Release

REM Run the server (requires admin privileges for port 80)
echo.
echo Starting Web Server...
echo Note: This server runs on port 80 and may require administrator privileges
echo Press Ctrl+C to stop the server
echo.
WebServer.exe

pause 