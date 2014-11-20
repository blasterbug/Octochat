#include "octonet/octonet_manager.hpp"

#include <boost/lexical_cast.hpp>

////tcp_connection

//public

boost::shared_ptr<tcp_connection> tcp_connection::create(octonet_manager* _net_manager)
{
    return boost::shared_ptr<tcp_connection>(new tcp_connection(_net_manager));
}

tcp::socket& tcp_connection::socket(void)
{
    return sock_;
}

void tcp_connection::start(void)
{
    version_len_ = octonet_version_header.size();
    version_buf_.reset(new char[version_len_]);
    sock_.async_read_some(boost::asio::buffer(version_buf_.get(), version_len_),
        boost::bind(&tcp_connection::handle_check_version, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

//private

tcp_connection::tcp_connection(octonet_manager* _net_manager) : net_manager_(_net_manager), sock_(_net_manager->io_service())
{
    ;
}

void tcp_connection::handle_check_version(const boost::system::error_code& _error, size_t _bytes_transferred)
{
    BOOST_LOG_TRIVIAL(info) << "INFO handle_check_version:";
    if (!_error && (_bytes_transferred == version_len_) && (octonet_version_header == std::string(version_buf_.get(), version_len_)))
    {
        tcp_port_len_ = octonet_port_header_length;
        tcp_port_buf_.reset(new char[tcp_port_len_]);
        sock_.async_read_some(boost::asio::buffer(tcp_port_buf_.get(), tcp_port_len_),
            boost::bind(&tcp_connection::handle_read_tcp_port, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
}

void tcp_connection::handle_read_tcp_port(const boost::system::error_code& _error, size_t _bytes_transferred)
{
    BOOST_LOG_TRIVIAL(info) << "INFO handle_read_tcp_port:";
    if (!_error && (_bytes_transferred == tcp_port_len_))
    {
        std::istringstream is(std::string(tcp_port_buf_.get(), tcp_port_len_));
        tcp_port_ = 0;
        if(!(is >> std::hex >> tcp_port_))
        {
            return;
        }
        
        udp_port_len_ = octonet_port_header_length;
        udp_port_buf_.reset(new char[udp_port_len_]);
        sock_.async_read_some(boost::asio::buffer(udp_port_buf_.get(), udp_port_len_),
            boost::bind(&tcp_connection::handle_read_udp_port, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
}

void tcp_connection::handle_read_udp_port(const boost::system::error_code& _error, size_t _bytes_transferred)
{
    BOOST_LOG_TRIVIAL(info) << "INFO handle_read_udp_port:";
    if (!_error && (_bytes_transferred == udp_port_len_))
    {
        std::istringstream is(std::string(udp_port_buf_.get(), udp_port_len_));
        udp_port_ = 0;
        if(!(is >> std::hex >> udp_port_))
        {
            return;
        }
        
        data_size_len_ = octonet_size_header_length;
        data_size_buf_.reset(new char[data_size_len_]);
        sock_.async_read_some(boost::asio::buffer(data_size_buf_.get(), data_size_len_),
            boost::bind(&tcp_connection::handle_read_data_len, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
}

void tcp_connection::handle_read_data_len(const boost::system::error_code& _error, size_t _bytes_transferred)
{
    if (!_error && (_bytes_transferred == data_size_len_))
    {
        std::istringstream is(std::string(data_size_buf_.get(), data_size_len_));
        data_len_ = 0;
        if(!(is >> std::hex >> data_len_))
        {
            return;
        }
        
        data_buf_.reset(new char[data_len_]);
        sock_.async_read_some(boost::asio::buffer(data_buf_.get(), data_len_),
            boost::bind(&tcp_connection::handle_read_data, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
}

void tcp_connection::handle_read_data(const boost::system::error_code& _error, size_t _bytes_transferred)
{
    if (!_error && (_bytes_transferred == data_len_))
    {
        try
        {
            octoquery query;
            octopeer peer(sock_.remote_endpoint().address(), tcp_port_);
            
            std::string archive_data(data_buf_.get(), data_len_);
            std::istringstream archive_stream(archive_data);
            boost::archive::text_iarchive archive(archive_stream);
            archive >> query;
            
            query.headers_map[octonet_ip_address_header] = sock_.remote_endpoint().address().to_string();
            query.headers_map[octonet_tcp_port_header] = boost::lexical_cast<std::string>(tcp_port_);
            query.headers_map[octonet_udp_port_header] = boost::lexical_cast<std::string>(udp_port_);

            BOOST_LOG_TRIVIAL(info) << "INFO octonet::_handle_udp: OK";

            net_manager_->add_peer(peer);
            net_manager_->notify_query_observers(query);
            net_manager_->add_remote_udp_port(udp_port_);
        }
        catch(std::exception& e)
        {
            BOOST_LOG_TRIVIAL(info) << "ERROR handle_read_data: "<<e.what();
        }
    }
}

////tcp_server

//public

tcp_server::tcp_server(octonet_manager* _net_manager, unsigned short _port) : net_manager_(_net_manager), acceptor_(_net_manager->io_service(), tcp::endpoint(tcp::v4(), _port))
{
	ip_address_ = acceptor_.local_endpoint().address();
    port_ = acceptor_.local_endpoint().port();
}

tcp_server::~tcp_server(void)
{
    ;
}

void tcp_server::run(void)
{
    start_accept();
    net_manager_->io_service().run();
}

unsigned short tcp_server::port(void)
{
    return port_;
}

boost::asio::ip::address tcp_server::ip_address(void)
{
	return ip_address_;
}

void tcp_server::start_accept(void)
{
    boost::shared_ptr<tcp_connection> new_connection = tcp_connection::create(net_manager_);

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
        boost::asio::placeholders::error));
}

//private

void tcp_server::handle_accept(boost::shared_ptr<tcp_connection> _new_connection, const boost::system::error_code& _error)
{
    BOOST_LOG_TRIVIAL(info) << "INFO handle_accept: handled";
    if (!_error)
    {
        _new_connection->start();
    }
    start_accept();
}

