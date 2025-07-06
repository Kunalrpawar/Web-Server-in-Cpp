# CMake configuration file for the C++ Web Server project
# This file defines how to build the web server using CMake

# Minimum CMake version required for this project
cmake_minimum_required(VERSION 3.10)

# Project name and basic information
project(WebServer)

# Set C++ standard to C++17 for modern C++ features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages (PkgConfig for dependency management)
find_package(PkgConfig REQUIRED)

# Define all source files that need to be compiled
# These are the .cpp files containing the implementation
set(SOURCES
    sockets/main.cpp              # Main entry point
    sockets/SimpleSocket.cpp      # Base socket class implementation
    sockets/BindingSocket.cpp     # Server socket binding implementation
    sockets/ListeningSocket.cpp   # Server socket listening implementation
    sockets/ConnectingSocket.cpp  # Client socket connection implementation
    server/SimpleServer.cpp       # Abstract server base class
    server/TestServer.cpp         # Basic HTTP server implementation
    Networking/hdelibc-networking.cpp  # Networking utilities
    sockets/hdelibc-sockets.cpp   # Socket utilities
)

# Define all header files
# These are the .hpp files containing class declarations and interfaces
set(HEADERS
    sockets/SimpleSocket.hpp      # Base socket class declaration
    sockets/BindingSocket.hpp     # Server socket binding declaration
    sockets/ListeningSocket.hpp   # Server socket listening declaration
    sockets/ConnectingSocket.hpp  # Client socket connection declaration
    sockets/hdelibc-sockets.hpp   # Socket utilities header
    server/SimpleServer.hpp       # Abstract server base class declaration
    server/TestServer.hpp         # Basic HTTP server declaration
    Networking/hdelibc-networking.hpp  # Networking utilities header
)

# Create the executable target named 'WebServer'
# This combines all source and header files into a single executable
add_executable(WebServer ${SOURCES} ${HEADERS})

# Set include directories for the compiler
# These directories contain header files that the source files need to include
target_include_directories(WebServer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}           # Root project directory
    ${CMAKE_CURRENT_SOURCE_DIR}/sockets   # Socket-related headers
    ${CMAKE_CURRENT_SOURCE_DIR}/server    # Server-related headers
    ${CMAKE_CURRENT_SOURCE_DIR}/Networking # Networking utilities headers
)

# Link required libraries for Windows
# The ws2_32 library is required for Windows Socket programming
if(WIN32)
    target_link_libraries(WebServer ws2_32)
endif()

# Set compiler-specific flags for warnings and code quality
if(MSVC)
    # Microsoft Visual C++ compiler flags
    target_compile_options(WebServer PRIVATE /W4)
else()
    # GCC/Clang compiler flags
    target_compile_options(WebServer PRIVATE -Wall -Wextra -Wpedantic)
endif() 