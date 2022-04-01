#include "map"
#include "unordered_map"

// DEFINE PLATFORMS FOR CROSS COMPATIBILITY
#define PLATFORM_WINDOWS 0
#define PLATFORM_MAC     1
#define PLATFORM_UNIX    2

#if defined(_WIN32)
#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNIX
#endif

// Include dependencies according to the current OS
#if PLATFORM == PLATFORM_WINDOWS
#include "winsock2.h"
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
#include "sys/socket.h"
#include "netinet/in.h"
#include "fcntl.h"

#endif

#if PLATFORM == PLATFORM_WINDOWS
#pragma comment( lib, "wsock32.lib" )
#endif

#define assertm(exp, msg) assert(((void)msg, exp))

#define PORT    11785
#define MAXLINE 1024
#define MAX_CLIENTS 16

#ifndef NETWORKING_SOCKET_H
#define NETWORKING_SOCKET_H



enum State{
    CONNECTED,
    DISCONNECTED,
    CONNECTING
};

class Socket {
public:
    Socket();
    Socket(sockaddr_in _in);
    sockaddr_in m_client;

    const char* ToString(char buffer[], int buffersize) const;

    //void Disconnect
};


#endif //NETWORKING_SOCKET_H
