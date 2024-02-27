#include "Destination.h"

#include "../Common/zhelpers.hpp"

#include <QDebug>

Destination::Destination(int type)
    : IClient(type)
{

}

Destination::Destination(zmq::context_t contexts, zmq::socket_t socket)
    : IClient(std::move(contexts), std::move(socket))
{
}

void Destination::start()
{
    while(1)
    {
        s_send(_socket, std::string("READY"));
        std::string reply = s_recv(_socket);
        qDebug() << "Client: " << QString::fromStdString(reply);
    }
}
