#ifndef OCTOPEER_OBSERVER_HPP
#define OCTOPEER_OBSERVER_HPP

#include "octopeer.hpp"

class octopeer_observer
{
    public:
		virtual ~octopeer_observer(void) {}
        virtual void update_peer(const octopeer &op, octopeer_state s) = 0;
};

#endif
