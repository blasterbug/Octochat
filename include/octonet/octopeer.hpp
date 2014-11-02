#ifndef OCTOPEER_HPP
#define OCTOPEER_HPP

#include <boost/asio.hpp>

struct octopeer
{
    boost::asio::ip::address ip_address;
    unsigned short tcp_port;
    unsigned short udp_port;

    octopeer(boost::asio::ip::address _ip_address, unsigned short _tcp_port, unsigned short _udp_port) : ip_address(_ip_address), tcp_port(_tcp_port), udp_port(_udp_port) {}
    octopeer(const octopeer &op) : ip_address(op.ip_address), tcp_port(op.tcp_port), udp_port(op.udp_port) {}
};

#endif
