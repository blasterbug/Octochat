#ifndef OCTOPEER_OBSERVER_HPP
#define OCTOPEER_OBSERVER_HPP

#include "octopeer.hpp"

class octopeer_observer
{
    public:
		virtual ~octopeer_observer(void) {}
        virtual void update_peer(const octopeer& _peer, octopeer_state _state) = 0;
};

#endif
