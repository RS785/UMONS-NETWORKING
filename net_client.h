//
// Created by slaur on 07/04/2022.
//

#pragma once
#include "tsqueue.h"

#ifndef NETWORKING_NET_CLIENT_H

#define NETWORKING_NET_CLIENT_H
#endif //NETWORKING_NET_CLIENT_H

namespace net{

    template<typename T>
    class client_interface{
    public:
        explicit client_interface(){

                        #if PLATFORM == PLATFORM_WINDOWS
            WSADATA WsaData;
            WSAStartup( MAKEWORD(2,2),
                        &WsaData )
                        == NO_ERROR;
                        #endif

            //net.InitializeSockets();

            if((handle = socket(AF_INET, SOCK_DGRAM, 0)) <= 0){
                perror("Couldn't create socket!");
                exit(EXIT_FAILURE);
            }
        }

        virtual ~client_interface(){
            Disconnect();
        }

        bool Connect(const sockaddr_in& address){


            m_connection = std::make_unique<connection<T>>(connection<T>::owner::client, address, m_qMessagesIn);

            //sendto(handle, (char[]*) )
/*
            try{


                //m_threadContext = std::thread([this]() { m_threadContext.run(); });
            }catch(std::nullptr_t) {

            }*/
            //sendto(handle)
            return false;
        }

        void Disconnect(){
            //sendto(handle, )
        }

        bool IsConnected(){
/*            if(m_connection)
                return m_connection.*/
            return false;
        }

        tsqueue<owned_message<T>>& Incoming(){
            return m_qMessagesIn;
        }

    public:
        void Send(const message<T>& msg){
            // Check if still connected to server thought.
            m_connection->Send(msg);
        }

    protected:
        std::unique_ptr<connection<T>> m_connection;
        struct sockaddr_in m_socket{};
        int handle;

        std::thread m_threadContext;

    private:
        tsqueue<owned_message<T>> m_qMessagesIn;
    };
}