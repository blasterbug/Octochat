#ifndef SERVER_FACTORY_HPP
#define SERVER_FACTORY_HPP

#include "tcp_server.hpp"
#include "udp_server.hpp"

enum server_type { tcp, udp };

class server_factory
{
private:
    octonet_manager* octonet_manager_;
public:
    server_factory(octonet_manager* _octonet_manager) : octonet_manager_(_octonet_manager) {}
    abstract_server* create_server(server_type _type, unsigned short _port)
    {
        switch(type)
        {
            case tcp: return new tcp_server(octonet_manager_, _port);
            case udp: return new udp_server(octonet_manager_, _port);
        }
    }
};

#endif
