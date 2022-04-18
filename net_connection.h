//
// Created by slaur on 07/04/2022.
//
#pragma once
#ifndef NETWORKING_NET_CONNECTION_H
#define NETWORKING_NET_CONNECTION_H

#endif //NETWORKING_NET_CONNECTION_H
#include "tsqueue.h"
#include "net_message.h"
#include "string"
#include "Network.h"

namespace net{
    template<typename T>
class connection : public std::enable_shared_from_this<connection<T>>{
public:
    enum class owner{
        server,
        client
    };
    connection(owner parent, struct sockaddr_in socket, tsqueue<owned_message<T>>& qIn)
            : m_socket(std::move(socket)), m_qMessagesIn(qIn)
            {
                m_nOwnerType = parent;
            }

    virtual ~connection(){}

    uint32_t GetID() const {
        return id;
    }

public:
    bool ConnectToClient(uint32_t uid = 0){
        if(m_nOwnerType == owner::server){

            // TODO: Check if socket is still open.
            id = uid;
            ReadHeader();
        }
    }
    bool ConnectToServer();
    bool Disconnect();
    bool IsConnected() const;

public:
    bool Send(const message<T>& msg){

/*        char* buf = new char[1024];
        buf[0] = ((uint32_t)11);
        buf[1] = ((uint32_t)69);

        uint32_t val1 = ((uint32_t)buf[0]);
        uint32_t val2 = ((uint32_t)buf[1]);
        std::cout << std::to_string(val1) << std::endl;
        std::cout << std::to_string(val2) << std::endl;

        uint32_t istr = ((uint32_t)msg.header.id);
        std::cout << "FUCK" << "\r";*/

        bool WritingMessage = !m_qMessagesOut.empty();
        m_qMessagesOut.push_back(msg);
        if(!WritingMessage)
            WriteHeader();

        return true;
    }

private:
    void ReadHeader(){

    }

    void ReadBody(){

    }

    void WriteHeader(){

        buffer[0] = (uint32_t)m_qMessagesOut.front().header.id;
        buffer[1] = (uint32_t)m_qMessagesOut.front().header.size;

        {
            /*        char buff[1024];
                    for(int w = 0; w < sizeof(uint32_t); w++){
                        buff[w] = ((char*)&m_qMessagesOut.front().header.size)[w];
                    }

                    for(int w = 0; w < sizeof(uint32_t); w++){
                        buff[w + sizeof(uint32_t)] = ((char*)&m_qMessagesOut.front().header.id)[w];
                    }

                    std::cout << "QDS" << std::endl;
                    buffer = (char*)&m_qMessagesOut.front().header.size;


                    buffer = "test";*/
        }

        if(m_qMessagesOut.front().body.size() > 0)
            WriteBody();
        else
        {
            m_qMessagesOut.pop_front();

            if(!m_qMessagesOut.empty())
                WriteHeader();
        }
    }

    void WriteBody(){


        //buffer = (char*)m_qMessagesOut.front().body.data();
        int len = strnlen((char*)m_qMessagesOut.front().body.data(), 1024);
        for(int w = 2; w < len; w++){
            buffer[w] = ((char*)m_qMessagesOut.front().body.data())[w];
        }


        net::message<T> msg;
        CustomMsgTypes msgType = static_cast<CustomMsgTypes>(buffer[0]);
        msg.header.id = msgType;
        msg.header.size = (uint32_t)buffer[1];

        for(int w = 2; w < len; w++){
            msg << buffer[w];
        }
/*        for(int w = 2; w < len - 1; w++){
            msg.body.data()[w] = buffer[w];
        }*/

        std::cout << buffer << std::endl;
        m_qMessagesOut.pop_front();

        // If the queue still has messages in it, then issue the task to
        // send the next messages' header.
        if (!m_qMessagesOut.empty())
        {
            WriteHeader();
        }

        //buffer << m_qMessagesOut.front().body.data();

/*        m_qMessagesOut.pop_front();

        if(!m_qMessagesOut.empty()){
            WriteHeader();
        }*/
    }

protected:
    // Each connection has a unique socket to a remote.
    struct sockaddr_in m_socket;

    // This queue holds all messages to be SENT to the remote side of this connection.
    tsqueue<message<T>> m_qMessagesOut;

    // This queue holds all messages that have been received from the remote side of this connection. Note it is a reference as the "owner" of this connection is expected to provide a queue;
    tsqueue<owned_message<T>>& m_qMessagesIn;

    char* buffer = new char[1024];

    owner m_nOwnerType = owner::server;
    uint32_t id = 0;
};
}