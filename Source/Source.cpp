#include "Source.h"

#include "../Common/zhelpers.hpp"

#include <QDebug>
#include <QElapsedTimer>

Source::Source(int type)
    : IClient(type)
{
    _minPackSize = 50;
    _maxPackSize = 8'000;
    _sendRate = 10'000;
}

Source::Source(zmq::context_t contexts, zmq::socket_t socket)
    : IClient(std::move(contexts), std::move(socket))
{
    _minPackSize = 50;
    _maxPackSize = 8'000;
    _sendRate = 10'000;
}

/*
 * start infinite loop to send data and display detail
 */
void Source::start()
{
    QElapsedTimer time;
    int  totalSize=0;
    while(true)
    {
        time.start();
        totalSize = 0;
        for( int request = 0 ; request < 10'000 ; request++)
        {
            auto packet = _generateRandomPacket();
            s_sendmore(_socket, std::string("")); // Envelope delimiter
            s_send(_socket, packet);

            totalSize += packet.size(); // sum packet size in Byte (char is 1 Byte)
        }
        // run every loop under 1 second
        int waitTime = 800-time.elapsed();
        std::this_thread::sleep_for(std::chrono::milliseconds(waitTime>0? waitTime : 0));

        qDebug()<< "Send rate: "
                << (_sendRate*1000)/time.elapsed() << "p/s \t" // packet per second
                << totalSize/1'000 << "KB/s"; // total sent size in Byte per second
    }
}

void Source::setMinPackSize(int size)
{
    if(size < 0)
        return;
    _minPackSize = size;
}

void Source::setMaxPackSize(int size)
{
    if(size < 0)
        return;
    _maxPackSize = size;
}

void Source::setSendRate(int rate)
{
    if(rate < 0)
        return;
    _sendRate = rate;
}

/*
 * generate random packet size between minimum size and maximum size
 * packet filled with 'A' character
 */
std::string Source::_generateRandomPacket()
{
    std::string result;

    std::call_once(_srandFlag, [](){std::srand(std::time(nullptr));});

    auto packSize = (_minPackSize+std::rand())%_maxPackSize;
    result.resize(packSize,'A');

    return result;
}
