

#include "Socket.h"

namespace std{
    template<>
    struct hash<Socket>{
        size_t operator()(const Socket& key){
            return hash<int>()(key.m_client.sin_addr.s_addr);
        }
    };
}

Socket::Socket(sockaddr_in _in) {
    m_client = _in;
}

const char *Socket::ToString(char *buffer, int buffersize) const {
    const uint8_t a =   m_client.sin_addr.s_addr & 0xff;
    const uint8_t b = ( m_client.sin_addr.s_addr >> 8  ) & 0xff;
    const uint8_t c = ( m_client.sin_addr.s_addr >> 16 ) & 0xff;
    const uint8_t d = ( m_client.sin_addr.s_addr >> 24 ) & 0xff;

    if(m_client.sin_port == 0)
        snprintf(buffer, buffersize, "%d.%d.%d.%d", a, b, c, d);
    else
        snprintf(buffer, buffersize, "%d.%d.%d.%d:%d", a, b, c, d, ntohs(m_client.sin_port));

    //sprintf(1, )
    return buffer;}
