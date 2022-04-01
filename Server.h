//
// Created by tanguy on 28/03/22.
//

#ifndef NETWORKING_SERVER_H
#define NETWORKING_SERVER_H

const int MAX_CLIENTS = 32;

namespace Network{
    class Server {
    public:
        int m_maxClients;
        int m_numConnectedClients;
        bool m_clientConnected[MAX_CLIENTS];
    };
}


#endif //NETWORKING_SERVER_H
