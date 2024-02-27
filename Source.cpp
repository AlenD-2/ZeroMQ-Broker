#include "Source.h"

#include "zhelpers.hpp"

#include <QDebug>

Source::Source(int type)
{
    zmq::context_t newContext(1);
    _context = std::move(newContext);
    zmq::socket_t sender(_context, type);
    _socket = std::move(sender);
}

Source::Source(zmq::context_t contexts, zmq::socket_t socket)
    : _context{std::move(contexts)}, _socket{std::move(socket)}
{
}

void Source::connect(const std::string &url)
{
#if (defined (WIN32))
    s_set_id(socket, (intptr_t)args);
#else
    s_set_id(_socket);
#endif

    _socket.connect(url);
}

void Source::start()
{
    for( int request = 0 ; request < 10 ; request++) {

        s_sendmore(_socket, std::string(""));
        s_send(_socket, std::string("Hello"));

        qDebug()<< "sent";
        s_sleep(1);
    }
}
