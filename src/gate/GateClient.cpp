#include "GateClient.h"


GateClient::GateClient(boost::asio::io_context &io_context,
                const tcp::resolver::results_type &endpoints)
                : io_context_(io_context), socket_(io_context)
{
    do_connect(endpoints);
}

GateClient::~GateClient()
{
}

void GateClient::write(const ProtoMessage &msg)
{
    boost::asio::post(io_context_, [this, msg]() {
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push(msg);
        if (!write_in_progress)
        {
            do_write();
        }
    });
}
void GateClient::close()
{
    boost::asio::post(io_context_, [this]() { socket_.close(); });
}

void GateClient::do_connect(const tcp::resolver::results_type &endpoints)
{
    std::cout << (*endpoints).host_name() << "do connect\n";
    boost::asio::async_connect(
        socket_,
        endpoints,
        [this](boost::system::error_code ec, tcp::endpoint) {
            if (!ec)
            {
                std::cout << "connect success\n";
                do_read_header();
            }
            else
            {
                std::cout << "connect wrong! error msg:" << ec.message() << std::endl;
            }
        });
}

void GateClient::do_read_header()
{
    std::cout << "reading header\n";
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(read_msg_.data(), ProtoMessage::HEADER_LENGTH),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec && read_msg_.decode_header())
            {
                do_read_body();
            }
            else
            {
                socket_.close();
            }
        });
}

void GateClient::do_read_body()
{
    boost::asio::async_read(
        socket_,
        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec)
            {
                std::cout.write(read_msg_.body(), read_msg_.body_length());
                do_read_header();
            }
            else
            {
                std::cout << ec.message() << std::endl;
                socket_.close();
            }
        });
}

void GateClient::do_write()
{
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(write_msgs_.front().data(),
                            write_msgs_.front().length()),
        [this](boost::system::error_code ec, std::size_t length) {
            INFO("write message length?:", length);
            if (!ec)
            {
                write_msgs_.pop();
                if (!write_msgs_.empty())
                {
                    do_write();
                }
            }
            else
            {
                socket_.close();
            }
        });
}