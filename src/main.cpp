#include <iostream>
#include <list>
#include <string>
#include "asio/chat/chat_client.h"
#include <boost/asio.hpp>
#include <boost/array.hpp>

int main(int argc, char *argv[])
{

    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage:chat_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(argv[1], argv[2]);
        chat_client c(io_context, endpoints);

        std::thread t([&io_context]() { io_context.run(); });

        char line[chat_message::MAX_BODY_LENGTH + 1];
        while (std::cin.getline(line, chat_message::MAX_BODY_LENGTH))
        {
            chat_message msg;
            msg.body_length(std::strlen(line));
            std::memcpy(msg.body(), line, msg.body_length());
            msg.encode_header();
            c.write(msg);
        }
        c.close();
        t.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}