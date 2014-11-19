#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

#include "abstract_server.hpp"

class udp_server : public abstract_server
{
private:
    octonet_manager octonet_manager_;
    unsigned short port_;
public:
    udp_server(octonet_manager _octonet_manager, unsigned short _port) : octonet_manager_(_octonet_manager), port_(_port) {}
    virtual void run(void) {}
    virtual unsigned short port(void) {}
};

#endif
