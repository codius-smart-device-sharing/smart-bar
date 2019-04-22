#include "root_certificates.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
namespace ssl = net::ssl;           // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

// Performs an HTTP GET and prints the response
int main(int argc, char** argv)
{
    try
    {
        // Check command line arguments.
        if(argc != 3)
        {
            std::cerr <<
                "Usage: ./client <method> <target>\n" <<
                "Example:\n" <<
                "    ./client OPTIONS /\n" <<
                "    ./client GET /cups\n" <<
                "    ./client GET /quantity\n" <<
                "    ./client GET /order\n";
            return EXIT_FAILURE;
}
        auto const host = "127.0.0.1";
        auto const ip = net::ip::make_address_v4(host);
        auto const port = static_cast<unsigned short>(8080);
        std::string method(argv[1]);
        std::string target(argv[2]);
        int version = 11;

        // The io_context is required for all I/O
        net::io_context ioc;

        // SSL Context
        //ssl::context ctx(ssl::context::tlsv12_client);

        // This holds root cert used for verification
        //load_root_certificates(ctx);


        // Verify remote server's cert
        //ctx.set_verify_mode(ssl::verify_peer);

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        //ssl::stream<tcp::socket> stream(ioc, ctx);
        tcp::socket sock{ioc};
        tcp::endpoint endpoint_{ip, port};

        // Set SNI Hostname
        // if (!SSL_set_tlsext_host_name(stream.native_handle(), host))
        // {
        //     beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
        //     throw beast::system_error{ec};
        // }
        
        // Look up domain name
        auto const results = resolver.resolve(endpoint_);

        // Make the connection on the IP address
        //tcp::socket::lowest_layer_type& sock = stream.lowest_layer();
        sock.connect(endpoint_);

        // SSl handshake
        //stream.handshake(ssl::stream_base::client);

        // Set up an HTTP request message
        http::request<http::string_body> req;
        req.version(version);

        if (method == "GET")
        {
            std::cout << "Sending GET request\n" << std::endl;
            req.method(http::verb::get);
        }
        else if (method == "OPTIONS")
        {
            std::cout << "Sending OPTIONS request\n" << std::endl;
            req.method(http::verb::options);
        }
        else if (method == "POST")
        {
            std::cout << "Sending POST request\n" << std::endl;
            req.method(http::verb::post);
            std::string body_("{\"method\":\"POST\",\"headers\":{\"Content-Type\":\"application/json\"},\"body\":{\"ingredients\":{\"Whiskey\":1,\"Coke\":1}}}");
            req.body() = body_;
            req.prepare_payload();
        }
        else
        {
            std::cout << "Something went wrong" << std::endl;
        }
        
        req.target(target);
        req.set(http::field::host, ip);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        http::write(sock/*stream*/, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(sock/*stream*/, buffer, res);

        // Write the message to standard out
        std::cout << "Received response..." << std::endl;
        std::cout << res << std::endl;

        // Gracefully close the socket
        beast::error_code ec;
        sock.shutdown(tcp::socket::shutdown_send, ec);
        // stream.shutdown(ec);
        // if(ec == net::error::eof)
        // {
        //     ec = {};
        // }
        // if (ec)
        // {
        //     throw beast::system_error{ec};
        // }
        // If we get here then the connection is closed gracefully
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
