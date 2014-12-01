//          Copyright Alexis Giraudet 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SERVER_FACTORY_HPP
#define SERVER_FACTORY_HPP

#include "tcp_server.hpp"
#include "udp_server.hpp"

class octonet_manager;

enum server_type { tcp, udp };

/*!
 * \class server_factory
 * \brief Classe server_factory, construit des serveurs UDP/TCP.
 */
class server_factory
{
private:
    octonet_manager* net_manager_;
public:

    /*!
     * \brief Constructeur par défaut de server_factory.
     * \param _net_manager : l'octonet_manager
     */
    server_factory(octonet_manager* _net_manager) : net_manager_(_net_manager) {}

    /*!
     * \brief Construit un serveur UDP ou TCP en fonction d'un port d'écoute.
     * \param _type : le type de serveur
     * \param _port : le port d'écoute
     */
    abstract_server* create_server(server_type _type, unsigned short _port)
    {
        switch(_type)
        {
        case tcp:
            return new tcp_server(net_manager_, _port);
        case udp:
            return new udp_server(net_manager_, _port);
        }
        return 0;
    }
};

#endif
