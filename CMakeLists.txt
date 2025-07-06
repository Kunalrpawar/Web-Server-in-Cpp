cmake_minimum_required(VERSION 3.10)
project(WebServer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)

# Add source files
set(SOURCES
    sockets/main.cpp
    sockets/SimpleSocket.cpp
    sockets/BindingSocket.cpp
    sockets/ListeningSocket.cpp
    sockets/ConnectingSocket.cpp
    server/SimpleServer.cpp
    server/TestServer.cpp
    Networking/hdelibc-networking.cpp
    sockets/hdelibc-sockets.cpp
)

# Add header files
set(HEADERS
    sockets/SimpleSocket.hpp
    sockets/BindingSocket.hpp
    sockets/ListeningSocket.hpp
    sockets/ConnectingSocket.hpp
    sockets/hdelibc-sockets.hpp
    server/SimpleServer.hpp
    server/TestServer.hpp
    Networking/hdelibc-networking.hpp
)

# Create executable
add_executable(WebServer ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(WebServer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/sockets
    ${CMAKE_CURRENT_SOURCE_DIR}/server
    ${CMAKE_CURRENT_SOURCE_DIR}/Networking
)

# Link libraries for Windows
if(WIN32)
    target_link_libraries(WebServer ws2_32)
endif()

# Set compiler flags
if(MSVC)
    target_compile_options(WebServer PRIVATE /W4)
else()
    target_compile_options(WebServer PRIVATE -Wall -Wextra -Wpedantic)
endif() 