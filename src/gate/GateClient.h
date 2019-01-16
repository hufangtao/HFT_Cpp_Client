#ifndef GATECLIENT_H
#define GATECLIENT_H

#include <boost/asio.hpp>
#include <queue>
#include <iostream>
using boost::asio::ip::tcp;

class GateClient
{
private:
    /* data */
public:
    GateClient(boost::asio::io_context &io_context,
                const tcp::resolver::results_type &endpoints);
    ~GateClient();
};

#endif