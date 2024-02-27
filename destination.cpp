#include "Destination.h"

int main (int argc, char *argv[])
{
    Destination dest(ZMQ_REQ);
    dest.connect("tcp://localhost:5671");
    dest.start();

    return 0;
}
