#pragma once

#include <zmq.hpp>

#include <queue>

class Broker
{
public:
    Broker(int frontType, int backType);
    Broker(zmq::context_t context, zmq::socket_t frontend, zmq::socket_t backend);

    void bind(const std::string& frontUrl, const std::string& backUrl);
    void start();

private:
    zmq::context_t _context;
    zmq::socket_t _frontend;
    zmq::socket_t _backend;

    std::queue<std::string> _queue;
};
