#include "zhelpers.hpp"

#include <QDebug>

int main (int argc, char *argv[])
{
    zmq::context_t context(1);

    zmq::socket_t reciver(context, ZMQ_REQ);

    qDebug() << "connecting..\n";
#if (defined (WIN32))
    s_set_id(worker, (intptr_t)arg);
    reciver.connect("tcp://localhost:5671");
#else
    s_set_id(reciver);
    reciver.connect("ipc://routing.ipc");
#endif
    qDebug() << "connected\n";

    while(1)
    {
        s_send(reciver, std::string("READY"));
        std::string reply = s_recv(reciver);
        qDebug() << "Client: " << QString::fromStdString(reply);
    }
}
