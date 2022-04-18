//
// Created by slaur on 08/04/2022.
//
#pragma once
#ifndef NETWORKING_NET_MESSAGE_H
#define NETWORKING_NET_MESSAGE_H

#endif //NETWORKING_NET_MESSAGE_H

namespace net{

    template<typename T>
    struct message_header{
        T id{};
        uint32_t size = 0;
    };

    template<typename T>
    struct message{
        message_header<T> header{};
        std::vector<uint8_t> body;

        size_t size() const{
            return sizeof(message_header<T>) + body.size();
        }

        template<typename DataType>
        friend message<T>& operator << (message<T>& msg, const DataType& data){
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed.");

            size_t i = msg.body.size();
            msg.body.resize(msg.body.size() + sizeof(DataType));
            std::memcpy(msg.body.data() + i, &data, sizeof(DataType));
            msg.header.size = msg.size();

            return msg;
        }

        template<typename DataType>
        friend message<T>& operator >> (message<T>& msg, DataType& data){
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pulled from vector");

            // Cache the location towards the end of the vector where the pulled data starts
            size_t i = msg.body.size() - sizeof(DataType);

            // Physically copy the data from the vector into the user variable
            std::memcpy(&data, msg.body.data() + i, sizeof(DataType));

            // Shrink the vector to remove read bytes, and reset end position
            msg.body.resize(i);

            // Recalculate the message size
            msg.header.size = msg.size();

            // Return the target message so it can be "chained"
            return msg;
        }
    };

    template <typename T>
    class connection;

    template <typename T>
    struct owned_message {
        std::shared_ptr<connection<T>> remote = nullptr;
        message<T> msg;

        // Again, a friendly string maker
        friend std::ostream& operator<<(std::ostream& os, const owned_message<T>& msg)
        {
            os << msg.msg;
            return os;
        }
    };
}