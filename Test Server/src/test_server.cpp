#include "server_certificate.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// HTTP Response for given request
template<class Body, class Allocator, class Send>
void handle_request(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send)
{
    // Create a bad request response
    auto const bad_request =
    [&req](beast::string_view why)
    {
        http::response<http::string_body> res{http::status::bad_request, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.keep_alive(req.keep_alive());
        res.body() = std::string(why);
        res.prepare_payload();
        return res;
    };

    // Make sure we can handle the method
    if(req.method() != http::verb::get)
    {
      return send(bad_request("Unknown HTTP-method"));
    }
    else if (req.target() == "/")
    {
      // Respond to GET request
      http::response<http::string_body> res;
      res.version(11);
      res.result(http::status::ok);
      res.set(http::field::server, "Pi");
      res.body() = "Accepted";
      res.prepare_payload();
      return send(std::move(res));
    }
    else if (req.target() == "/cups")
    {
    // Respond to GET request
      http::response<http::string_body> res;
      res.version(11);
      res.result(http::status::ok);
      res.set(http::field::server, "Pi");
      res.body() = "Cup Levels";
      res.prepare_payload();
      return send(std::move(res));
    }
    else if (req.target() == "/quantity")
    {
    // Respond to GET request
      http::response<http::string_body> res;
      res.version(11);
      res.result(http::status::ok);
      res.set(http::field::server, "Pi");
      res.body() = "Quantities";
      res.prepare_payload();
      return send(std::move(res));
    }
    else if (req.target() == "/order")
    {
    // Respond to GET request
      http::response<http::string_body> res;
      res.version(11);
      res.result(http::status::ok);
      res.set(http::field::server, "Pi");
      res.body() = "Making Drink...";
      res.prepare_payload();
      return send(std::move(res));
    }
}

// Failure
void fail(beast::error_code ec, char const* what)
{
  std::cerr << what << ": " << ec.message() << "\n";
}

// Lambda function to send HTTP message
template<class Stream>
struct send_lambda
{
  Stream& stream_;
  bool& close_;
  beast::error_code& ec_;

  explicit send_lambda(Stream& stream, bool& close, beast::error_code& ec) : stream_(stream), close_(close), ec_(ec)
  {
  }

  template<bool isRequest, class Body, class Fields>
  void operator()(http::message<isRequest, Body, Fields>&& msg) const
  {
    // Should we close connection
    close_ = msg.need_eof();

    // Serializer for const messages
    http::serializer<isRequest, Body, Fields> sr{msg};
    http::write(stream_, sr, ec_);
  }
};

// Handle HTTP server connection
void do_session(tcp::socket& socket, ssl::context& ctx)
{
  bool close = false;
  beast::error_code ec;

  ssl::stream<tcp::socket&> stream{socket, ctx};

  stream.handshake(ssl::stream_base::server, ec);
  if (ec)
  {
    return fail(ec, "handshake");
  }


  // Buffer to persist across reads
  beast::flat_buffer buffer;

  // Lambda to send messages
  send_lambda<ssl::stream<tcp::socket&>> lambda{stream, close, ec};

  for(;;)
  {
    // Read a request
    http::request<http::string_body> req;
    http::read(stream, buffer, req, ec);
    if (ec == http::error::end_of_stream)
    {
      break;
    }
    if (ec)
    { 
      return fail(ec, "read");
    }
    else
    {
      // Write the message to standard out
      std::cout << req << std::endl;
    }
    

    // Send Response
    handle_request(std::move(req), lambda);
    if (ec)
    {
      return fail(ec, "write");
    }
    if (close)
    {
      break;
    }
  }

  // Send SSL shutdown
  stream.shutdown(ec);
  if (ec)
  {
    return fail(ec, "shutdown");
  }
}

int main(int argc, char* argv[])
{
  try
  {
    auto const address = net::ip::make_address_v4("127.0.0.1");
    auto const port = static_cast<unsigned short>(8080);

    net::io_context ioc;

    ssl::context ctx(ssl::context::tlsv12);

    load_server_certificate(ctx);

    // Create Acceptor
    tcp::acceptor acceptor_{ioc, {address, port}};
    for(;;)
    {
      // Receive new connection
      tcp::socket socket{ioc};

      // Block until connection
      acceptor_.accept(socket);

      std::thread{std::bind(
        &do_session, 
        std::move(socket),
        std::ref(ctx)
      )}.detach();
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
}