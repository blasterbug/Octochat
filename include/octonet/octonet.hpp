#ifndef OCTONET_HPP
#define OCTONET_HPP

#define OCTONET_VERSION "1"
#define OCTONET_HEADER "OCTONET"
#define APP_HEADER "APP"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
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

class octonet
{
    private:
        std::set<octoquery_observer*> query_observers;
        std::set<octopeer_observer*> peer_observers;
        //TODO : think about const members
        unsigned short __tcp_port;
        unsigned short __udp_port;

    protected:
        boost::asio::io_service _io_service;
        void _notify_query_observers(const octoquery &oq) const {}
        void _notify_peer_observers(const octopeer &op) const
        {
			std::set<octopeer_observer*>::const_iterator it;
			for(it=peer_observers.begin(); it!=peer_observers.end(); ++it)
			{
				(*it)->update_peer(op);
			}
        }
        void _server_tcp(unsigned short port)
        {
                boost::asio::ip::tcp::acceptor a(_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
                for (;;)
                {
                        boost::shared_ptr<boost::asio::ip::tcp::socket> sock(new boost::asio::ip::tcp::socket(_io_service));
                        a.accept(*sock);
                        boost::thread t(boost::bind(&octonet::_session_tcp0, this, sock));
                }
        }
        void _session_tcp0(boost::shared_ptr<boost::asio::ip::tcp::socket> sock)
        {
                char header_buf[8];
                std::size_t data_len;
                std::size_t read_len;
                boost::system::error_code error;
                std::vector<char> data_vec;
                octoquery oq;
                try
                {
                        read_len = sock->read_some(boost::asio::buffer(header_buf), error);
                        if(error || (read_len != 8))
                        {
                                //log
                                return;
                        }
                        
                        std::istringstream is(std::string(header_buf, 8));
                        data_len = 0;
                        if (!(is >> std::hex >> data_len))
                        {
                                //log
                                return;
                        }
                        
                        data_vec.resize(data_len);
                        read_len = sock->read_some(boost::asio::buffer(data_vec), error);
                        if(error || (read_len != data_len))
                        {
                                //log
                                return;
                        }
                        std::string archive_data(&data_vec[0], data_vec.size());
                        std::istringstream archive_stream(archive_data);
                        boost::archive::text_iarchive archive(archive_stream);
                        archive >> oq;
                        
                        _notify_query_observers(oq);
                }
                catch (std::exception& e)
                {
                        //log
                }
        }

    public:
        octonet() : _io_service() {}
        ~octonet() {}
        bool add_query_observer(octoquery_observer *oq_obs) { return (query_observers.insert(oq_obs)).second; }
        bool rem_query_observer(octoquery_observer *oq_obs) { return query_observers.erase(oq_obs) > 0; }
        bool add_peer_observer(octopeer_observer *op_obs) { return (peer_observers.insert(op_obs)).second; }
        bool rem_peer_observer(octopeer_observer *op_obs) { return peer_observers.erase(op_obs) > 0; }
        bool send_query_tcp(const octopeer &op, const octoquery &oq)
        {
                try
                {
                        boost::asio::ip::tcp::socket s(_io_service);
                        s.connect(op.endpoint);

                        std::ostringstream archive_stream;
                        boost::archive::text_oarchive archive(archive_stream);
                        archive << oq;
                        std::string data_str = archive_stream.str();

                        std::ostringstream header_stream;
                        header_stream << std::setw(8) << std::hex << data_str.size();
                        if (!header_stream || header_stream.str().size() != 8)
                        {
                                //log
                                return false;
                        }
                        std::string header_str = header_stream.str();
                        
                        std::vector<boost::asio::const_buffer> buffers;
                        buffers.push_back(boost::asio::buffer(header_str));
                        buffers.push_back(boost::asio::buffer(data_str));
                        boost::asio::write(s, buffers);
                        return true;
                }
                catch (std::exception& e)
                {
                        //log
                        return false;
                }
                return false;
        }
};

#endif
