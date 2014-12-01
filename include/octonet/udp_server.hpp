//          Copyright Alexis Giraudet 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>

#include "abstract_server.hpp"

using boost::asio::ip::udp;

class octonet_manager;

class udp_server : public abstract_server
{
private:
    boost::asio::io_service io_service_;
    octonet_manager* net_manager_;
    boost::asio::ip::address ip_address_;
    unsigned short port_;
    udp::socket sock_;
    udp::endpoint remote_endpoint_;
    boost::scoped_array<char> data_buf_;
    std::size_t data_len_;

    void start_receive(void);
    void handle_receive(const boost::system::error_code& _error, std::size_t _bytes_recvd);

public:
    udp_server(octonet_manager* _net_manager, unsigned short _port);
    virtual void stop(void);
    virtual void run(void);
    virtual unsigned short port(void);
    virtual boost::asio::ip::address ip_address(void);
};

#endif
