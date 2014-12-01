//          Copyright Alexis Giraudet 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCTOPEER_HPP
#define OCTOPEER_HPP

#include <boost/asio.hpp>

enum octopeer_state { online, offline };

/*!
 * \struct octopeer
 * \brief Structure octopeer, correspond à un pair, identifié par une adresse IP et un port TCP.
 */
struct octopeer
{
    boost::asio::ip::address ip_address;
    unsigned short tcp_port;

    /*!
     * \brief Constructeur de octopeer.
     * \param _ip_address : l'adresse IP
     * \param _tcp_port : le port TCP
     */
    octopeer(boost::asio::ip::address _ip_address, unsigned short _tcp_port) : ip_address(_ip_address), tcp_port(_tcp_port) {}

    /*!
     * \brief Constructeur par recpie de octopeer.
     * \param _peer : le pair à recopier
     */
    octopeer(const octopeer& _peer) : ip_address(_peer.ip_address), tcp_port(_peer.tcp_port) {}
};

/*!
 * \struct octopeer_comparator
 * \brief Structure octopeer_comparator, comparateur de octopeer.
 */
struct octopeer_comparator
{
    bool operator()(const octopeer& lhs, const octopeer& rhs) const
    {
        return lhs.ip_address < rhs.ip_address;
    }
};

#endif
