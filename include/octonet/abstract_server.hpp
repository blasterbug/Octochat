#ifndef ABSTRACT_SERVER_HPP
#define ABSTRACT_SERVER_HPP

#include <boost/asio.hpp>

class abstract_server
{
public:
    virtual ~abstract_server(void) {}
    virtual void stop(void) = 0;
    virtual void run(void) = 0;
    virtual unsigned short port(void) = 0;
    virtual boost::asio::ip::address ip_address(void) = 0;
};

#endif
