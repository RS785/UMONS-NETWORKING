//
// Created by tanguy on 29/03/22.
//

#include <cstring>
#include "Address.h"

Address::Address() {
    //memset(address, 0, sizeof(address));
}

Address::Address(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint16_t _port) {
    address = (a << 24) | (b << 16) | (c << 8) | d;
    port = _port;
}

Address::Address(unsigned int addr, unsigned short _port) {
    address = addr;
    port = _port;
}

const char *Address::ToString(char buffer[], int buffersize) const{
    const uint8_t a =   address & 0xff;
    const uint8_t b = ( address >> 8  ) & 0xff;
    const uint8_t c = ( address >> 16 ) & 0xff;
    const uint8_t d = ( address >> 24 ) & 0xff;

    if(port == 0)
        snprintf(buffer, buffersize, "%d.%d.%d.%d", a, b, c, d);
    else
        snprintf(buffer, buffersize, "%d.%d.%d.%d:%d", a, b, c, d, ntohs(port));

    //sprintf(1, )
    return buffer;
}

Address::Address(sockaddr_in addr) {
    address = addr.sin_addr.s_addr;
    port = addr.sin_port;
    clientAddr = addr;
}
