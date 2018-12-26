#include "allocation_server.h"

allocation_server::allocation_server(boost::asio::io_context &io_context, short port):
acceptor_(io_context, tcp::endpoint(tcp::v4(), port)){
    do_accept();
}

void allocation_server::do_accept(){
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket){
            if(!ec){
                std::make_shared<session>(std::move(socket))->start();
            }
            do_accept();
        }
    )
}