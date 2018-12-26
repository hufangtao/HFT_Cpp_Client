#ifndef ALLOCATION_SERVER_H
#define ALLOCATION_SERVER_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class allocation_server
{
  private:
    tcp::acceptor acceptor_;
    void do_accept();

  public:
    allocation_server(boost::asio::io_context &io_context, short port);
};


#endif