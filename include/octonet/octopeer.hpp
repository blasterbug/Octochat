#ifndef OCTOPEER_HPP
#define OCTOPEER_HPP

#include <boost/asio.hpp>

struct octopeer
{
    boost::asio::ip::tcp::endpoint endpoint;
    octopeer(const octopeer &op) : endpoint(op.endpoint) {}
};

#endif
