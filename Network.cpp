#include <unistd.h>
#include <fstream>
#include "Network.h"
#include "cassert"
#include "set"
#include "Address.h"
#include "string"
#include "chrono"
#include "thread"
#include "vector"
#include "chrono"
#include "iostream"
#include "libs/json.hpp"
#include "Utils/PlayerClass.h"
#include "Utils/DataType.h"
#include "thread"

// Windows related stuff
bool InitializeSockets(){
#if PLATFORM == PLATFORM_WINDOWS
    WSADATA WsaData;
    // TODO: Windows support (not yet)
#else
    return true;
#endif
}

void Network::ShutdownSockets(){
#if PLATFORM == PLATFORM_WINDOWS
    WSACleanup();
#endif
    close(handle);
}

/*class Address{
public:
    Address(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned short _port){
        address = (a << 24) | (b << 16) | (c << 8) | d;
        port = _port;
    }
    unsigned int getAddress() const {return address;}
    unsigned short getPort() const {return port;}

private:
    unsigned int    address;
    unsigned short  port;
};*/

/*class Socket{
public:
    Socket(){};
    ~Socket(){};

    bool Open(unsigned short port){

    }

    bool IsOpen(){}

    bool Send(const Address &destination, const void* data, int size){

    }
};*/


bool yPressed = false;

/// TODO: Serialization, and deserialization on server-side.

class Player{
public:
    int index;
    vec3f position;
};


double t = 0.0;
double dt = 1.0 / PACKET_SEND_FREQ; // 30Hz send frequency


void foo(){
    std::cout << "HELLO FROM THREAD" << std::endl;
}
// Self-explanatory
void Network::init() {
    if((handle = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Couldn't create socket!");
        exit(EXIT_FAILURE);
    }

    //std::thread testThread(foo);

    nlohmann::json j;
    //j["Players"]["name"] = "Player01";

    j["Players"][0]["name"] = "Player01";
    j["Players"][0]["x"] = 12;
    j["Players"][0]["y"] = 0;
    j["Players"][0]["z"] = 6;

    j["Players"][1]["name"] = "Player02";
    j["Players"][1]["x"] = 26;
    j["Players"][1]["y"] = 2;
    j["Players"][1]["z"] = 0;



/*    j["Object"]["Rock"]["x"] = 12;
    j["Object"]["Rock"]["y"] = 0;
    j["Object"]["Rock"]["z"] = 6;

    j["Object"]["Rock"]["x"] = 12;
    j["Object"]["Rock"]["y"] = 0;
    j["Object"]["Rock"]["z"] = 6;*/


/*    std::vector<PlayerClass> pcls{};
    DataType dt1{};
    dt1.JSONToPlayerClass(&pcls, j);

    json j2;
    dt1.PlayerClassToJSON(&pcls, j2);
    std::cout << "SERIALIZE: " << to_string(j2).c_str() << std::endl;


    std::cout << std::setw(4) << to_string(j).c_str() << std::endl;
    std::ofstream file("test.txt");
    file << j;*/

    memset(&serveraddr, 0, sizeof(serveraddr));
    memset(&clients, 0, sizeof(clients));

    Address serverAddress = Address(127, 0, 0, 1, PORT);

    // Setup IP
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = ntohl(serverAddress.address);
    serveraddr.sin_port = htons(PORT);

    #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
        int nonBlocking = 1;
        if ( fcntl( handle, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 )
        {
            printf( "Failed to set non-blocking\n" );
            exit(EXIT_FAILURE);
        }
    #elif PLATFORM == PLATFORM_WINDOWS
            DWORD nonBlocking = 1;
                if ( ioctlsocket( handle, FIONBIO, &nonBlocking ) != 0 )
                {
                    printf( "failed to set non-blocking\n" );
                    return false;
                }

    #endif

    FD_ZERO(&m_master);
}

// FIXME: Redo that somewhere else: huge refactor incoming...
int Network::findFreeSlot(){
    for(int s = 0; s < MAX_CLIENTS; s++){
        if(!m_clientConnected[s])
            return s;
    }

    // No slots available
    return -1;
}

std::vector<PlayerClass> players{};
[[noreturn]] void Network::runServer() {
    FD_SET(handle, &m_master);

    players.push_back(PlayerClass{"Player0", vec2f{0, 0}});

    if (bind(handle, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    Address saddr = Address(serveraddr);
    char *buff[256];
    std::cout << "SERVER RUNNING ON: " << ntohs(saddr.clientAddr.sin_port) << std::endl;

    // TODO: SEMI-FIXED TIMESTEP FOR BOTH CLIENT AND SERVER.
    auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000.0;
    //std::cout << currentTime << std::endl;
    int paramTries = 0;
    while(true){
        double time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000.0;
        double frameTime = time - currentTime;
        currentTime = time;

        while(frameTime > 0.0){
            float deltaTime = std::min(frameTime, dt);
    /*        fd_set c = m_master;
            int socketCount = select(0, &c, nullptr, nullptr, reinterpret_cast<timeval *>(1000));

            for(int s = 0; s < socketCount; s++){
                int socket = c.fds_bits[s];
                if(socket == handle){
                    std::cout << "OK HAN" << std::endl;
                }else{
                    std::cout << "OTHER OK NHAN" << std::endl;
                }
            }*/
            //std::cout << "passed: " << socketCount << std::endl;
            //printf(reinterpret_cast<const char *>(socketCount));


    /*        for(int i = 0; i < 31; i++){

            }*/
    /*        if(clientSlot == -1){
                continue;
            }*/

            //int n = recvfrom(handle, (char*) buffer, MAXLINE, 0, (struct sockaddr*) &m_clientAddress[clientSlot].clientAddr,
            //reinterpret_cast<socklen_t *>(sizeof(m_clientAddress[clientSlot].clientAddr)));

    /*        if(m_clientAddress[clientSlot].clientAddr.sin_addr.s_addr != 0)
                std::cout << "B: " << m_clientAddress[clientSlot].clientAddr.sin_addr.s_addr << std::endl;*/

            int len, n;

            char *message = "Successfully connected to server";
            len = sizeof(claddr);  //len is value/result

            // (n) = number of bytes read
            n = recvfrom(handle, (char *)buffer, MAXLINE, 0, ( struct sockaddr *) &claddr,
                         reinterpret_cast<socklen_t *>(&len));


            Address current = Address(claddr);
            int existing = FindExistingClientIndex(current);
            if(n != -1 && existing != -1){
                buffer[n] = '\0';
                onMessageReceived(existing, buffer, sizeof(buffer[n]));
            }


            /// FIXME: Re-factorize the system so It's more flexible.
            /// When a new client connects to the server.
            int slot = findFreeSlot();
            if(FindExistingClientIndex(current) == -1 && slot != -1 && claddr.sin_addr.s_addr != 0 && n != -1)
            {
                //m_clients[m_clients.size() + 1] = &current;
                m_clientConnected[slot] = true;
                m_clientAddress[slot] = current;
                onClientConnected(slot);

                //onClientConnected(m_clients.size() + 1);

                char iBuf[256];
                //char *message = "Handshake successful! You're registered in the system.";
                //sendToClient(slot, (const char*) message, strlen(message));
                std::cout << "New entry: " << ntohs(current.clientAddr.sin_port) << std::endl;
    /*            char iBuf[256];
                buffer[n] = '\0';
                std::cout << "(" << slot << ")New entry: " << m_clientAddress[slot].ToString(iBuf, 256) << std::endl;
                printf("Client : %s\n", buffer);*/
            }
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

            players[0].position.y = std::abs(std::sin(3.1415 * t));
            //std::cout << players[0].position.y << std::endl;
            broadcastToClients(to_string(DataType::PlayerClassToJSON(&players)).c_str(), 0);

            frameTime -= deltaTime;
            t += deltaTime;

        }

    }
}

//std::vector<char*> text = {"First handshake test", "Second request", "Third thing?", "Fourth test it's the end", "Five", "666", "7"};
std::vector<char*> text = {"First piece of text", "Second piece of text", "Third piece of text", "Fourth piece of text", "Fifth piece of text"};
void Network::runClient() {
    memset(&serveraddr, 0, sizeof(serveraddr));


    Address server = Address(127, 0, 0, 1, PORT);

    // SERVER INFO
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(server.port);
    serveraddr.sin_addr.s_addr = ntohl(server.address);
    Address reqServer = Address(serveraddr);


    char textBuffer[256];
    std::cout << "QUERYING SERVER: " << reqServer.ToString(textBuffer, 256) << ":" << ntohs(serveraddr.sin_port) << std::endl;

    PlayerClass plr{"test player", vec2f{1, 2}};
    plr.position = vec2f(1, 2);

/*    std::stringstream in(R"({
   "PlayerA": {
      "capital": "paris",
      "highpoint": "20"
    },
   "PlayerB": {
      "size": "20",
      "population": "5000"
    }
})");*/

    std::vector<PlayerClass> listOP{};
    listOP.push_back(plr);

/*    json jimp = json::parse(,listOP);
    std::vector<PlayerClass> players = jimp.get<std::vector<PlayerClass>>();*/

    //std::cout << jimp << std::endl;
    std::chrono::high_resolution_clock::time_point test = std::chrono::high_resolution_clock::now();

    // TODO: SEMI-FIXED TIMESTEP FOR BOTH CLIENT AND SERVER.
    auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000.0;
    std::cout << currentTime << std::endl;
    int paramTries = 0;
    while(true){
        double time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000.0;
        double frameTime = time - currentTime;
        currentTime = time;

        while(frameTime > 0.0){
            float deltaTime = std::min(frameTime, dt);

            char *message = text.at(paramTries);
            //std::cout << (connect(handle, (sockaddr*)&serveraddr, sizeof(serveraddr))) << std::endl;
            int len, n;
            sendto(handle, (const char *)message, strlen(message),
                   0, (const struct sockaddr *) &serveraddr,
                   sizeof(serveraddr));

            n = recvfrom(handle, (char *)buffer, MAXLINE,
                         0, (struct sockaddr *) &serveraddr,
                         reinterpret_cast<socklen_t *>(&len));


            buffer[n] = '\0';
            if(n != -1)
            {
                //std::cout << buffer << std::endl;
                players.clear();
                json j = json::parse(buffer);
                DataType::JSONToPlayerClass(&players, j);


                //std::cout << players[0].position.y << std::endl;
            }

            paramTries++;

            if(paramTries > text.capacity() - 1){
                paramTries = 0;

                //player1.position.y = std::sin(t) + 1;
                //std::cout << player1.position.y << std::endl;

/*
            paramTries--;
*/
                //message = "#";
                //break;
            }

            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
/*        for(int i = 0; i < paramTries; i++){


            message += '#';
        }*/

            //t += dt;
            frameTime -= deltaTime;
            t += deltaTime;
        }
    }

    ShutdownSockets();
}

void Network::sendToClient(int slot, const char *message, int length) {
    sendto(handle, (const char *)message, length,
           0, (const struct sockaddr *) &m_clientAddress[slot].clientAddr,
           sizeof(m_clientAddress[slot].clientAddr));
}

void Network::onClientConnected(int _socket) {
    char tbuff[256];
    time_t now = time(0);
    tm* ctm = localtime(&now);

    std::cout << "["  << ctm->tm_hour << ":" << ctm->tm_min << ":" << ctm->tm_sec << "] " <<"Inbound connexion from: " << m_clientAddress[_socket].ToString(tbuff, 256) << std::endl;
}

void Network::onClientDisconnected(int _socket) {

}

void Network::onMessageReceived(int slot, const char *_in, int len) {
    char cBuffer[256];
    std::string str = m_clientAddress[slot].ToString(cBuffer, 256);
    memset(cBuffer, 0, sizeof (cBuffer));

    char *nBuffer = const_cast<char *>(_in);
    nBuffer[MAXLINE] = '\0';
    ///std::cout << "- " << str << " -- \"" << nBuffer << "\"" <<std::endl;
    //json j = json::parse(nBuffer);
    //DataType::JSONToPlayerClass(&players, j);
/*    if(players.size() >= 1)
        std::cout << "Player added" << std::endl;*/
}

void Network::broadcastToClients(const char *_in, int len) {
    for(int s = 0; s < MAX_CLIENTS; s++){
        if(m_clientConnected[s]){

            sendToClient(s, _in, strlen(_in));
        }
    }
}

int Network::FindExistingClientIndex(const Address & _socket) const
{

/*    for(int e = 0; e < m_clients.size() ; e++){
        if(!m_clients.count(e))
            return -1;
        if(m_clients.at(e)->m_client.sin_addr.s_addr == _socket.m_client.sin_addr.s_addr)
            return e ;
    }*/
/*    for(auto& [slot, client] : m_clients){
        if(_socket.m_client.sin_port == client->m_client.sin_port)
            return slot;
    }*/
    for ( int i = 0; i < MAX_CLIENTS; i++ )
    {
        const Address testcomp = m_clientAddress[i];
        if(testcomp.clientAddr.sin_port == _socket.clientAddr.sin_port)
            return i;
    }
    return -1;
}


