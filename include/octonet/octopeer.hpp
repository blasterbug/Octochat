#ifndef OCTOPEER_HPP
#define OCTOPEER_HPP

#include <boost/asio.hpp>

struct octopeer
{
    boost::asio::ip::address ip_address;
    unsigned short tcp_port;

    octopeer(boost::asio::ip::address _ip_address, unsigned short _tcp_port) : ip_address(_ip_address), tcp_port(_tcp_port) {}
    octopeer(const octopeer &op) : ip_address(op.ip_address), tcp_port(op.tcp_port) {}
};

struct octopeer_comparator
{
    bool operator()(const octopeer &lhs, const octopeer &rhs) const
    {
        return lhs.ip_address < rhs.ip_address;
    }
};

#endif
