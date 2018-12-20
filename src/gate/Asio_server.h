//
// Created by mayn on 2018/11/24.
//

#ifndef HFT_CPP_CLIENT_ASIO_SERVER_H
#define HFT_CPP_CLIENT_ASIO_SERVER_H


class Asio_server {
public:
    static Asio_server *getInstance();

private:
    static Asio_server *asio_server;
    Asio_server();
    Asio_server(const Asio_server &);

    Asio_server &operator=(const Asio_server &);

};


#endif //HFT_CPP_CLIENT_ASIO_SERVER_H
