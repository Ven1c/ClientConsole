// common.h

#pragma once
#ifndef COMMON_H
#define COMMON_H

#ifdef _WIN32 // If host's OS is Windows
#ifndef _WIN32_WINNT // Necessary for properly initializing WindowsAPI
#define _WIN32_WINNT 0x0600 // minimum - Windows Vista (0x0600)
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <unordered_map>

#pragma comment(lib, "ws2_32.lib") // For VS compiler
#else // Other UNIX-like OSes
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h> // For getting error codes
#include <sys/select.h>
#endif

#include <string>
#include <iostream>
#include <cstring>
#include <ctime>

// Cross-Platform macros
#ifdef _WIN32
#define CLOSE_SOCKET(s) closesocket(s)
#define GET_SOCKET_ERRNO() (WSAGetLastError())
#define IS_VALID_SOCKET(s) ((s) != INVALID_SOCKET)
#else
#define SOCKET int
#define CLOSE_SOCKET(s) close(s)
#define GET_SOCKET_ERRNO() (errno)
#define IS_VALID_SOCKET(s) ((s) >= 0)
#endif

#define MAX_DATA_BUFFER_SIZE 2048
    
#define BACKLOG 10
using namespace std::string_literals;
// Adds 4-digit length to the beginning of the message string: message.size() == 4 -> "0004<message_string>"; message.size() == 1002 -> "1002<message_string>"

#endif