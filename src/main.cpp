#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "multicast/sender.cpp"
int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage:sender <multicast_address>\n";
            std::cerr << "For IPv4, try\n";
            std::cerr << "    sender 239.255.0.1\n";
            std::cerr << "For IPv6, try\n";
            std::cerr << "    sender ff31::8000:1234\n";
            return 1;
        }
        boost::asio::io_context io_context;
        sender s(io_context, boost::asio::ip::make_address(argv[1]));
        io_context.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}