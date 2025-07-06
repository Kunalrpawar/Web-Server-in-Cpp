@echo off
echo Building Advanced Web Server with GCC (MinGW)...

echo Compiling Web Server...

REM Compile all source files with GCC
REM This command compiles all the necessary C++ files and links them with the Windows Socket library
g++ -std=c++17 ^
   sockets/main.cpp ^
   sockets/SimpleSocket.cpp ^
   sockets/BindingSocket.cpp ^
   sockets/ListeningSocket.cpp ^
   sockets/ConnectingSocket.cpp ^
   server/SimpleServer.cpp ^
   server/TestServer.cpp ^
   server/AdvancedServer.cpp ^
   -I. ^
   -I sockets ^
   -I server ^
   -I Networking ^
   -lws2_32 ^
   -o WebServer.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Starting Advanced Web Server on port 8080...
    echo Main page: http://localhost:8080
    echo Admin panel: http://localhost:8080/admin
    echo Static files served from: public/
    echo Single-threaded mode
    echo Press Ctrl+C to stop the server
    echo.
    WebServer.exe
) else (
    echo Build failed! Check the error messages above.
)

pause 