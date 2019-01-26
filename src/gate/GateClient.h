#ifndef GATECLIENT_H
#define GATECLIENT_H

#include <boost/asio.hpp>
#include <queue>
#include <iostream>
#include "common/protomessage/ProtoMessage.h"
using boost::asio::ip::tcp;

typedef std::queue<ProtoMessage> ProtoMessageQueue;

class GateClient
{
private:
    /* data */
public:
    GateClient(boost::asio::io_context &io_context,
                const tcp::resolver::results_type &endpoints);
    ~GateClient();

public:
    void write(const ProtoMessage &msg);
    void close();

private:
    void do_connect(const tcp::resolver::results_type &endpoints);
    void do_read_header();
    void do_read_body();
    void do_write();

private:
    boost::asio::io_context &io_context_;
    tcp::socket socket_;
    ProtoMessage read_msg_;
    ProtoMessageQueue write_msgs_;
};

#endif