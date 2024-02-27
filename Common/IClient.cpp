#include "IClient.h"

#include "../Common/zhelpers.hpp"

#include <QDebug>

IClient::IClient(int type)
{
    zmq::context_t tempContext(1);
    _context = std::move(tempContext);
    zmq::socket_t tempSocket(_context, type);
    _socket = std::move(tempSocket);
}

IClient::IClient(zmq::context_t contexts, zmq::socket_t socket)
    : _context{std::move(contexts)}, _socket{std::move(socket)}
{

}

void IClient::connect(const std::string &url)
{
#if (defined (WIN32))
    s_set_id(_socket, (intptr_t)arg);
#else
    s_set_id(_socket);
#endif
    _socket.connect(url);
}
