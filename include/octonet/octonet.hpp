#ifndef OCTONET_HPP
#define OCTONET_HPP

#include <boost/asio.hpp>

#include "octonet_manager.hpp"
#include "octopeer.hpp"
#include "octopeer_observer.hpp"
#include "octoquery.hpp"
#include "octoquery_observer.hpp"

/*!
 * \class octonet
 * \brief 
 */
class octonet
{
private:
    octonet_manager net_manager_;
public:
    /*!
     * \brief 
     */
    octonet(void) : net_manager_(octonet_default_tcp_port, octonet_default_udp_port) {}

    /*!
     * \brief 
     */
    octonet(unsigned short _tcp_port, unsigned short _udp_port) : net_manager_(_tcp_port, _udp_port) {}

    /*!
     * \brief 
     * \return 
     */
    boost::asio::ip::address ip_address(void)
    {
        return net_manager_.ip_address();
    }

    /*!
     * \brief 
     * \return 
     */
    unsigned short tcp_port(void)
    {
        return net_manager_.tcp_port();
    }

    /*!
     * \brief 
     * \return 
     */
    unsigned short udp_port(void)
    {
        return net_manager_.udp_port();
    }

	/*!
	 * \brief 
	 * \param _peers : 
	 * \return 
	 */
	 std::set<octopeer, octopeer_comparator>& peers(std::set<octopeer, octopeer_comparator>& _peers)
	 {
		 return net_manager_.peers(_peers);
	 }

    /*!
     * \brief 
     * \param _query_observer : 
     * \return 
     */
    bool add_query_observer(octoquery_observer* _query_observer)
    {
        return net_manager_.add_query_observer(_query_observer);
    }
    
    /*!
     * \brief 
     * \param _query_observer : 
     * \return 
     */
    bool rem_query_observer(octoquery_observer* _query_observer)
    {
        return net_manager_.rem_query_observer(_query_observer);
    }
    
    /*!
     * \brief 
     * \param _peer_observer : 
     * \return 
     */
    bool add_peer_observer(octopeer_observer* _peer_observer)
    {
        return net_manager_.add_peer_observer(_peer_observer);
    }
    
    /*!
     * \brief 
     * \param _peer_observer : 
     * \return 
     */
    bool rem_peer_observer(octopeer_observer* _peer_observer)
    {
        return net_manager_.rem_peer_observer(_peer_observer);
    }

    /*!
     * \brief 
     */
    void run(void)
    {
        net_manager_.run();
    }

    /*!
     * \brief 
     * \param _peer : 
     * \param _query : 
     * \return 
     */
    bool send_query(const octopeer& _peer, const octoquery& _query)
    {
            return net_manager_.send_query(_peer, _query);
    }
    /*!
     * \brief 
     * \param _port : 
     * \return 
     */
    bool send_broadcast(unsigned short _port)
    {
            return net_manager_.send_broadcast(_port);
    }
};

#endif
