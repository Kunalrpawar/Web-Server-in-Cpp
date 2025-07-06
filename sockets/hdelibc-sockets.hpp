#ifndef hdelibc_sockets_hpp
#define hdelibc_sockets_hpp

#include <stdio.h>
#include "SimpleSocket.hpp"      // Base socket class
#include "BindingSocket.hpp"     // Server socket binding
#include "ListeningSocket.hpp"   // Server socket listening
#include "ConnectingSocket.hpp"  // Client socket connection

// Socket utilities header file
// This file provides convenient access to all socket-related classes
// Include this file to get access to the complete socket hierarchy:
// - SimpleSocket: Base class for all sockets
// - BindingSocket: For server applications that need to bind to a port
// - ListeningSocket: For server applications that need to listen for connections
// - ConnectingSocket: For client applications that need to connect to servers

#endif