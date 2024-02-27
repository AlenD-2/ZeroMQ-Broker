#pragma once

#include <zmq.hpp>


class Destination
{
public:
    Destination(int type);
    Destination(zmq::context_t contexts, zmq::socket_t socket);

    void connect(const std::string& url);
    void start();

private:
    zmq::context_t _context;
    zmq::socket_t _socket;
};
