#ifndef SESSION_H
#define SESSION_H
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
class session : public std::enable_shared_from_this<session>
{
  private:
    tcp::socket socket_;
    std::array<char, 1024> data_;
    handler_memory handler_memory_;
    void do_read();
    void do_write(std::size_t length);

  public:
    session(tcp::socket socket);
    void start();
    ~session();
};

template <typename Handler>
inline custom_alloc_handler<Handler> make_custom_alloc_handler(handler_memory &m, Handler h)
{
    return custom_alloc_handler<Handler>(m, h);
}

#endif