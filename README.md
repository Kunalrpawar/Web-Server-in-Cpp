# C++ Web Server

A simple HTTP web server implemented in C++ using Windows Sockets (Winsock).

## Features

- HTTP/1.1 compliant responses
- Multi-threaded connection handling
- Windows-compatible networking
- Clean object-oriented design

## Project Structure

```
├── sockets/           # Socket abstraction classes
│   ├── SimpleSocket.hpp/.cpp
│   ├── BindingSocket.hpp/.cpp
│   ├── ListeningSocket.hpp/.cpp
│   ├── ConnectingSocket.hpp/.cpp
│   └── main.cpp       # Main entry point
├── server/            # Server implementation
│   ├── SimpleServer.hpp/.cpp
│   └── TestServer.hpp/.cpp
├── Networking/        # Networking utilities
│   └── hdelibc-networking.hpp/.cpp
├── CMakeLists.txt     # CMake build configuration
├── build.bat          # Windows build script
└── README.md          # This file
```

## Prerequisites

- Windows 10/11
- Visual Studio 2019 or later (with C++ development tools)
- CMake 3.10 or later

## Building the Project

### Option 1: Using the build script (Recommended)

1. Open Command Prompt as Administrator (required for port 80)
2. Navigate to the project directory
3. Run the build script:
   ```cmd
   build.bat
   ```

### Option 2: Manual build

1. Create a build directory:
   ```cmd
   mkdir build
   cd build
   ```

2. Configure with CMake:
   ```cmd
   cmake .. -G "Visual Studio 17 2022" -A x64
   ```

3. Build the project:
   ```cmd
   cmake --build . --config Release
   ```

4. Run the server:
   ```cmd
   WebServer.exe
   ```

   or .\build_gcc.bat

## Usage

1. Start the server (requires administrator privileges for port 80)
2. Open a web browser and navigate to `http://localhost`
3. You should see "Hello from server!" displayed

## Important Notes

- **Administrator Privileges**: The server runs on port 80, which requires administrator privileges on Windows
- **Firewall**: You may need to allow the application through Windows Firewall
- **Port 80**: If port 80 is already in use, modify the port number in `TestServer.cpp`

## Troubleshooting

### Common Issues

1. **"WSAStartup failed"**: Ensure you're running as administrator
2. **"Failed to bind"**: Port 80 might be in use by another service (IIS, Apache, etc.)
3. **Build errors**: Make sure Visual Studio C++ tools are installed

### Alternative Port

To use a different port (e.g., 8080), modify line 3 in `server/TestServer.cpp`:
```cpp
HDE::TestServer::TestServer() : SimpleServer(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10)
```

## Architecture

The project uses a layered architecture:

- **SimpleSocket**: Base socket class with common functionality
- **BindingSocket**: Handles socket binding operations
- **ListeningSocket**: Manages listening for incoming connections
- **SimpleServer**: Abstract server class defining the server interface
- **TestServer**: Concrete implementation of the web server
