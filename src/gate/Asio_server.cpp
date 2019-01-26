//
// Created by mayn on 2018/11/24.
//

#include "Asio_server.h"

Asio_server *Asio_server::asio_server = nullptr;

Asio_server *Asio_server::getInstance()
{
    if (nullptr == asio_server)
        asio_server = new Asio_server();
    return asio_server;
}

Asio_server::Asio_server()
{
}
