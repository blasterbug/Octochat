#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>

#include "abstract_server.hpp"

using boost::asio::ip::tcp;

class octonet_manager;

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
private:
    octonet_manager* net_manager_;
    tcp::socket sock_;
    boost::scoped_array<char> version_buf_;
    boost::scoped_array<char> tcp_port_buf_;
    boost::scoped_array<char> udp_port_buf_;
    boost::scoped_array<char> data_size_buf_;
    boost::scoped_array<char> data_buf_;
    std::size_t version_len_;
    std::size_t tcp_port_len_;
    std::size_t udp_port_len_;
    std::size_t data_size_len_;
    std::size_t data_len_;
    unsigned short tcp_port_;
    unsigned short udp_port_;    

    tcp_connection(boost::asio::io_service& _io_service, octonet_manager* _net_manager);
    void handle_check_version(const boost::system::error_code& _error, size_t _bytes_transferred);
    void handle_read_tcp_port(const boost::system::error_code& _error, size_t _bytes_transferred);
    void handle_read_udp_port(const boost::system::error_code& _error, size_t _bytes_transferred);
    void handle_read_data_len(const boost::system::error_code& _error, size_t _bytes_transferred);
    void handle_read_data(const boost::system::error_code& _error, size_t _bytes_transferred);

public:
    static boost::shared_ptr<tcp_connection> create(boost::asio::io_service& _io_service, octonet_manager* _net_manager);
    tcp::socket& socket(void);
    void start(void);
};

class tcp_server : public abstract_server
{
private:
    boost::asio::io_service io_service_;
    octonet_manager* net_manager_;
    boost::asio::ip::address ip_address_;
    unsigned short port_;
    tcp::acceptor acceptor_;
    
    void start_accept(void);
    void handle_accept(boost::shared_ptr<tcp_connection> _new_connection, const boost::system::error_code& _error);

public:
    tcp_server(octonet_manager* _net_manager, unsigned short _port);
    virtual void stop(void);
    virtual void run(void);
    virtual unsigned short port(void);
    virtual boost::asio::ip::address ip_address(void);
};

#endif
