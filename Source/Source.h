#pragma once

#include "../Common/IClient.h"

#include <zmq.hpp>

#include <mutex>

class Source : public IClient
{
public:
    Source(int type);
    Source(zmq::context_t contexts, zmq::socket_t socket);

    void start() override;

    void setMinPackSize(int size);
    void setMaxPackSize(int size);

private:
    std::string _generateRandomPacket();
    int _minPackSize;
    int _maxPackSize;

    std::once_flag srandFlag;
};
