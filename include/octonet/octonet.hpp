//          Copyright Alexis Giraudet 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCTONET_HPP
#define OCTONET_HPP

#include <boost/asio.hpp>

#include "octonet_manager.hpp"
#include "octopeer.hpp"
#include "octopeer_observer.hpp"
#include "octoquery.hpp"
#include "octoquery_observer.hpp"

/*!
 * \class octonet
 * \brief Classe octonet, permet d'abonner les observeurs et d'envoyer les requêtes.
 */
class octonet
{
private:
    octonet_manager net_manager_;
public:
    /*!
     * \brief Constructeur par défaut de octonet.
     */
    octonet(void) : net_manager_(octonet_default_tcp_port, octonet_default_udp_port) {}

    /*!
     * \brief Constructeur permettant de paramétrer les ports UDP/TCP de octonet.
     * \param _tcp_port : le port d'écoute TCP
     * \param _udp_port : le port d'écoute UDP
     */
    octonet(unsigned short _tcp_port, unsigned short _udp_port) : net_manager_(_tcp_port, _udp_port) {}

    /*!
     * \brief Retourne l'UUID.
     * \return l'UUID
     */
    std::string uuid(void) const
    {
        return net_manager_.uuid();
    }

    /*!
     * \brief Retourne l'adresse IP.
     * \return l'adresse IP
     */
    boost::asio::ip::address ip_address(void) const
    {
        return net_manager_.ip_address();
    }

    /*!
     * \brief Retourne le port TCP.
     * \return le port TCP
     */
    unsigned short tcp_port(void) const
    {
        return net_manager_.tcp_port();
    }

    /*!
     * \brief Retourne le port UDP.
     * \return le port UDP
     */
    unsigned short udp_port(void) const
    {
        return net_manager_.udp_port();
    }

    /*!
     * \brief Remplit l'ensemble passé en paramètre avec touts les pairs en ligne.
     * \param _peers : l'ensemble de pairs à remplir
     * \return l'ensemble de pairs
     */
    std::set<octopeer, octopeer_comparator>& peers(std::set<octopeer, octopeer_comparator>& _peers)
    {
        return net_manager_.peers(_peers);
    }

    /*!
     * \brief Ajoute un observeur de requêtes.
     * \param _query_observer : l'observeur de requêtes
     * \return vrai si l'observeur de requêtes à bien été ajouté, sinon faux
     */
    bool add_query_observer(octoquery_observer* _query_observer)
    {
        return net_manager_.add_query_observer(_query_observer);
    }

    /*!
     * \brief Supprime un observeur de requêtes.
     * \param _query_observer : l'observeur de requêtes
     * \return vrai si l'observeur de requêtes à bien été supprimé, sinon faux
     */
    bool rem_query_observer(octoquery_observer* _query_observer)
    {
        return net_manager_.rem_query_observer(_query_observer);
    }

    /*!
     * \brief Ajoute un observeur de pairs.
     * \param _query_observer : l'observeur de pairs
     * \return vrai si l'observeur de pairs à bien été ajouté, sinon faux
     */
    bool add_peer_observer(octopeer_observer* _peer_observer)
    {
        return net_manager_.add_peer_observer(_peer_observer);
    }

    /*!
     * \brief Supprime un observeur de pairs.
     * \param _query_observer : l'observeur de pairs
     * \return vrai si l'observeur de pairs à bien été supprimé, sinon faux
     */
    bool rem_peer_observer(octopeer_observer* _peer_observer)
    {
        return net_manager_.rem_peer_observer(_peer_observer);
    }

    /*!
     * \brief Lance les services d'entrées/sorties.
     */
    void run(void)
    {
        net_manager_.run();
    }

    /*!
     * \brief Envoie une requête.
     * \param _peer : le destinataire
     * \param _query : la requête
     * \return vrai si la requête a bien été envoyée, sinon faux
     */
    bool send_query(const octopeer& _peer, octoquery& _query)
    {
        return net_manager_.send_query(_peer, _query);
    }

    /*!
     * \brief Émet un broadcast UDP.
     * \param _port : le port de destination
     * \return vrai si le broadcast a bien été émis, sinon faux
     */
    bool send_broadcast(unsigned short _port)
    {
        return net_manager_.send_broadcast(_port);
    }
};

#endif
