#include "octonet/octonet.hpp"

octonet::octonet()
{
    ;
}

octonet::~octonet()
{
    ;
}

bool octonet::add_query_observer(const octoquery_observer *oq_obs)
{
    return (query_observers.insert(oq_obs)).second;
}

bool octonet::rem_query_observer(const octoquery_observer *oq_obs)
{
    return query_observers.erase(oq_obs) > 0;
}

bool octonet::add_peer_observer(const octopeer_observer *op_obs)
{
    return (peer_observers.insert(op_obs)).second;
}

bool octonet::rem_peer_observer(const octopeer_observer *op_obs)
{
    return peer_observers.erase(op_obs) > 0;
}

bool octonet::send_query(const octopeer &op, const octoquery &oq) const
{
    ;
}

void octonet::_notify_query_observers(const octoquery &oq) const
{
    char *app = 0;
    std::set<octoquery_observer*>::const_iterator fi = oq.headers.find("APP");
    if(fi != query_observers.end())
    {
        app = fi->second;
    }
    for(std::set<octoquery_observer*>::const_iterator it=query_observers.begin(); it!=query_observers.end(); ++it)
    {
        ;
    }
}

void octonet::_notify_peer_observers(const octopeer &op) const
{
    for(std::set<octopeer_observer*>::const_iterator it=peer_observers.begin(); it!=peer_observers.end(); ++it)
    {
        (*it)->update_peer(op);
    }
}
