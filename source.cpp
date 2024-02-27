#include "zhelpers.hpp"

#include <QDebug>

int main (int argc, char *argv[])
{
    zmq::context_t context(1);

    zmq::socket_t sender(context, ZMQ_DEALER);

#if (defined (WIN32))
    s_set_id(sender, (intptr_t)args);
#else
    s_set_id(sender);
#endif

    sender.connect("tcp://localhost:5559");

    for( int request = 0 ; request < 10 ; request++) {

        s_sendmore(sender, std::string(""));
        s_send(sender, std::string("Hello"));

        qDebug()<< "sent";
        s_sleep(5);
    }
}
