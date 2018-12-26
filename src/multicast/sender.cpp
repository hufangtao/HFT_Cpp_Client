#include <boost/asio.hpp>
#include <iostream>
#include <sstream>
#include <string>

constexpr short multicast_port = 30001;
constexpr int max_message_count = 100;

class sender
{
  private:
    boost::asio::ip::udp::endpoint endpoint_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::steady_timer timer_;
    int message_count_;
    std::string message_;

    void do_send()
    {
        std::string temp;
        std::cout<<"enter msg---------"<<std::endl;
        std::cin>>temp;
        std::ostringstream os;
        os << "Senderhu says:" << message_count_++<<temp;
        message_ = os.str();

        socket_.async_send_to(boost::asio::buffer(message_), endpoint_,
                              [this](boost::system::error_code ec, std::size_t length) {
                                  if (!ec && message_count_ < max_message_count)
                                  {
                                      /* code */
                                      do_timeout();
                                  }
                              });
    }

    void do_timeout()
    {
        timer_.expires_after(std::chrono::seconds(1));
        timer_.async_wait(
            [this](boost::system::error_code ec) {
                if (!ec)
                {
                    /* code */
                    do_send();
                }
            });
    }

  public:
    sender(boost::asio::io_context &io_context,
    const boost::asio::ip::address &multicast_address):endpoint_(multicast_address, multicast_port),
    socket_(io_context, endpoint_.protocol()),timer_(io_context),message_count_(0){
        do_send();
    }
};
