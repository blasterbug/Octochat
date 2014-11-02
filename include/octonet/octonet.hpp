#ifndef OCTONET_HPP
#define OCTONET_HPP

#include "octopeer.hpp"
#include "octoquery.hpp"
#include "octopeer_observer.hpp"
#include "octoquery_observer.hpp"

class octonet
{
    private:
        unsigned short __tcp_port;
        unsigned short __udp_port;
    protected:
        void _notify_query_observer(const octoquery &oq) const;
        void _notify_peer_observer(const octopeer &op) const;
    public:
        octonet();
        ~octonet();
        bool add_query_observer(const octoquery_observer *oq_obs);
        bool rem_query_observer(const octoquery_observer *oq_obs);
        bool add_peer_observer(const octopeer_observer *op_obs);
        bool rem_peer_observer(const octopeer_observer *op_obs);
};

#endif
