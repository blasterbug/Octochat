#ifndef OCTONET_MANAGER_HPP
#define OCTONET_MANAGER_HPP

#define OCTONET_DEFAULT_TCP_PORT 4444
#define OCTONET_DEFAULT_UDP_PORT 3333
#define OCTONET_SIZE_HEADER_LENGTH 8
#define OCTONET_PORT_HEADER_LENGTH 4
#define OCTONET_VERSION_HEADER "OCTONET1"
#define OCTONET_APP_ID_HEADER "APP_ID"
#define OCTONET_IP_ADDRESS_HEADER "IP_ADDRESS"
#define OCTONET_TCP_PORT_HEADER "TCP_PORT"
#define OCTONET_UDP_PORT_HEADER "UDP_PORT"

#include <boost/archive/text_oarchive.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <ios>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "octopeer.hpp"
#include "octoquery.hpp"
#include "octopeer_observer.hpp"
#include "octoquery_observer.hpp"
#include "server_factory.hpp"

static const unsigned short octonet_default_tcp_port = OCTONET_DEFAULT_TCP_PORT;
static const unsigned short octonet_default_udp_port = OCTONET_DEFAULT_UDP_PORT;
static const std::size_t octonet_size_header_length = OCTONET_SIZE_HEADER_LENGTH;
static const std::size_t octonet_port_header_length = OCTONET_PORT_HEADER_LENGTH;
static const std::string octonet_version_header = OCTONET_VERSION_HEADER;
static const std::string octonet_app_id_header = OCTONET_APP_ID_HEADER;
static const std::string octonet_ip_address_header = OCTONET_IP_ADDRESS_HEADER;
static const std::string octonet_tcp_port_header = OCTONET_TCP_PORT_HEADER;
static const std::string octonet_udp_port_header = OCTONET_UDP_PORT_HEADER;

using boost::asio::ip::udp;
using boost::asio::ip::tcp;

class octonet_manager
{
private:
    boost::asio::ip::address ip_address_;
    unsigned short tcp_port_;
    unsigned short udp_port_;

    boost::mutex peers_set_mtx_;
    boost::mutex query_observers_set_mtx_;
    boost::mutex peer_observers_set_mtx_;
    boost::mutex remote_udp_ports_set_mtx_;

    std::set<octopeer, octopeer_comparator> peers_set_;
    std::set<octoquery_observer*> query_observers_set_;
    std::set<octopeer_observer*> peer_observers_set_;
    std::set<unsigned short> remote_udp_ports_set_;

    boost::asio::io_service io_service_;
    server_factory server_factory_;
    boost::scoped_ptr<abstract_server> tcp_server_ptr_;
    boost::scoped_ptr<abstract_server> udp_server_ptr_;
    boost::thread_group servers_group_;

public:
    /*!
     * \brief 
     */
    octonet_manager(unsigned short _tcp_port, unsigned short _udp_port) : tcp_port_(_tcp_port), udp_port_(_udp_port), server_factory_(this) {}

    /*!
     * \brief 
     */
    ~octonet_manager(void)
    {
		io_service_.stop();
		servers_group_.join_all();
	}

    /*!
     * \brief 
     * \return 
     */
    boost::asio::io_service& io_service(void)
    {
        return io_service_;
    }

    /*!
     * \brief 
     * \return 
     */
    boost::asio::ip::address ip_address(void)
    {
        return ip_address_;
    }

    /*!
     * \brief 
     * \return 
     */
    unsigned short tcp_port(void)
    {
        return tcp_port_;
    }

    /*!
     * \brief 
     * \return 
     */
    unsigned short udp_port(void)
    {
        return udp_port_;
    }

    /*!
     * \brief 
     * \param _port : 
     */
    void add_udp_broadcast_port(unsigned short _port)
    {
        boost::lock_guard<boost::mutex> guard(remote_udp_ports_set_mtx_);
        if(remote_udp_ports_set_.find(_port) == remote_udp_ports_set_.end())
        {
            remote_udp_ports_set_.insert(_port);
            send_broadcast(_port);
        }
    }

    /*!
     * \brief 
     * \param _peer : 
     */
    void add_peer(const octopeer& _peer)
    {
        boost::lock_guard<boost::mutex> guard(peers_set_mtx_);
        if(peers_set_.find(_peer) == peers_set_.end())
        {
            octoquery query;
            if(send_query(_peer, query))
            {
                BOOST_LOG_TRIVIAL(info) << "INFO octonet::add_peer: peer added";
                peers_set_.insert(_peer);
                notify_peer_observers(_peer, online);
            }
        }
    }

    /*!
     * \brief 
     * \param peer : 
     */
    void rem_peer(const octopeer& _peer)
    {
        boost::lock_guard<boost::mutex> guard(peers_set_mtx_);
        if(peers_set_.erase(_peer) > 0)
        {
            notify_peer_observers(_peer, offline);
        }
    }

    /*!
     * \brief 
     * \param _query_observer : 
     * \return 
     */
    bool add_query_observer(octoquery_observer* _query_observer)
    {
        boost::lock_guard<boost::mutex> guard(query_observers_set_mtx_);
        return (query_observers_set_.insert(_query_observer)).second;
    }
    
    /*!
     * \brief 
     * \param _query_observer : 
     * \return 
     */
    bool rem_query_observer(octoquery_observer* _query_observer)
    {
        boost::lock_guard<boost::mutex> guard(query_observers_set_mtx_);
        return query_observers_set_.erase(_query_observer) > 0;
    }
    
    /*!
     * \brief 
     * \param _peer_observer : 
     * \return 
     */
    bool add_peer_observer(octopeer_observer* _peer_observer)
    {
        boost::lock_guard<boost::mutex> guard(peer_observers_set_mtx_);
        return (peer_observers_set_.insert(_peer_observer)).second;
    }
    
    /*!
     * \brief 
     * \param _peer_observer : 
     * \return 
     */
    bool rem_peer_observer(octopeer_observer* _peer_observer)
    {
        boost::lock_guard<boost::mutex> guard(peer_observers_set_mtx_);
        return peer_observers_set_.erase(_peer_observer) > 0;
    }

    /*!
     * \brief 
     * \param query : 
     */
    void notify_query_observers(const octoquery& _query)
    {
        std::string app_str;                            
        std::map<std::string, std::string>::const_iterator app_it = _query.headers_map.find(octonet_app_id_header);
        if(app_it != _query.headers_map.end())
        {
            app_str = app_it->second;
        }
        
        boost::lock_guard<boost::mutex> guard(query_observers_set_mtx_);
        for(std::set<octoquery_observer*>::const_iterator it=query_observers_set_.begin(); it!=query_observers_set_.end(); ++it)
        {
            if((*it)->app() == app_str)
            {
                (*it)->update_query(_query);
            }
        }
    }
    
    /*!
     * \brief 
     * \param _peer : 
     * \param _state : 
     */
    void notify_peer_observers(const octopeer& _peer, octopeer_state _state)
    {                    
        boost::lock_guard<boost::mutex> guard(peer_observers_set_mtx_);
        for(std::set<octopeer_observer*>::const_iterator it=peer_observers_set_.begin(); it!=peer_observers_set_.end(); ++it)
        {
            (*it)->update_peer(_peer, _state);
        }
    }

    /*!
     * \brief 
     */
    void run(void)
    {
            tcp_server_ptr_.reset(server_factory_.create_server(tcp, tcp_port_));
            ip_address_ = tcp_server_ptr_->ip_address();
            tcp_port_ = tcp_server_ptr_->port();
            servers_group_.create_thread(boost::bind(&abstract_server::run, tcp_server_ptr_.get()));

            udp_server_ptr_.reset(server_factory_.create_server(udp, udp_port_));
            udp_port_ = udp_server_ptr_->port();
            servers_group_.create_thread(boost::bind(&abstract_server::run, udp_server_ptr_.get()));
            
            add_udp_broadcast_port(udp_port_);
    }
    
    /*!
     * \brief 
     * \param _peer : 
     * \param _query : 
     * \return 
     */
    bool send_query(const octopeer& _peer, const octoquery& _query)
    {
        BOOST_LOG_TRIVIAL(info) << "INFO octonet::send_query: start sending query to " << _peer.ip_address << ":" << _peer.tcp_port;
        std::vector<boost::asio::const_buffer> buffers;
        try
        {
            std::ostringstream archive_stream;
            boost::archive::text_oarchive archive(archive_stream);
            archive << _query;
            std::string data_str = archive_stream.str();

            std::ostringstream tcp_port_stream;
            tcp_port_stream << std::setw(octonet_port_header_length) << std::hex << tcp_port_;
            if (!tcp_port_stream || tcp_port_stream.str().size() != octonet_port_header_length)
            {
                    BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_query: bad size header";
                    throw std::exception();
            }
            std::string tcp_port_str = tcp_port_stream.str();

            std::ostringstream udp_port_stream;
            udp_port_stream << std::setw(octonet_port_header_length) << std::hex << udp_port_;
            if (!udp_port_stream || udp_port_stream.str().size() != octonet_port_header_length)
            {
                    BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_query: bad size header";
                    throw std::exception();
            }
            std::string udp_port_str = udp_port_stream.str();

            std::ostringstream size_stream;
            size_stream << std::setw(octonet_size_header_length) << std::hex << data_str.size();
            if (!size_stream || size_stream.str().size() != octonet_size_header_length)
            {
                    BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_query: bad size header";
                    throw std::exception();
            }
            std::string size_str = size_stream.str();
            
            buffers.push_back(boost::asio::buffer(octonet_version_header));
            buffers.push_back(boost::asio::buffer(tcp_port_str));
            buffers.push_back(boost::asio::buffer(udp_port_str));
            buffers.push_back(boost::asio::buffer(size_str));
            buffers.push_back(boost::asio::buffer(data_str));
        }
        catch (std::exception& e)
        {
            BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_query: " << e.what();
            return false;
        }
        try
        {
            tcp::socket sock(io_service_);
            tcp::endpoint endpoint(_peer.ip_address, _peer.tcp_port);
            sock.connect(endpoint);
            boost::asio::write(sock, buffers);
            BOOST_LOG_TRIVIAL(info) << "INFO octonet::send_query: query sent to " << _peer.ip_address << ":" << _peer.tcp_port;
        }
        catch (std::exception& e)
        {
            BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_query: " << e.what();
            rem_peer(_peer);
            return false;
        }
        return true;
    }

    /*!
     * \brief 
     * \param _port : 
     * \return 
     */
    bool send_broadcast(unsigned short _port)
    {
            BOOST_LOG_TRIVIAL(info) << "INFO octonet::send_broadcast: start sending broadcast on port " << _port;
            try
            {
                    std::string data_str(octonet_version_header);
                    
                    std::ostringstream tcp_port_stream;
                    tcp_port_stream << std::setw(octonet_port_header_length) << std::hex << tcp_port_;
                    if (!tcp_port_stream || tcp_port_stream.str().size() != octonet_port_header_length)
                    {
                            BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_broadcast: bad tcp port header";
                            throw std::exception();
                    }
                    data_str += tcp_port_stream.str();

                    udp::socket sock(io_service_, udp::endpoint(udp::v4(), 0));
                    sock.set_option(boost::asio::socket_base::broadcast(true));
                    udp::endpoint broadcast_endpoint(boost::asio::ip::address_v4::broadcast(), _port);
                    sock.send_to(boost::asio::buffer(data_str), broadcast_endpoint);
                    BOOST_LOG_TRIVIAL(info) << "INFO octonet::send_broadcast: broadcast sent on port " << _port << " %" << data_str;
            }
            catch (std::exception& e)
            {
                    BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_broadcast: " << e.what();
                    return false;
            }
            return true;
    }
};

#endif
