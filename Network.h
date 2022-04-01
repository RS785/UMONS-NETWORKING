#include <iostream>
#include <cassert>
#include "cstring"
#include "Address.h"
#include "unordered_map"
#include "Socket.h"

#ifndef NETWORKING_NETWORK_H
#define NETWORKING_NETWORK_H

#define PACKET_SEND_FREQ 30

class Network {
public:
    char buffer[MAXLINE];
    std::unordered_map<int, Socket*> m_clients{};

    struct sockaddr_in serveraddr, claddr;
    struct sockaddr_in clients[MAX_CLIENTS]{};
    int handle;

    Address m_clientAddress[MAX_CLIENTS];
    bool m_clientConnected[MAX_CLIENTS];
    uint numClients = 0;

    void init();;
    int findFreeSlot();
    int FindExistingClientIndex(const Address & address) const;
    void ShutdownSockets();

    int inboundSocket();

    [[noreturn]] void runServer();
    void runClient();


protected:
    virtual void sendToClient(int _socket, const char* _out, int len);
    virtual void onClientConnected(int _socket);
    virtual void onClientDisconnected(int _socket);
    // Handler for whenever a client sends a message to the server.
    virtual void onMessageReceived(int client_socket, const char* _in, int len);
    virtual void broadcastToClients(const char* _in, int len);

private:
    const char* IP_Address;
    fd_set m_master;

};


#endif //NETWORKING_NETWORK_H
