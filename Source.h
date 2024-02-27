#pragma once

#include <zmq.hpp>

class Source
{
public:
    Source(int type);
    Source(zmq::context_t contexts, zmq::socket_t socket);

    void connect(const std::string& url);
    void start();

private:
    zmq::context_t _context;
    zmq::socket_t _socket;
};
