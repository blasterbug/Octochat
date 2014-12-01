//          Copyright Alexis Giraudet 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef OCTOPEER_OBSERVER_HPP
#define OCTOPEER_OBSERVER_HPP

#include "octopeer.hpp"

/*!
 * \class octopeer_observer
 * \brief Classe octopeer_observer, observateur de pairs, est notifiée du changement de l'état d'un pair.
 */
class octopeer_observer
{
public:

    /*!
     * \brief Destructeur par défaut.
     */
    virtual ~octopeer_observer(void) {}

    /*!
     * \brief Méthode appelée lors du changement de l'état d'un pair.
     * \param _peer : le pair
     * \param _state : l'état du pair
     */
    virtual void update_peer(const octopeer& _peer, octopeer_state _state) = 0;
};

#endif
