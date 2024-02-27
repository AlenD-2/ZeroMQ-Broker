#pragma once

#include "../Common/IClient.h"

#include <zmq.hpp>


class Destination : public IClient
{
public:
    Destination(int type);
    Destination(zmq::context_t contexts, zmq::socket_t socket);

    void start() override;
};
