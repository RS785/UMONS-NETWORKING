//
// Created by slaur on 07/04/2022.
//
#pragma once
#include "net_message.h"
#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>

#ifndef NETWORKING_TSQUEUE_H
#define NETWORKING_TSQUEUE_H

#endif //NETWORKING_TSQUEUE_H

namespace net{
    template<typename T>
    class tsqueue{
    public:
        tsqueue() = default;
        tsqueue(const tsqueue<T>&) = delete;
        virtual ~tsqueue(){clear();}

        const T& front(){
            std::scoped_lock lock(muxQueue);
            return deqQueue.front();
        }

        const T& back(){
            std::scoped_lock lock(muxQueue);
            return deqQueue.back();
        }

        void push_back(const T& item){
            std::scoped_lock lock(muxQueue);
            deqQueue.emplace_back(std::move(item));
        }

        void push_front(const T& item){
            std::scoped_lock lock(muxQueue);
            deqQueue.emplace_front(std::move(item));
        }

        bool empty(){
            std::scoped_lock lock(muxQueue);
            return deqQueue.empty();
        }

        size_t count(){
            std::scoped_lock lock(muxQueue);
            return deqQueue.size();
        }

        void clear(){
            std::scoped_lock lock(muxQueue);
            deqQueue.clear();
        }

        T pop_front(){
            std::scoped_lock lock(muxQueue);
            auto t = std::move(deqQueue.front());
            deqQueue.pop_front();
            return t;
        }

        T pop_back(){
            std::scoped_lock lock(muxQueue);
            auto t = std::move(deqQueue.back());
            deqQueue.pop_back();
            return t;
        }

    protected:
        std::mutex muxQueue;
        std::deque<T> deqQueue;
    };


/*    // Forward declare connection
*//*    template<typename T>
    class connection;*//*

    template<typename T>
    struct owned_message{
        std::shared_ptr<net::connection<T>> remote = nullptr;
       //Network::message<T> msg;

        friend std::ostream& operator << (std::ostream& os, const owned_message<T>& msg){
            os << msg.msg;
            return os;
        }
    };*/
}