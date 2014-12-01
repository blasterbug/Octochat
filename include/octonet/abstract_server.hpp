//          Copyright Alexis Giraudet 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ABSTRACT_SERVER_HPP
#define ABSTRACT_SERVER_HPP

#include <boost/asio.hpp>

/*!
 * \class abstract_server
 * \brief Classe abstract_server, classe abstraite représentant un serveur.
 */
class abstract_server
{
public:

	/*!
	 * \brief Destructeur par défaut de abstract_server.
	 */
    virtual ~abstract_server(void) {}

    /*!
     * \brief Arrête le serveur.
     */
    virtual void stop(void) = 0;

    /*!
     * \brief Démarre le serveur.
     */
    virtual void run(void) = 0;

    /*!
     * \brief Retourne le port d'écoute du serveur.
     * \return le port d'écoute du serveur
     */
    virtual unsigned short port(void) = 0;

    /*!
     * \brief Retourne l'adresse IP du serveur.
     * \return l'adresse IP du serveur
     */
    virtual boost::asio::ip::address ip_address(void) = 0;
};

#endif
