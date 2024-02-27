#include "Source.h"

#include <QDebug>

int main (int argc, char *argv[])
{
    Source s(ZMQ_DEALER);
    s.connect("tcp://localhost:5559");
    s.start();

    return  0;
}
