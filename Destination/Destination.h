#pragma once

#include "../Common/IClient.h"

#include <zmq.hpp>

#include <thread>
#include <mutex>

class Destination : public IClient
{
public:
    Destination(int type);
    Destination(zmq::context_t contexts, zmq::socket_t socket);

    void start() override;

private:
    void _displayAsinc();
    std::mutex _displayMutex;

    size_t _sentCount;
    size_t _reciveCount;
};
