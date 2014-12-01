//          Copyright Alexis Giraudet 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "octonet/octonet_manager.hpp"
#include "octonet/octopeer.hpp"
#include "octonet/udp_server.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>
#include <ios>
#include <sstream>

udp_server::udp_server(octonet_manager* _net_manager, unsigned short _port) : net_manager_(_net_manager), sock_(io_service_, udp::endpoint(udp::v4(), _port))
{
	ip_address_ = sock_.local_endpoint().address();
    port_ = sock_.local_endpoint().port();
}

void udp_server::stop(void)
{
    io_service_.stop();
}

void udp_server::run(void)
{
    data_len_ = octonet_version_header.size() + octonet_port_header_length;
    data_buf_.reset(new char(data_len_));
    start_receive();
    io_service_.run();
}

unsigned short udp_server::port(void)
{
    return port_;
}

boost::asio::ip::address udp_server::ip_address(void)
{
	return ip_address_;
}

void udp_server::start_receive(void)
{
    sock_.async_receive_from(
        boost::asio::buffer(data_buf_.get(), data_len_), remote_endpoint_,
        boost::bind(&udp_server::handle_receive, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void udp_server::handle_receive(const boost::system::error_code& _error, std::size_t _bytes_recvd)
{
#   ifdef OCTONET_LOG_ENABLE
    BOOST_LOG_TRIVIAL(info) << "udp_server::handle_receive: start " << remote_endpoint_.address() << ":" << remote_endpoint_.port();
#   endif
    if (!_error && (_bytes_recvd == data_len_) && (octonet_version_header == std::string(data_buf_.get(), octonet_version_header.size())))
    {
        std::istringstream tcp_is(std::string(data_buf_.get() + octonet_version_header.size(), octonet_port_header_length));
        unsigned short tcp_port = 0;
        if(!(tcp_is >> std::hex >> tcp_port))//TODO: remove if(!... -> if(...
        {
            ;
        }
        else
        {
#           ifdef OCTONET_LOG_ENABLE
            BOOST_LOG_TRIVIAL(info) << "udp_server::handle_receive: OK " << remote_endpoint_.address() << ":" << remote_endpoint_.port();
#           endif
            octopeer peer(remote_endpoint_.address(), tcp_port);
            net_manager_->add_peer(peer);
        }
    }
    start_receive();
}
