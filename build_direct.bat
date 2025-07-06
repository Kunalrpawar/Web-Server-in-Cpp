@echo off
echo Building Web Server directly with Visual Studio compiler...

REM Try to find Visual Studio
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist "%VSWHERE%" (
    for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
        set "VS_PATH=%%i"
    )
)

if defined VS_PATH (
    echo Found Visual Studio at: %VS_PATH%
    call "%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat"
) else (
    echo Visual Studio not found. Trying default paths...
    if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
    ) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat"
    ) else if exist "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
    ) else (
        echo Error: Visual Studio not found. Please install Visual Studio with C++ tools.
        pause
        exit /b 1
    )
)

echo Compiling Web Server...

REM Compile all source files
cl /EHsc /std:c++17 ^
   sockets/main.cpp ^
   sockets/SimpleSocket.cpp ^
   sockets/BindingSocket.cpp ^
   sockets/ListeningSocket.cpp ^
   sockets/ConnectingSocket.cpp ^
   server/SimpleServer.cpp ^
   server/TestServer.cpp ^
   /I. ^
   /I sockets ^
   /I server ^
   /I Networking ^
   ws2_32.lib ^
   /Fe:WebServer.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Starting Web Server on port 8080...
    echo Open your browser and go to: http://localhost:8080
    echo Press Ctrl+C to stop the server
    echo.
    WebServer.exe
) else (
    echo Build failed!
)

pause 