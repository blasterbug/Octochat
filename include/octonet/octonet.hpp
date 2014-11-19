#ifndef OCTONET_HPP
#define OCTONET_HPP

#define OCTONET_DEFAULT_TCP_PORT 4444
#define OCTONET_DEFAULT_UDP_PORT 3333
#define OCTONET_SIZE_HEADER_LENGTH 8
#define OCTONET_PORT_HEADER_LENGTH 4
#define OCTONET_VERSION "OCTONET1"
#define OCTONET_APP_HEADER "APP"
#define OCTONET_TCP_PORT_HEADER "TCP_PORT"
#define OCTONET_UDP_PORT_HEADER "UDP_PORT"

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

using boost::asio::ip::udp;
using boost::asio::ip::tcp;

/*!
 * \class octonet
 * \brief 
 */
class octonet
{
protected:
        /*!
         * \brief 
         * \param op : 
         */
        void _add_peer(const octopeer &op)
        {
                boost::lock_guard<boost::mutex> guard(__peers_mtx);
                if(send_hello(op) && __peers.insert(op).second)//TODO: check
                {
                        BOOST_LOG_TRIVIAL(info) << "INFO octonet::_add_peer: peer added";
                        _notify_peer_observers(op, online);
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
                        _notify_peer_observers(op, offline);
                }
        }
        
        /*!
         * \brief 
         * \param oq : 
         */
        void _notify_query_observers(const octoquery &oq)
        {
                std::string app_str;
                std::set<octoquery_observer*>::const_iterator it;
                                
                std::map<std::string, std::string>::const_iterator app_it = oq.headers_map.find(app_header);
                if(app_it != oq.headers_map.end())
                {
                        app_str = app_it->second;
                }
                
                boost::lock_guard<boost::mutex> guard(__query_observers_mtx);
                for(it=__query_observers.begin(); it!=__query_observers.end(); ++it)
                {
                        if((*it)->app() == app_str)
                        {
                                (*it)->update_query(oq);
                        }
                }
        }
        
        /*!
         * \brief 
         * \param op : 
         */
        void _notify_peer_observers(const octopeer &op, octopeer_state s)
        {
			std::set<octopeer_observer*>::const_iterator it;
                        
                        boost::lock_guard<boost::mutex> guard(__peer_observers_mtx);
			for(it=__peer_observers.begin(); it!=__peer_observers.end(); ++it)
			{
				(*it)->update_peer(op, s);
			}
        }

        /*!
         * \brief 
         */
        void _handle_udp(const boost::system::error_code& error, size_t bytes_recvd)
        {
                BOOST_LOG_TRIVIAL(info) << "INFO octonet::_handle_udp: new udp datagram from " << __udp_endpoint.address() << ":" << __udp_endpoint.port();
                if (!error && (bytes_recvd == __udp_data_len) && (version == std::string(__udp_data.get(), version.size())))
                {
                        std::istringstream tcp_is(std::string(__udp_data.get(), port_header_length));
                        unsigned short tcp_port = 0;
                        if (!(tcp_is >> std::hex >> tcp_port))
                        {
                                BOOST_LOG_TRIVIAL(error) << "ERROR octonet::_handle_udp: bad tcp port header";
                        }
                        else
                        {
                                BOOST_LOG_TRIVIAL(info) << "INFO octonet::_handle_udp: good tcp port header %"<<tcp_port;
                                octopeer op(__udp_endpoint.address(), tcp_port);
                                send_hello(op);
                        }
                }
               __udp_sock->async_receive_from(
                        boost::asio::buffer(__udp_data.get(), __udp_data_len), __udp_endpoint,
                        boost::bind(&octonet::_handle_udp, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        }

        /*!
         * \brief 
         */
        void _run_server_udp()
        {
                BOOST_LOG_TRIVIAL(info) << "INFO octonet::_run_server_udp: start udp server";
                try
                {
                        __udp_sock.reset(new udp::socket(__io_service, udp::endpoint(udp::v4(), __udp_port)));
                        __udp_data_len = version.size() + port_header_length;
                        __udp_data.reset(new char[__udp_data_len]);
                        __udp_sock->async_receive_from(
                                boost::asio::buffer(__udp_data.get(), __udp_data_len), __udp_endpoint,
                                boost::bind(&octonet::_handle_udp, this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));
                        __io_service.run();
                }
                catch (std::exception& e)
                {
                        BOOST_LOG_TRIVIAL(error) << "ERROR octonet::_run_server_udp: " << e.what();
                }
        }

        /*!
         * \brief 
         */
        void _run_server_tcp()
        {
                BOOST_LOG_TRIVIAL(info) << "INFO octonet::_run_server_tcp: start tcp server";
                try
                {
                        tcp::acceptor a(__io_service, tcp::endpoint(tcp::v4(), __tcp_port));
                        for (;;)
                        {
                                boost::shared_ptr<tcp::socket> sock(new tcp::socket(__io_service));
                                a.accept(*sock);
                                boost::thread t(boost::bind(&octonet::_handle_tcp, this, sock));
                        }
                }
                catch (std::exception& e)
                {
                        BOOST_LOG_TRIVIAL(error) << "ERROR octonet::_run_server_tcp: " << e.what();
                }
        }
        
        /*!
         * \brief 
         * \param sock : 
         */
        void _handle_tcp(boost::shared_ptr<tcp::socket> sock)
        {
                BOOST_LOG_TRIVIAL(info) << "INFO octonet::_handle_udp: new tcp session from " << sock->remote_endpoint().address() << ":" << sock->remote_endpoint().port();
                try
                {
                        std::vector<char> data_vec;
                        octoquery oq;
                        tcp::endpoint remote_endpoint(sock->remote_endpoint());
                        octopeer op(remote_endpoint.address(), remote_endpoint.port());
                        
                        {
                                char version_buf[] = OCTONET_VERSION;
                                char header_buf[size_header_length];

                                std::size_t read_len = sock->read_some(boost::asio::buffer(version_buf));
                                if((read_len != version.size()) || (version != std::string(version_buf)))
                                {
                                        BOOST_LOG_TRIVIAL(error) << "ERROR octonet::_handle_udp: bad version";
                                        return;
                                }

                                read_len = sock->read_some(boost::asio::buffer(header_buf));
                                if(read_len != size_header_length)
                                {
                                        BOOST_LOG_TRIVIAL(error) << "ERROR octonet::_handle_udp: bad header";
                                        return;
                                }
                                
                                std::istringstream is(std::string(header_buf, size_header_length));
                                std::size_t data_len = 0;
                                if (!(is >> std::hex >> data_len))
                                {
                                        BOOST_LOG_TRIVIAL(error) << "ERROR octonet::_handle_udp: bad size header";
                                        return;
                                }
                                
                                data_vec.resize(data_len);
                                read_len = sock->read_some(boost::asio::buffer(data_vec));
                                if(read_len != data_len)
                                {
                                        BOOST_LOG_TRIVIAL(error) << "ERROR octonet::_handle_udp: bad data";
                                        return;
                                }
                        }
                        
                        std::string archive_data(&data_vec[0], data_vec.size());
                        std::istringstream archive_stream(archive_data);
                        boost::archive::text_iarchive archive(archive_stream);
                        archive >> oq;
                        
                        BOOST_LOG_TRIVIAL(info) << "INFO octonet::_handle_udp: OK";
                        
                        _add_peer(op);
                        _notify_query_observers(oq);
                }
                catch (std::exception& e)
                {
                        BOOST_LOG_TRIVIAL(error) << "ERROR octonet::_handle_udp: " << e.what();
                }
        }

    public:
        static const std::string version;
        static const std::string app_header;
        static const std::string tcp_port_header;
        static const std::string udp_port_header;
        enum { default_tcp_port = OCTONET_DEFAULT_TCP_PORT };
        enum { default_udp_port = OCTONET_DEFAULT_UDP_PORT };
        enum { size_header_length = OCTONET_SIZE_HEADER_LENGTH };
        enum { port_header_length = OCTONET_PORT_HEADER_LENGTH };

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
        ~octonet() { __io_service.stop(); __servers.interrupt_all(); }

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
                __servers.create_thread(boost::bind(&octonet::_run_server_udp, this));
                //__servers.create_thread(boost::bind(&octonet::_run_server_tcp, this));
                boost::thread t(boost::bind(&octonet::_run_server_tcp, this));
                send_broadcast(default_udp_port);
        }
        
        /*!
         * \brief 
         * \param op : 
         * \return 
         */
        bool send_hello(const octopeer &op)
        {
                octoquery oq;

                std::ostringstream tcp_port_stream;
                tcp_port_stream << std::setw(port_header_length) << std::hex << __tcp_port;
                if (!tcp_port_stream || tcp_port_stream.str().size() != port_header_length)
                {
                        BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_hello: bad tcp port header";
                        return false;
                }
                oq.headers_map[tcp_port_header] = tcp_port_stream.str();

                std::ostringstream udp_port_stream;
                udp_port_stream << std::setw(port_header_length) << std::hex << __udp_port;
                if (!udp_port_stream || udp_port_stream.str().size() != port_header_length)
                {
                        BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_hello: bad udp port header";
                        return false;
                }
                oq.headers_map[udp_port_header] = udp_port_stream.str();
                
                return send_query(op, oq);
        }
        
        /*!
         * \brief 
         * \param op : 
         * \param oq : 
         * \return 
         */
        bool send_query(const octopeer &op, const octoquery &oq)
        {
                BOOST_LOG_TRIVIAL(info) << "INFO octonet::send_query: start sending query to " << op.ip_address << ":" << op.tcp_port;
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
                                BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_query: bad size header";
                                return false;
                        }
                        std::string header_str = header_stream.str();
                        
                        std::vector<boost::asio::const_buffer> buffers;
                        buffers.push_back(boost::asio::buffer(header_str));
                        buffers.push_back(boost::asio::buffer(data_str));

                        tcp::socket s(__io_service);
                        tcp::endpoint endpoint(op.ip_address, op.tcp_port);
                        s.connect(endpoint);
                        boost::asio::write(s, buffers);
                        BOOST_LOG_TRIVIAL(info) << "INFO octonet::send_query: query sent to " << op.ip_address << ":" << op.tcp_port;
                        return true;
                }
                catch (std::exception& e)
                {
                        BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_query: " << e.what();
                }
                _rem_peer(op);
                return false;
        }

        /*!
         * \brief 
         * \param port : 
         * \return 
         */
        bool send_broadcast(unsigned short port)
        {
                BOOST_LOG_TRIVIAL(info) << "INFO octonet::send_broadcast: start sending broadcast on port " << port;
                try
                {
                        std::string data_str(version);
                        
                        std::ostringstream tcp_port_stream;
                        tcp_port_stream << std::setw(port_header_length) << std::hex << __tcp_port;
                        if (!tcp_port_stream || tcp_port_stream.str().size() != port_header_length)
                        {
                                BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_broadcast: bad tcp port header";
                                return false;
                        }
                        data_str += tcp_port_stream.str();

                        udp::socket sock(__io_service, udp::endpoint(udp::v4(), 0));
                        sock.set_option(boost::asio::socket_base::broadcast(true));
                        udp::endpoint broadcast_endpoint(boost::asio::ip::address_v4::broadcast(), port);
                        sock.send_to(boost::asio::buffer(data_str), broadcast_endpoint);
                        BOOST_LOG_TRIVIAL(info) << "INFO octonet::send_broadcast: broadcast sent on port " << port << " %" << data_str;
                        return true;
                }
                catch (std::exception& e)
                {
                        BOOST_LOG_TRIVIAL(error) << "ERROR octonet::send_broadcast: " << e.what();
                }
                return false;
        }

    private:
        std::set<octopeer, octopeer_comparator> __peers;
        boost::mutex __peers_mtx;
        std::set<octoquery_observer*> __query_observers;
        boost::mutex __query_observers_mtx;
        std::set<octopeer_observer*> __peer_observers;
        boost::mutex __peer_observers_mtx;

        const unsigned short __tcp_port;
        const unsigned short __udp_port;
        boost::scoped_ptr<udp::socket> __udp_sock;
        udp::endpoint __udp_endpoint;
        boost::scoped_array<char> __udp_data;
        std::size_t __udp_data_len;
        
        boost::thread_group __servers;
        
        boost::asio::io_service __io_service; //need to be destruct in last
};

const std::string octonet::version = OCTONET_VERSION;
const std::string octonet::app_header = OCTONET_APP_HEADER;
const std::string octonet::tcp_port_header = OCTONET_TCP_PORT_HEADER;
const std::string octonet::udp_port_header = OCTONET_UDP_PORT_HEADER;

#endif
