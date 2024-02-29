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
    std::thread displayThread(&Destination::_displayAsinc, this);
    _reciveCount = 0;

    while(1)
    {
        auto id = s_recv(_socket); // broker id
        s_recv(_socket); // Envelope delimiter
        auto reply = s_recv(_socket); // main packet
        s_recv(_socket); // Envelope delimiter
        {
            std::lock_guard<std::mutex> countLock(_displayMutex);
            _sentCount = std::stoi(s_recv(_socket)); // sent count
            _reciveCount++;
        }
    }

    displayThread.join();
}

/*
 * diplay [Sent], [Recive] and [packet lost] every one seconds.
 */
void Destination::_displayAsinc()
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> countLock(_displayMutex);
        qDebug()<< "Sent: " << _sentCount
                << "\tRecive: " << _reciveCount << "\tpacket lost: "
                << _sentCount-(_reciveCount);
    }
}
