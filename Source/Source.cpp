#include "Source.h"

#include "../Common/zhelpers.hpp"

#include <QDebug>

Source::Source(int type)
    : IClient(type)
{

}

Source::Source(zmq::context_t contexts, zmq::socket_t socket)
    : IClient(std::move(contexts), std::move(socket))
{
}

void Source::start()
{
    for( int request = 0 ; request < 100 ; request++)
    {
        s_sendmore(_socket, std::string(""));
        s_send(_socket, std::string("Msg number ")+std::to_string(request));
    }
    qDebug()<< "sent";
}
