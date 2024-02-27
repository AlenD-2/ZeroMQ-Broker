#include "zhelpers.hpp"

#include <QDebug>

std::string backidentity;

int main (int argc, char *argv[])
{
    //  Prepare our context and sockets
    zmq::context_t context(1);
    zmq::socket_t frontend (context, ZMQ_ROUTER);
    zmq::socket_t backend (context, ZMQ_ROUTER);

    frontend.bind("tcp://*:5559");
#if (defined(WIN32))
    backend.bind("tcp://*:5571");
#else
    backend.bind("ipc://routing.ipc");
#endif

    //  Initialize poll set
    zmq::pollitem_t items [] = {
        { frontend, 0, ZMQ_POLLIN, 0 },
        { backend, 0, ZMQ_POLLIN, 0 }
    };

    // Switch messages between sockets
    while (1) {
        zmq::message_t message;
        const zmq::message_t emptyMsg;
        int more; // Multipart detection

        // Poll for events indefinitely
        zmq_poll(items, 2, -1);

        if (items [0].revents & ZMQ_POLLIN) {
            std::string identity = s_recv(frontend);
            s_recv(frontend);     // Envelope delimiter
            std::string msg = s_recv(frontend);     // Response from frontend

            qDebug()<<"Frontend: "<<QString::fromStdString(msg);

            s_sendmore(backend, backidentity);
            s_sendmore(backend, std::string(""));
            s_send(backend, msg);
        }
        if (items [1].revents & ZMQ_POLLIN) {
            backidentity = s_recv(backend);
            s_recv(backend);     // Envelope delimiter
            std::string request = s_recv(backend);
            qDebug() << "Backend: "<<QString::fromStdString(request);
        }
    }
    return 0;
}
