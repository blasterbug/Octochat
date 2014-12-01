//          Copyright Alexis Giraudet 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "octonet/octonet.hpp"
#include "octonet/octopeer.hpp"
#include "octonet/octopeer_observer.hpp"
#include "octonet/octoquery.hpp"
#include "octonet/octoquery_observer.hpp"

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <string>

#define OCTOGLOBALCHAT_APP_ID "OCTOGLOBALCHAT"

class octoglobalchat : public octopeer_observer, public octoquery_observer
{
private:
    boost::mutex out_mtx_;
    const std::string app_;
    const std::string uuid_;
public:
    octoglobalchat(std::string _uuid) : app_(OCTOGLOBALCHAT_APP_ID), uuid_(_uuid) {}

    virtual void update_peer(const octopeer& _peer, octopeer_state _state)
    {
        boost::lock_guard<boost::mutex> guard(out_mtx_);
        std::cout << "*** " << _peer.ip_address << ":" << _peer.tcp_port << " ";
        switch(_state)
        {
        case online :
            std::cout << "has joined";
            break;
        case offline :
            std::cout << "has left";
            break;
        default :
            std::cout << "is a jedi";
            break;
        }
        std::cout << std::endl;
    }

    virtual void update_query(const octoquery& _query)
    {
        if(_query.headers_map.find(octonet_uuid_header)->second == uuid_)
        {
            return;
        }

        boost::lock_guard<boost::mutex> guard(out_mtx_);
        std::cout << "[time] <" << _query.headers_map.find(octonet_ip_address_header)->second << ":" << _query.headers_map.find(octonet_tcp_port_header)->second << "> " << _query.content_str << std::cout << std::endl;
    }

    virtual std::string app() const
    {
        return app_;
    }
};

int main(void)
{
    octonet net;
    octoglobalchat globalchat(net.uuid());
    net.add_peer_observer(&globalchat);
    net.add_query_observer(&globalchat);
    net.run();
    std::string line;
    while(std::getline(std::cin, line))
    {
        octoquery query;
        query.headers_map[octonet_app_id_header] = OCTOGLOBALCHAT_APP_ID;
        query.content_str = line;
        std::set<octopeer, octopeer_comparator> peers;
        net.peers(peers);
        for(std::set<octopeer, octopeer_comparator>::const_iterator peer=peers.begin(); peer!=peers.end(); ++peer)
        {
            net.send_query(*peer, query);
        }
    }
    return 0;
}
