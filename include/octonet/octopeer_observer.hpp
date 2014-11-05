#ifndef OCTOPEER_OBSERVER_HPP
#define OCTOPEER_OBSERVER_HPP

#include "octopeer.hpp"

class octopeer_observer
{
    public:
        virtual void update_peer(const octopeer &op) = 0;
};

#endif
