#pragma once

#include "../Common/IClient.h"

#include <zmq.hpp>

class Source : public IClient
{
public:
    Source(int type);
    Source(zmq::context_t contexts, zmq::socket_t socket);

    void start() override;
};
