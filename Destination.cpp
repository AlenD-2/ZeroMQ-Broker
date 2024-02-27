#include "Destination.h"

#include "zhelpers.hpp"

#include <QDebug>

Destination::Destination(int type)
{
    zmq::context_t ctx(1);
    _context = std::move(ctx);
    zmq::socket_t skt(_context, type);
    _socket = std::move(skt);
}

Destination::Destination(zmq::context_t contexts, zmq::socket_t socket)
    : _context{std::move(contexts)}, _socket{std::move(socket)}
{
}

void Destination::connect(const std::string &url)
{
#if (defined (WIN32))
    s_set_id(_socket, (intptr_t)arg);
#else
    s_set_id(_socket);
#endif
    _socket.connect(url);
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
