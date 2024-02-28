#include "Source.h"

#include "../Common/zhelpers.hpp"

#include <QDebug>
#include <QElapsedTimer>

Source::Source(int type)
    : IClient(type)
{
    _minPackSize = 50;
    _maxPackSize = 8'000;
}

Source::Source(zmq::context_t contexts, zmq::socket_t socket)
    : IClient(std::move(contexts), std::move(socket))
{
    _minPackSize = 50;
    _maxPackSize = 8'000;
}

void Source::start()
{
    QElapsedTimer time;
    time.start();
    for( int request = 0 ; request < 10000 ; request++)
    {
        s_sendmore(_socket, std::string(""));
        s_send(_socket, _generateRandomPacket());
    }
    qDebug()<< "sent" << "elapced time: " << time.elapsed();
}

void Source::setMinPackSize(int size)
{
    if(size < 0)
        return;
    _minPackSize = size;
}

void Source::setMaxPackSize(int size)
{
    if(size < 0)
        return;
    _maxPackSize = size;
}

std::string Source::_generateRandomPacket()
{
    std::string result;

    std::call_once(srandFlag, [](){std::srand(std::time(nullptr));});

    // generate random packet size between minimum size and maximum size
    auto packSize = (_minPackSize+std::rand())%_maxPackSize;
    result.resize(packSize,'A');

    return result;
}
