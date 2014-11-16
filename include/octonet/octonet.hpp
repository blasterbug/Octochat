#ifndef OCTONET_HPP
#define OCTONET_HPP

#define OCTONET_DEFAULT_TCP_PORT 4444
#define OCTONET_DEFAULT_UDP_PORT 3333
#define OCTONET_SIZE_HEADER_LENGTH 8
#define OCTONET_PORT_HEADER_LENGTH 4
#define OCTONET_VERSION "OCTONET1"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <iomanip>
#include <set>
#include <sstream>
#include <vector>

#include "octoconnect_tcp.hpp"
#include "octopeer.hpp"
#include "octoquery.hpp"
#include "octopeer_observer.hpp"
#include "octoquery_observer.hpp"

/*!
 * \class octonet
 * \brief 
 */
class octonet
{
    private:
        std::set<octopeer, octopeer_comparator> __peers;
        boost::mutex __peers_mtx;
        std::set<octoquery_observer*> __query_observers;
        boost::mutex __query_observers_mtx;
        std::set<octopeer_observer*> __peer_observers;
        boost::mutex __peer_observers_mtx;
        const unsigned short __tcp_port;
        const unsigned short __udp_port;
        boost::asio::io_service __io_service;

        /*!
         * \brief 
         * \param op : 
         */
        void _add_peer(const octopeer &op)
        {
                boost::lock_guard<boost::mutex> guard(__peers_mtx);
                if(__peers.insert(op).second)
                {
                        BOOST_LOG_TRIVIAL(info) << "add peer: peer added";
                        _notify_peer_observers(op);
                        octoquery oq;
                        oq.headers_map["HELLO"] = "";
                        send_query_tcp(op, oq);
                }
        }

        /*!
         * \brief 
         * \param op : 
         */
        void _rem_peer(const octopeer &op)
        {
                boost::lock_guard<boost::mutex> guard(__peers_mtx);
                if(__peers.erase(op) > 0)
                {
                        _notify_peer_observers(op);
                }
        }
        
        /*!
         * \brief 
         * \param oq : 
         */
        void _notify_query_observers(const octoquery &oq)
        {
                boost::lock_guard<boost::mutex> guard(__query_observers_mtx);
        }
        
        /*!
         * \brief 
         * \param op : 
         */
        void _notify_peer_observers(const octopeer &op)
        {
			std::set<octopeer_observer*>::const_iterator it;
                        boost::lock_guard<boost::mutex> guard(__peer_observers_mtx);
			for(it=__peer_observers.begin(); it!=__peer_observers.end(); ++it)
			{
				(*it)->update_peer(op);
			}
        }

        /*!
         * \brief 
         */
        void _run_server_udp()
        {
                boost::asio::ip::udp::socket sock(__io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), __udp_port));
                for (;;)
                {
                        char port_headers[port_header_length*2];
                        boost::asio::ip::udp::endpoint sender_endpoint;
                        std::size_t length = sock.receive_from(boost::asio::buffer(port_headers), sender_endpoint);
                        if(length == (port_header_length*2))
                        {
                                std::istringstream tcp_is(std::string(port_headers, port_header_length));
                                unsigned short tcp_port = 0;
                                if (!(tcp_is >> std::hex >> tcp_port))
                                {
                                        return;
                                }
                                
                                std::istringstream udp_is(std::string(port_headers+port_header_length, port_header_length));
                                unsigned short udp_port = 0;
                                if (!(udp_is >> std::hex >> udp_port))
                                {
                                        return;
                                }
                                
                                octopeer op(sender_endpoint.address(), tcp_port);
                                octoquery oq;
                                oq.headers_map["HELLO"] = "";
                                send_query_tcp(op, oq);
                        }
                        
                }
        }

        /*!
         * \brief 
         */
        void _run_server_tcp()
        {
                boost::asio::ip::tcp::acceptor a(__io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), __tcp_port));
                for (;;)
                {
                        boost::shared_ptr<boost::asio::ip::tcp::socket> sock(new boost::asio::ip::tcp::socket(__io_service));
                        a.accept(*sock);
                        boost::thread t(boost::bind(&octonet::_session_tcp0, this, sock));
                }
        }
        
        /*!
         * \brief 
         * \param sock : 
         */
        void _session_tcp0(boost::shared_ptr<boost::asio::ip::tcp::socket> sock)
        {
                BOOST_LOG_TRIVIAL(info) << "session tcp start";
                try
                {
                        std::vector<char> data_vec;
                        octoquery oq;
                        boost::asio::ip::tcp::endpoint remote_endpoint(sock->remote_endpoint());
                        octopeer op(remote_endpoint.address(), remote_endpoint.port());
                        
                        {
                                char header_buf[size_header_length];
                                
                                std::size_t read_len = sock->read_some(boost::asio::buffer(header_buf));
                                if(read_len != size_header_length)
                                {
                                        BOOST_LOG_TRIVIAL(error) << "session tcp: bad header";
                                        return;
                                }
                                
                                std::istringstream is(std::string(header_buf, size_header_length));
                                std::size_t data_len = 0;
                                if (!(is >> std::hex >> data_len))
                                {
                                        BOOST_LOG_TRIVIAL(error) << "session tcp: bad header";
                                        return;
                                }
                                
                                data_vec.resize(data_len);
                                read_len = sock->read_some(boost::asio::buffer(data_vec));
                                if(read_len != data_len)
                                {
                                        BOOST_LOG_TRIVIAL(error) << "session tcp: bad data";
                                        return;
                                }
                        }
                        
                        std::string archive_data(&data_vec[0], data_vec.size());
                        std::istringstream archive_stream(archive_data);
                        boost::archive::text_iarchive archive(archive_stream);
                        archive >> oq;
                        
                        _add_peer(op);
                        _notify_query_observers(oq);
                }
                catch (std::exception& e)
                {
                        BOOST_LOG_TRIVIAL(error) << "session tcp: " << e.what();
                }
        }

    public:
        static const std::string version;
        enum { default_tcp_port = OCTONET_DEFAULT_TCP_PORT };
        enum { default_udp_port = OCTONET_DEFAULT_UDP_PORT };
        enum { size_header_length = OCTONET_SIZE_HEADER_LENGTH };
        enum { port_header_length = OCTONET_PORT_HEADER_LENGTH };
        enum peer_state { online, offline };

        /*!
         * \brief 
         */
        octonet() : __tcp_port(default_tcp_port), __udp_port(default_udp_port) {}

        /*!
         * \brief 
         */
        octonet(unsigned short tcp_port, unsigned short udp_port) : __tcp_port(tcp_port), __udp_port(udp_port) {}

        /*!
         * \brief 
         */
        ~octonet() {}

        /*!
         * \brief 
         * \param oq_obs : 
         * \return 
         */
        bool add_query_observer(octoquery_observer *oq_obs) { boost::lock_guard<boost::mutex> guard(__query_observers_mtx); return (__query_observers.insert(oq_obs)).second; }
        
        /*!
         * \brief 
         * \param oq_obs : 
         * \return 
         */
        bool rem_query_observer(octoquery_observer *oq_obs) { boost::lock_guard<boost::mutex> guard(__query_observers_mtx); return __query_observers.erase(oq_obs) > 0; }
        
        /*!
         * \brief 
         * \param op_obs : 
         * \return 
         */
        bool add_peer_observer(octopeer_observer *op_obs) { boost::lock_guard<boost::mutex> guard(__peer_observers_mtx); return (__peer_observers.insert(op_obs)).second; }
        
        /*!
         * \brief 
         * \param op_obs : 
         * \return 
         */
        bool rem_peer_observer(octopeer_observer *op_obs) { boost::lock_guard<boost::mutex> guard(__peer_observers_mtx); return __peer_observers.erase(op_obs) > 0; }
        
        /*!
         * \brief 
         */
        void run(void)
        {
                boost::thread t0(boost::bind(&octonet::_run_server_tcp, this));
                boost::thread t1(boost::bind(&octonet::_run_server_udp, this));
                send_udp_broadcast(default_udp_port);
        }
        
        /*!
         * \brief 
         * \param op : 
         * \param oq : 
         * \return 
         */
        bool send_query_tcp(const octopeer &op, const octoquery &oq)
        {
                try
                {
                        std::ostringstream archive_stream;
                        boost::archive::text_oarchive archive(archive_stream);
                        archive << oq;
                        std::string data_str = archive_stream.str();

                        std::ostringstream header_stream;
                        header_stream << std::setw(size_header_length) << std::hex << data_str.size();
                        if (!header_stream || header_stream.str().size() != size_header_length)
                        {
                                BOOST_LOG_TRIVIAL(error) << "send query tcp: bad header";
                                return false;
                        }
                        std::string header_str = header_stream.str();
                        
                        std::vector<boost::asio::const_buffer> buffers;
                        buffers.push_back(boost::asio::buffer(header_str));
                        buffers.push_back(boost::asio::buffer(data_str));

                        boost::asio::ip::tcp::socket s(__io_service);
                        boost::asio::ip::tcp::endpoint endpoint(op.ip_address, op.tcp_port);
                        s.connect(endpoint);
                        boost::asio::write(s, buffers);
                        BOOST_LOG_TRIVIAL(info) << "send query tcp: query sent";
                        return true;
                }
                catch (std::exception& e)
                {
                        BOOST_LOG_TRIVIAL(error) << "send query tcp: " << e.what();
                }
                return false;
        }

        /*!
         * \brief 
         * \param port : 
         * \return 
         */
        bool send_udp_broadcast(unsigned int port)
        {
                try
                {
                        std::ostringstream tcp_port_stream;
                        tcp_port_stream << std::setw(port_header_length) << std::hex << __tcp_port;
                        if (!tcp_port_stream || tcp_port_stream.str().size() != port_header_length)
                        {
                                BOOST_LOG_TRIVIAL(error) << "send query udp broadcast: bad tcp port header";
                                return false;
                        }
                        std::string tcp_port_str = tcp_port_stream.str();

                        std::ostringstream udp_port_stream;
                        udp_port_stream << std::setw(port_header_length) << std::hex << __udp_port;
                        if (!udp_port_stream || udp_port_stream.str().size() != port_header_length)
                        {
                                BOOST_LOG_TRIVIAL(error) << "send query udp broadcast: bad udp port header";
                                return false;
                        }
                        std::string udp_port_str = udp_port_stream.str();

                        std::vector<boost::asio::const_buffer> buffers;
                        buffers.push_back(boost::asio::buffer(tcp_port_str));
                        buffers.push_back(boost::asio::buffer(udp_port_str));
                        
                        boost::asio::ip::udp::socket sock(__io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));
                        sock.set_option(boost::asio::socket_base::broadcast(true));
                        boost::asio::ip::udp::endpoint broadcast_endpoint(boost::asio::ip::address_v4::broadcast(), default_udp_port);
                        sock.send_to(boost::asio::buffer(buffers), broadcast_endpoint);
                        BOOST_LOG_TRIVIAL(info) << "send udp broadcast: broadcast sent";
                        return true;
                }
                catch (std::exception& e)
                {
                        BOOST_LOG_TRIVIAL(error) << "send query udp broadcast: " << e.what();
                }
                return false;
        }
};

const std::string octonet::version = OCTONET_VERSION;

#endif
