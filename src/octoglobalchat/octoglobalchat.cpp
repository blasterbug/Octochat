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
    const std::string ip_address_;
    const std::string tcp_port_;
public:
    octoglobalchat(boost::asio::ip::address _ip_address, unsigned short _tcp_port) : app_(OCTOGLOBALCHAT_APP_ID), ip_address_(_ip_address.to_string()), tcp_port_(boost::lexical_cast<std::string>(_tcp_port)) {}
    octoglobalchat(void) {}

    virtual void update_peer(const octopeer& _peer, octopeer_state _state)
    {
        boost::lock_guard<boost::mutex> guard(out_mtx_);
        std::cout << "*** " << _peer.ip_address << ":" << _peer.tcp_port << " ";
        switch(_state)
        {
            case online : std::cout << "has joined"; break;
            case offline : std::cout << "has left"; break;
            default : std::cout << "is a jedi"; break;
        }
        std::cout << std::endl;
    }

    virtual void update_query(const octoquery& _query)
    {

		std::map<std::string, std::string>::const_iterator ip_it = _query.headers_map.find(octonet_ip_address_header);
		std::map<std::string, std::string>::const_iterator tcp_it = _query.headers_map.find(octonet_tcp_port_header);
		if((ip_it == _query.headers_map.end()) || (tcp_it == _query.headers_map.end()))
		{
			return;
		}

		std::string ip_address = ip_it->second;
		std::string tcp_port = tcp_it->second;
		if((ip_address == ip_address_) && (tcp_port == tcp_port_))
		{
			return;
		}

        boost::lock_guard<boost::mutex> guard(out_mtx_);
        std::cout << "[time] <" << ip_address << ":" << tcp_port << "> " << _query.content_str << std::cout << std::endl;
    }

    virtual std::string app() const
    {
        return app_;
    }
};

int main(void)
{
    octoglobalchat globalchat;
    octonet net;
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
