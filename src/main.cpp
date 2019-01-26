#include <iostream>
#include <list>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "common/proto/Pmd.pb.h"
#include "common/proto/AccPmd.pb.h"


#include "gate/GateClient.h"

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
        GateClient c(io_context, endpoints);

        std::thread t([&io_context]() { io_context.run(); });

        char line[ProtoMessage::MAX_BODY_LENGTH + 1];
        while (std::cin.getline(line, ProtoMessage::MAX_BODY_LENGTH))
        {
            PlatPmd::LoginAccPmd_C2S loginMsg;
            loginMsg.set_platform("1222");
            loginMsg.set_channel_open_id("86597281346500");
            loginMsg.set_game_account_id("2200000147556");
            loginMsg.set_game_account_sign("qwe168+asd879qw");
            loginMsg.set_channel_param("aaaaa");
            ProtoMessage msg(loginMsg);
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