#include "Broker.h"

#include "../Common/zhelpers.hpp"

#include <QDebug>

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

void Broker::start()
{
    std::string backidentity;
    bool isReady=false;

    //  Initialize poll set
    zmq::pollitem_t items [] = {
        { _frontend, 0, ZMQ_POLLIN, 0 },
        { _backend, 0, ZMQ_POLLIN, 0 }
    };

    // Switch messages between sockets
    while (1) {
        zmq::message_t message;
        const zmq::message_t emptyMsg;
        int more; // Multipart detection

        // Poll for events indefinitely
        zmq_poll(items, 2, -1);

        // if frontend sent a msg
        if (items [0].revents & ZMQ_POLLIN) {
            std::string identity = s_recv(_frontend);
            s_recv(_frontend); // Envelope delimiter
            std::string msg = s_recv(_frontend); // Response from frontend
            if(isReady)
            {
                qDebug()<<"Direct: "<<QString::fromStdString(msg);
                isReady = false;
                s_sendmore(_backend, backidentity);
                s_sendmore(_backend, std::string(""));
                s_send(_backend, msg);
            }
            else
            {
                qDebug()<<"Pushed: "<<QString::fromStdString(msg);
                _queue.push(msg);
            }
        }
        // if backend sent a msg
        if (items [1].revents & ZMQ_POLLIN) {
            backidentity = s_recv(_backend);
            s_recv(_backend); // Envelope delimiter
            std::string request = s_recv(_backend); // Response from backend
            if(request == "READY")
            {
                // if queue is empty then be ready and wait for incomming msg
                if(_queue.empty())
                {
                    isReady = true;
                }
                else
                {
                    s_sendmore(_backend, backidentity);
                    s_sendmore(_backend, std::string(""));
                    s_send(_backend, _queue.front());
                    _queue.pop();
                }
            }
        }
    }
}
