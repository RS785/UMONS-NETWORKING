//
// Created by tanguy on 29/03/22.
//
#include <netinet/in.h>
#include "iostream"
#ifndef NETWORKING_ADDRESS_H
#define NETWORKING_ADDRESS_H


class Address {
public:

    unsigned int    address;
    unsigned short  port;
    char readBuffer[64];

    Address();
    ~Address()= default;

    Address(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint16_t _port = 0);
    Address(unsigned int addr, uint16_t _port = 0);
    Address(sockaddr_in addr);

    const char* ToString(char buffer[], int buffersize) const;
    struct sockaddr_in clientAddr;
};


#endif //NETWORKING_ADDRESS_H
