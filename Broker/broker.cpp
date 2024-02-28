#include "Broker.h"

int main (int argc, char *argv[])
{
    Broker broker(ZMQ_ROUTER, ZMQ_DEALER);
    broker.bind("tcp://*:5559", "tcp://*:5671");
    broker.start();

    return 0;
}
