#include <fstream>
#include <regex>
#include "LoggingLib.hpp"
#include "MulticastSenderLib.hpp"
#include "Helpers.hpp"

const int MAX_MESSAGE_COUNT = 5;

MulticastSenderLib::MulticastSenderLib(boost::asio::io_service &io_service, const boost::asio::ip::address &multicast_address, const short multicast_port)
    : endpoint_(multicast_address, multicast_port),
      socket_(io_service, endpoint_.protocol()),
      timer_(io_service),
      message_count_(0)
{
    Logging::Info("MulticastSenderLib Constructor");
}

MulticastSenderLib::~MulticastSenderLib()
{
    Logging::Info("MulticastSenderLib Destructor");
    this->socket_.close();
}

void MulticastSenderLib::on_timer(const boost::system::error_code &error)
{
    if (!error)
    {
        Logging::Info("MulticastSenderLib::on_timer timeout");
        this->AsyncSendTo("timeout");
    }
    else
    {
        Logging::Info("MulticastSenderLib::on_timer error");
    }
}

void MulticastSenderLib::AsyncSendTo(std::string origin)
{

    std::stringstream s ;
    s << "Sending " << origin << " Message " << message_count_ ;
    Logging::Info(s);

    std::ostringstream message;
    message << "Message " << message_count_++;

    auto buffer = boost::asio::buffer(message.str());
    socket_.send_to(buffer, endpoint_);

    if (message_count_ < MAX_MESSAGE_COUNT)
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
    std::stringstream s ;

    // adicionamos el home
    auto ConvertedFileName = std::regex_replace( FileName, std::regex("^\\~"), getenv("HOME") ) ;

    s.str("");
    s << "MulticastSender Run " << Address << ":" << Port << " de " << ConvertedFileName;
    Logging::Info(s);

    std::ifstream myfile( ConvertedFileName );
    if( !myfile.is_open() )
    {
        s.str("");
        s << "File " << ConvertedFileName << " cannot be open" ;
        Logging::Error(s);
        return ;
    }
    else
    {
        int i = 0 ;
        std::string line ;
        for( int i = 0 ; i < MAX_MESSAGE_COUNT && getline( myfile, line ); i++ )
        {
            Logging::Info( line );

            auto buffer = line.substr(25, line.length() - 42 ) ;
            if( buffer.length() >= 18)
            {
                Logging::Warn( buffer );

                auto binary = Helpers::base64_decode( buffer ) ;

                auto secuencia = Helpers::GetSecuenciaBiva( binary );
                s.str("");
                s << secuencia ;
                Logging::Error( s );
            }

        }
        myfile.close();
    }


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
        s.str(e.what());
        Logging::Error(s);
    }
}
