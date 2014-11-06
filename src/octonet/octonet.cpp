#include "octonet/octonet.hpp"

octonet::octonet()
{
    ;
}

octonet::~octonet()
{
    ;
}

bool octonet::add_query_observer(octoquery_observer *oq_obs)
{
    return (query_observers.insert(oq_obs)).second;
}

bool octonet::rem_query_observer(octoquery_observer *oq_obs)
{
    return query_observers.erase(oq_obs) > 0;
}

bool octonet::add_peer_observer(octopeer_observer *op_obs)
{
    return (peer_observers.insert(op_obs)).second;
}

bool octonet::rem_peer_observer(octopeer_observer *op_obs)
{
    return peer_observers.erase(op_obs) > 0;
}

bool octonet::send_query(const octopeer &op, const octoquery &oq) const
{
    return false;
}

void octonet::_notify_query_observers(const octoquery &oq) const
{
	std::set<octoquery_observer*>::const_iterator it;
    const char* app_obs;
    const char* app_que = oq.get_header(APP_HEADER);

    for(it=query_observers.begin(); it!=query_observers.end(); ++it)
    {
        app_obs = (*it)->get_app();
        if((app_obs == 0) || ((app_que != 0) && (std::strcmp(app_obs, app_que) == 0)))
        {
			(*it)->update_query(oq);
		}
    }
}

void octonet::_notify_peer_observers(const octopeer &op) const
{
	std::set<octopeer_observer*>::const_iterator it;

    for(it=peer_observers.begin(); it!=peer_observers.end(); ++it)
    {
        (*it)->update_peer(op);
    }
}
