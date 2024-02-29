#include "Destination.h"

#include "../Common/zhelpers.hpp"

#include <QDebug>
#include <QElapsedTimer>

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
    int packCount=0;
    QElapsedTimer time;
    time.start();
    while(1)
    {
        std::string id = s_recv(_socket);
        s_recv(_socket);
        std::string reply = s_recv(_socket);
        packCount++;
        if(reply == "END")
            break;
    }
    qDebug() << "Client: " << packCount << " in "<<time.elapsed();
}
