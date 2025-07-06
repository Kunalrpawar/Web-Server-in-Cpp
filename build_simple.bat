@echo off
echo Building Web Server...

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake
cmake .. -G "Visual Studio 17 2022" -A x64

REM Build the project
cmake --build . --config Release

REM Run the server
echo.
echo Starting Web Server on port 8080...
echo Open your browser and go to: http://localhost:8080
echo Press Ctrl+C to stop the server
echo.
WebServer.exe

pause 