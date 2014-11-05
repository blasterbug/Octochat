#ifndef OCTONET_HPP
#define OCTONET_HPP

#include <set>

#include "octopeer.hpp"
#include "octoquery.hpp"
#include "octopeer_observer.hpp"
#include "octoquery_observer.hpp"

class octonet
{
    private:
        //TODO : think about optimal container
        std::set<octoquery_observer*> query_observers;
        std::set<octopeer_observer*> peer_observers;
        //TODO : think about const members
        unsigned short __tcp_port;
        unsigned short __udp_port;
    protected:
        void _notify_query_observers(const octoquery &oq) const;
        void _notify_peer_observers(const octopeer &op) const;
    public:
        octonet();
        ~octonet();
        bool add_query_observer(const octoquery_observer *oq_obs);
        bool rem_query_observer(const octoquery_observer *oq_obs);
        bool add_peer_observer(const octopeer_observer *op_obs);
        bool rem_peer_observer(const octopeer_observer *op_obs);
        bool send_query(const octopeer &op, const octoquery &oq) const;
};

#endif
