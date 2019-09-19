#pragma once
// http://www.boost.org/doc/libs/1_37_0/doc/html/boost_asio/example/multicast/sender.cpp

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// Ver https://code.visualstudio.com/docs/languages/cpp cuando haya problemas con paths

#ifndef LOG
#define LOG(x)                                                         \
    {                                                                  \
        std::stringstream str;                                         \
        str << boost::posix_time::microsec_clock::local_time();        \
        std::cout << str.str().substr(0, 24) << " " << x << std::endl; \
    }
#endif

class MulticastSenderLib
{

    boost::asio::ip::udp::endpoint endpoint_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::deadline_timer timer_;

    int message_count_;
    std::ifstream inFile;

    void AsyncSendTo(std::string origin);

public:
    static int Test1();
    static int Test2();

    MulticastSenderLib(boost::asio::io_service &io_service, const boost::asio::ip::address &multicast_address, const short multicast_port);
    ~MulticastSenderLib();

    void on_timer(const boost::system::error_code &error);

    static void Run(const std::string FileName, const std::string Address, const short Port);
};