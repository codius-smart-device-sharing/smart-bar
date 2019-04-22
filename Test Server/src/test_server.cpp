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
#include <regex>
#include <map>
#include <mutex>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

std::mutex m;
std::map<std::string, int> quantities;
std::map<std::string, int> motors;
int cup_count = 12;
auto const address = net::ip::make_address_v4("127.0.0.1");
auto const port = static_cast<unsigned short>(8080);
// auto const address = net::ip::make_address_v4("10.186.91.134");
// auto const port = static_cast<unsigned short>(5001);
bool makeDrink = false;
bool orderDone = true;

// Make Drink
void make_drink(std::map<std::string, int> recipe)
{
  for(auto &keys : recipe)
  {
    switch (motors[keys.first])
    {
      case 0:
        std::cout << "Pouring: " << keys.first << std::endl;
        std::cout << "Amount: " << keys.second << std::endl;
        std::cout << "Motor #: 0" << std::endl;
        break;

      case 1:
        std::cout << "Pouring: " << keys.first << std::endl;
        std::cout << "Amount: " << keys.second << std::endl;
        std::cout << "Motor #: 1" << std::endl;
        break;

      case 2:
        std::cout << "Pouring: " << keys.first << std::endl;
        std::cout << "Amount: " << keys.second << std::endl;
        std::cout << "Motor #: 2" << std::endl;
        break;

      case 3:
        std::cout << "Pouring: " << keys.first << std::endl;
        std::cout << "Amount: " << keys.second << std::endl;
        std::cout << "Motor #: 3" << std::endl;
        break;

      case 4:
        std::cout << "Pouring: " << keys.first << std::endl;
        std::cout << "Amount: " << keys.second << std::endl;
        std::cout << "Motor #: 4" << std::endl;
        break;

      case 5:
        std::cout << "Pouring: " << keys.first << std::endl;
        std::cout << "Amount: " << keys.second << std::endl;
        std::cout << "Motor #: 5" << std::endl;
        break;
    
      default:
        break;
    }
    // std::cout << keys.first << ":" << keys.second << std::endl;
  }
}
// Get cup levels
std::string get_cup_levels()
{
  m.lock();
  std::string cups = std::to_string(cup_count);
  m.unlock();
  return cups;
}

// Get quantities
std::string get_quantities(std::string str)
{
  std::string delimeter("=");
  // Get type of liquid from request
  std::string sub(str.substr(str.find(delimeter) + 1, str.length()));
  if (sub == str)
  {
    return std::string("No type sent.");
  }
  // Get quantity level from stored levels for certain type
  m.lock();
  std::string quantity(std::to_string(quantities[sub]));
  m.unlock();
  return quantity;
}

// parse order into individual ingredients (partially mimics a JSON parser)
std::map<std::string, int> parse_order(std::string body_)
{
  std::regex appos("\"");
  std::string order(body_.substr(body_.find("ingredients"), body_.length()));
  // std::cout << order << std::endl;
  int first_ingredient = order.find("{");
  int second_ingredient = order.find(",");
  int end_ingredients = order.find("}");
  std::string ingredient1(std::regex_replace(order.substr(first_ingredient + 1, second_ingredient - first_ingredient - 1), appos, ""));
  // std::cout << ingredient1 << std::endl;
  std::string ingredient2(std::regex_replace(order.substr(second_ingredient + 1, end_ingredients - second_ingredient - 1), appos, ""));
  // std::cout << ingredient2 << std::endl;

  std::string name1(ingredient1.substr(0, ingredient1.find(":")));
  std::string amount1(ingredient1.substr(ingredient1.find(":") + 1, ingredient1.length()));
  std::string name2(ingredient2.substr(0, ingredient2.find(":")));
  std::string amount2(ingredient2.substr(ingredient2.find(":") + 1, ingredient2.length()));

  std::map<std::string, int> recipe;
  recipe.insert(std::pair<std::string, int>(name1, std::stoi(amount1)));
  recipe.insert(std::pair<std::string, int>(name2, std::stoi(amount2)));
  return recipe;
}
// HTTP Response for given request
template<class Body, class Allocator, class Send>
void handle_request(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send)
{
    std::string target(req.target());
    std::regex cups("/cups");
    std::regex quantity("/quantity");
    std::regex order("/order");
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
    if((req.method() != http::verb::get) && (req.method() != http::verb::options) && (req.method() != http::verb::post))
    {
      return send(bad_request("Unknown HTTP-method"));
    }

    // Respond to OPTIONS request
    if (req.method() == http::verb::options)
    {
      http::response<http::string_body> res;
      res.version(11);
      res.result(http::status::no_content);
      res.set(http::field::server, "SmartBar");
      res.set(http::field::access_control_allow_origin, "*");
      res.set(http::field::access_control_allow_methods, "OPTIONS, GET");
      res.prepare_payload();
      return send(std::move(res));
    }
    // Respond to GET request
    else if (req.method() == http::verb::get)
    {
      if (std::regex_search(target, cups))
      {
        http::response<http::string_body> res;
        res.version(11);
        res.result(http::status::ok);
        res.set(http::field::server, "SmartBar");
        res.body() = get_cup_levels();
        res.prepare_payload();
        return send(std::move(res));
      }
      else if (std::regex_search(target, quantity))
      {
        // /quantity?ingredient=...
        http::response<http::string_body> res;
        res.version(11);
        res.result(http::status::ok);
        res.set(http::field::server, "SmartBar");
        res.body() = get_quantities(target);
        res.prepare_payload();
        return send(std::move(res));
      }
    }
    else if (req.method() == http::verb::post)
    {
      if (std::regex_search(target, order))
      {
        http::response<http::string_body> res;
        res.version(11);
        res.result(http::status::ok);
        res.set(http::field::server, "SmartBar");
        res.body() = "Making Drink...";
        res.prepare_payload();
        std::map<std::string, int> recipe(parse_order(req.body()));
        std::thread ordering(std::bind(&make_drink, recipe));
        ordering.join();
        // make_drink(recipe);
        return send(std::move(res));
      }
    }
    else
    {
      return send(bad_request("Unknown Target"));
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
void do_session(tcp::socket& socket/*, ssl::context& ctx*/)
{
  bool close = false;
  beast::error_code ec;

  // ssl::stream<tcp::socket&> stream{socket, ctx};

  // stream.handshake(ssl::stream_base::server, ec);
  // if (ec)
  // {
  //   return fail(ec, "handshake");
  // }


  // Buffer to persist across reads
  beast::flat_buffer buffer;

  // Lambda to send messages
  send_lambda<tcp::socket/*ssl::stream<tcp::socket&>*/> lambda{socket/*stream*/, close, ec};

  for(;;)
  {
    // Read a request
    http::request<http::string_body> req;
    http::read(socket/*stream*/, buffer, req, ec);
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
  // stream.shutdown(ec);
  socket.shutdown(tcp::socket::shutdown_send, ec);
  // if (ec)
  // {
  //   return fail(ec, "shutdown");
  // }
}

int start_server()
{
  try
  {
    net::io_context ioc{1};

    //ssl::context ctx(ssl::context::tlsv12);

    //load_server_certificate(ctx);

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
        std::move(socket)
        /*,std::ref(ctx)*/
      )}.detach();
    }
    // tcp::socket socket{ioc};
    // acceptor_.accept(socket);
    // do_session(socket);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}

int main(int argc, char* argv[])
{
  // Set drink amounts
  quantities.insert(std::pair<std::string, int>("Whiskey", 60));
  quantities.insert(std::pair<std::string, int>("Vodka", 60));
  quantities.insert(std::pair<std::string, int>("Rum", 60));
  quantities.insert(std::pair<std::string, int>("Coke", 33));
  quantities.insert(std::pair<std::string, int>("Sprite", 33));
  quantities.insert(std::pair<std::string, int>("Cranberry", 33));

  motors.insert(std::pair<std::string, int>("Whiskey", 0));
  motors.insert(std::pair<std::string, int>("Vodka", 1));
  motors.insert(std::pair<std::string, int>("Rum", 2));
  motors.insert(std::pair<std::string, int>("Coke", 3));
  motors.insert(std::pair<std::string, int>("Sprite", 4));
  motors.insert(std::pair<std::string, int>("Cranberry", 5));
  start_server();
  // std::thread server(start_server);
  // server.join();
  // for(;;)
  // {
  //   start_server();
  //   if ((makeDrink == true) && (orderDone == true))
  //   {
  //     std::thread(make_drink).detach();
  //   }
  // }
}