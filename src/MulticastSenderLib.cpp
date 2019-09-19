#include "MulticastSenderLib.hpp"

const int max_message_count = 5;

MulticastSenderLib::MulticastSenderLib(boost::asio::io_service &io_service, const boost::asio::ip::address &multicast_address, const short multicast_port)
    : endpoint_(multicast_address, multicast_port),
      socket_(io_service, endpoint_.protocol()),
      timer_(io_service),
      message_count_(0)
{
    LOG("MulticastSenderLib Constructor");
}

MulticastSenderLib::~MulticastSenderLib()
{
    LOG("MulticastSenderLib Destructor");    
    this->socket_.close();
}

void MulticastSenderLib::on_timer(const boost::system::error_code &error)
{
    if (!error)
    {
        LOG("MulticastSenderLib::on_timer timeout");
        this->AsyncSendTo("timeout");
    }
    else
    {
        LOG("MulticastSenderLib::on_timer error");
    }
}

void MulticastSenderLib::AsyncSendTo(std::string origin)
{

    LOG("Sending " << origin << " Message " << message_count_);

    std::ostringstream message;
    message << "Message " << message_count_++;

    auto buffer = boost::asio::buffer(message.str());
    socket_.send_to(buffer, endpoint_);

    if (message_count_ < max_message_count)
    {
        timer_.expires_from_now(boost::posix_time::seconds(1));
        timer_.async_wait(boost::bind(&MulticastSenderLib::on_timer, this, boost::asio::placeholders::error));
    }
}

int MulticastSenderLib::Test1()
{
    return 1;
}

int MulticastSenderLib::Test2()
{
    return 2;
}

// estática
void MulticastSenderLib::Run(const std::string FileName, const std::string Address, const short Port)
{

    LOG("MulticastSender Run " << Address << ":" << Port << " de " << FileName);
    auto multicast_address = boost::asio::ip::address::from_string(Address);

    try
    {
        boost::asio::io_service service;
        MulticastSenderLib s(service, multicast_address, Port);

        s.AsyncSendTo("stack");
        service.run();
    }
    catch (std::exception &e)
    {
        std::cerr << boost::posix_time::microsec_clock::local_time() << " Exception: " << e.what() << "\n";
    }
}
