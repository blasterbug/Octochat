//          Copyright Alexis Giraudet 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "octonet/octonet.hpp"
#include "octonet/octopeer.hpp"
#include "octonet/octopeer_observer.hpp"
#include "octonet/octoquery.hpp"
#include "octonet/octoquery_observer.hpp"

#include <boost/thread/thread.hpp>
#include <iostream>
#include <string>

class octowatch : public octopeer_observer, public octoquery_observer
{
private:
    boost::mutex out_mtx_;
    std::string app_;
public:
    octowatch(void) {}
    octowatch(const std::string& _app) : app_(_app) {}

    virtual void update_peer(const octopeer& _peer, octopeer_state _state)
    {
        boost::lock_guard<boost::mutex> guard(out_mtx_);
        std::cout << "update peer: " << _peer.ip_address << ":" << _peer.tcp_port << " ";
        switch(_state)
        {
            case online : std::cout << "online"; break;
            case offline : std::cout << "offline"; break;
            default : std::cout << "???"; break;
        }
        std::cout << std::endl;
    }

    virtual void update_query(const octoquery& _query)
    {
        boost::lock_guard<boost::mutex> guard(out_mtx_);
        std::cout << "update query:";
        for(std::map<std::string, std::string>::const_iterator it=_query.headers_map.begin(); it!=_query.headers_map.end(); ++it)
        {
            std::cout << " " << it->first << "=" << it->second;
        }
        std::cout << std::endl;
    }

    virtual std::string app() const
    {
        return app_;
    }
};

int main(void)
{
    octowatch watch;
    octonet net;
    net.add_peer_observer(&watch);
    net.add_query_observer(&watch);
    net.run();
    std::string s;
    std::getline(std::cin, s);
    return 0;
}
