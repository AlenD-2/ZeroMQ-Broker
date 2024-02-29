#include "Broker.h"

#include "../Common/zhelpers.hpp"

#include <QDebug>
#include <QDir>

Broker::Broker(int frontType, int backType)
{
    zmq::context_t tempCtx(1);
    _context = std::move(tempCtx);
    zmq::socket_t tempFront(_context, frontType);
    _frontend = std::move(tempFront);
    zmq::socket_t tempBack(_context, backType);
    _backend = std::move(tempBack);
}

Broker::Broker(zmq::context_t context, zmq::socket_t frontend, zmq::socket_t backend)
    : _context{std::move(context)}, _frontend{std::move(frontend)}, _backend{std::move(backend)}
{
}

void Broker::bind(const std::string &frontUrl, const std::string &backUrl)
{
    _frontend.bind(frontUrl);
    _backend.bind(backUrl);
}

/*
 * start polling for frontend packets.
 * use two thread: a new thread for baackend and main thread for frontend
 * incomming packets.
 * push packet in queue and notify backend thread to send them.
 */
void Broker::start()
{
    // start backend thread to send packet
    std::thread backendThread (&Broker::_backendSender, this);

    //  Initialize poll set
    zmq::pollitem_t items [] = {
        { _frontend, 0, ZMQ_POLLIN, 0 }
    };

    while(true)
    {
        // Poll for events indefinitely
        zmq_poll(items, 1, -1);

        // if frontend sent a packet
        if (items [0].revents & ZMQ_POLLIN)
        {
            s_recv(_frontend); // frontend identity
            s_recv(_frontend); // Envelope delimiter
            std::string packet = s_recv(_frontend); // Response from frontend
            {
                std::lock_guard<std::mutex> queueLkGourd(_queueLock);
                _packetQueue.push(packet);
                _backup.push(packet);
            }
            _queueCondition.notify_one();
        }
    }

    backendThread.join();
}

/*
 * when queue is not emptyy then start sending packets
 * to backend and wait for queue again
 */
void Broker::_backendSender()
{
    while(true)
    {
        s_sendmore(_backend, std::string(""));

        std::unique_lock<std::mutex> queueLock(_queueLock);
        _queueCondition.wait(queueLock, [this]{return !_packetQueue.empty();});
        auto packet  = _packetQueue.front();
        _packetQueue.pop();
        _backup.pop();
        queueLock.unlock();

        s_send(_backend, packet);

    }
}
