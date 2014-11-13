#ifndef OCTONET_HPP
#define OCTONET_HPP

#define OCTONET_VERSION "1"
#define OCTONET_HEADER "OCTONET"
#define APP_HEADER "APP"
#define CONTENT_LENGTH_HEADER "CONTENT_LENGTH"

#include <set>

#include "octoconnect_tcp.hpp"
#include "octopeer.hpp"
#include "octoquery.hpp"
#include "octopeer_observer.hpp"
#include "octoquery_observer.hpp"

class octonet
{
    private:
        std::set<octoquery_observer*> query_observers;
        std::set<octopeer_observer*> peer_observers;
        //TODO : think about const members
        unsigned short __tcp_port;
        unsigned short __udp_port;

    protected:
        void _notify_query_observers(const octoquery &oq) const {}
        void _notify_peer_observers(const octopeer &op) const
        {
			std::set<octopeer_observer*>::const_iterator it;
			for(it=peer_observers.begin(); it!=peer_observers.end(); ++it)
			{
				(*it)->update_peer(op);
			}
		}

    public:
        octonet() {}
        ~octonet() {}
        bool add_query_observer(octoquery_observer *oq_obs) { return (query_observers.insert(oq_obs)).second; }
        bool rem_query_observer(octoquery_observer *oq_obs) { return query_observers.erase(oq_obs) > 0; }
        bool add_peer_observer(octopeer_observer *op_obs) { return (peer_observers.insert(op_obs)).second; }
        bool rem_peer_observer(octopeer_observer *op_obs) { return peer_observers.erase(op_obs) > 0; }
        bool send_query(const octopeer &op, const octoquery &oq) const { return false; }
};

#endif
