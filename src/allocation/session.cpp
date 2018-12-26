#include "session.h"

session::session(tcp::socket socket) : socket_(std::move(socket))
{
}

void session::start()
{
    do_read();
}

void session::do_read()
{
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_),
                            make_custom_alloc_handler(handler_memory_,
                                                       [this, self](boost::system::error_code ec, std::size_t length) {
                                                           if (!ec)
                                                           {
                                                               /* code */
                                                               do_write(length);
                                                           }
                                                       }));
}

void session::do_write(std::size_t length)
{
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
    make_custom_alloc_handler(handler_memory_,
    [this, self](boost:system::error_code ec, std::size_t length){
        if(!ec){
            do_read();
        }
    }));
}

session::~session()
{
}
