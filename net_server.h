//
// Created by slaur on 08/04/2022.
//
#pragma once
#include <memory>
#include "tsqueue.h"
#include "glm/glm.hpp"
#include "net_connection.h"

#ifndef NETWORKING_NET_SERVER_H
#define NETWORKING_NET_SERVER_H

#endif //NETWORKING_NET_SERVER_H

#define PACKET_SEND_FREQ 60

namespace net{
    template<typename T>
    class server_interface{
    public:
        explicit server_interface(){
            #if PLATFORM == PLATFORM_WINDOWS
            WSADATA WsaData;
            WSAStartup( MAKEWORD(2,2),
                               &WsaData )
                               == NO_ERROR;
            #endif

            if((handle = socket(AF_INET, SOCK_DGRAM, 0)) <= 0){
                perror("Couldn't create socket!");
                exit(EXIT_FAILURE);
            }

            //m_socket = server_socket;
            m_socket.sin_family = AF_INET;
            m_socket.sin_addr.s_addr = INADDR_ANY;
            m_socket.sin_port = htons((unsigned short) 11785);

            {
            #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
                int nonBlocking = 1;
                if ( fcntl( handle, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 )
                {
                    printf( "Failed to set non-blocking\n" );
                    exit(EXIT_FAILURE);
                }
                #elif PLATFORM == PLATFORM_WINDOWS

                DWORD nonBlocking = 1;
                if ( ioctlsocket( handle,
                                  FIONBIO,
                                  &nonBlocking ) != 0 )
                {
                    printf( "failed to set non-blocking\n" );
                    exit(EXIT_FAILURE);
                }

                #endif
            }

            if (bind(handle, (const sockaddr *)&m_socket, sizeof(sockaddr_in)) < 0)
            {
                perror("bind failed");
                exit(EXIT_FAILURE);
            }
         }

        virtual ~server_interface(){
            Stop();
        }

        [[noreturn]] bool Start(){

            std::cout << "Server started on port: " << PORT << "\n";
            auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000.0;

            while(true){
                double time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000.0;
                double frameTime = time - currentTime;
                currentTime = time;


                // [ID|DATA]
                char* buffer;
                //buffer = mess

                std::cout << buffer << "\r";
                while(frameTime > 0.0){
                    ZeroMemory(buffer, 1024);
                    //std::cout << "Runnning...\n";
                    float deltaTime = glm::min(frameTime, dt);

                    struct sockaddr_in claddr;

                    int len, n;

                    char *message = "Successfully connected to server";
                    len = sizeof(claddr);  //len is value/result

                    // (n) = number of bytes read
                    n = recvfrom(handle, (char *)buffer, MAXLINE, 0, ( struct sockaddr *) &claddr,
                            reinterpret_cast<int *>(&len));


                    if(n != -1){
                        std::cout << "VALUE CHANGED AHAHAH!!\n";
                        std::shared_ptr<connection<T>> newconn = std::make_shared<connection<T>>(connection<T>::owner::server, std::move(claddr), m_qMessagesIn);
                        if(OnClientConnect(newconn)){

                        }else{
                            std::cout << "NOT CONNECTED\n";
                        }
                    }

//                    Address current = Address(claddr);
//                    int existing = FindExistingClientIndex(current);
//                    if(n != -1 && existing != -1){
//                        buffer[n] = '\0';
//                        onMessageReceived(existing, buffer, sizeof(buffer[n]));
//                    }
//
//
//                    /// FIXME: Re-factorize the system so It's more flexible.
//                    /// When a new client connects to the server.
//                    int slot = findFreeSlot();
//                    if(FindExistingClientIndex(current) == -1 && slot != -1 && claddr.sin_addr.s_addr != 0 && n != -1)
//                    {
//                        //m_clients[m_clients.size() + 1] = &current;
//                        m_clientConnected[slot] = true;
//                        m_clientAddress[slot] = current;
//                        onClientConnected(slot);
//
//                        //onClientConnected(m_clients.size() + 1);
//
//                        char iBuf[256];
//                        //char *message = "Handshake successful! You're registered in the system.";
//                        //sendToClient(slot, (const char*) message, strlen(message));
//                        std::cout << "New entry: " << ntohs(current.clientAddr.sin_port) << std::endl;
//                        /*            char iBuf[256];
//                                    buffer[n] = '\0';
//                                    std::cout << "(" << slot << ")New entry: " << m_clientAddress[slot].ToString(iBuf, 256) << std::endl;
//                                    printf("Client : %s\n", buffer);*/
//                    }
                    /*        sendto(handle, (const char *)message, strlen(message),
                                   0, (const struct sockaddr *) &claddr,
                                   len);*/

                    /*        buffer[n] = '\0';
                            printf("Client : %s\n", buffer);
                            sendto(handle, (const char *)message, strlen(message),
                                   0, (const struct sockaddr *) &claddr,
                                   len);
                            printf("Hello message sent.\n");*/

                    //const char* buf = to_string(JSONEASYLOL["Players"]).c_str();
                    //std::cout << "BEFORE SEND: " << to_string(DataType::PlayerClassToJSON(&players, j)).c_str() << std::endl;
                    //std::cout << "DQSDS:" << buf << std::endl;

                    //players[0].position.y = std::abs(std::sin(3.1415 * t));
                    //std::cout << players[0].position.y << std::endl;
                    //broadcastToClients(to_string(DataType::PlayerClassToJSON(&players)).c_str(), 0);

                    frameTime -= deltaTime;
                    t += deltaTime;

                }
            }
        }

        bool Stop(){

            return false;
        }

        void WaitForClientConnection(){

        }

        void MessageClient(std::shared_ptr<connection<T>> _client, const message<T>& msg){
            _client->Send(msg);
        }

        void MessageAllClients(const message<T>& msg, std::shared_ptr<connection<T>> pIgnoreClient = nullptr){

        }

    protected:
        virtual bool OnClientConnect(std::shared_ptr<connection<T>> client){

            return false;
        }

        virtual void OnClientDisconnect(std::shared_ptr<connection<T>> client){

        }

        virtual void OnMessage(std::shared_ptr<connection<T>> client, message<T>& msg){

        }

    protected:
        tsqueue<owned_message<T>> m_qMessagesIn;
        struct sockaddr_in m_socket;
        int handle;

        std::thread m_threadContext;

        double t = 0.0;
        double dt = 1.0 / (double)PACKET_SEND_FREQ; // 30Hz send frequency

        uint32_t nIDCounter = 10000;
    };
}