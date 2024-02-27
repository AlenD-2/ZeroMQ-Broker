#pragma once

#include <zmq.hpp>

/*
 * Interface Client
 * An Interface Class for Source and Destination Classes
 */

class IClient
{
public:
    IClient(int type);
    IClient(zmq::context_t contexts, zmq::socket_t socket);

    void connect(const std::string& url);
    virtual void start()=0;

protected:
    zmq::context_t _context;
    zmq::socket_t _socket;
};
