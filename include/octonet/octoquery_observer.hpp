//          Copyright Alexis Giraudet 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCTOQUERY_OBSERVER_HPP
#define OCTOQUERY_OBSERVER_HPP

#include <string>

#include "octoquery.hpp"

/*!
 * \class octoquery_observer
 * \brief Classe octoquery_observer, est notifiée lors de la réception d'une nouvelle requête.
 */
class octoquery_observer
{
    public:

		/*!
		 * \brief Destructeur par défaut.
		 */
		virtual ~octoquery_observer(void) {}

		/*!
		 * \brief Méthode appelée lors de la réception d'une nouvelle requête correspondant à l'identifiant de l'application (ou bien si l'identifiant de l'application est vide).
		 * \param _query : la requête
		 */
        virtual void update_query(const octoquery& _query) = 0;

		/*!
		 * \brief Retourne l'identifiant de l'application.
		 * \return l'identifiant
		 */
        virtual std::string app() const = 0;
};

#endif
