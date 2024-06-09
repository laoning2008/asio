#include <cstdio>
#include <iostream>
#include <array>
#include <functional>
#include <memory>
#include <asio.hpp>

#if defined(ASIO_HAS_VM_SOCKETS)

using asio::vm::stream_protocol;

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(asio::io_context& io_context)
    : socket_(io_context)
  {
  }

  stream_protocol::socket& socket()
  {
    return socket_;
  }

  void start()
  {
    socket_.async_read_some(asio::buffer(data_),
        std::bind(&session::handle_read,
          shared_from_this(),
          asio::placeholders::error,
          asio::placeholders::bytes_transferred));
  }

  void handle_read(const asio::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
      asio::async_write(socket_,
          asio::buffer(data_, bytes_transferred),
          std::bind(&session::handle_write,
            shared_from_this(),
            asio::placeholders::error));
    }
  }

  void handle_write(const asio::error_code& error)
  {
    if (!error)
    {
      socket_.async_read_some(asio::buffer(data_),
          std::bind(&session::handle_read,
            shared_from_this(),
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));
    }
  }

private:
  // The socket used to communicate with the client.
  stream_protocol::socket socket_;

  // Buffer used to store data received from the client.
  std::array<char, 1024> data_;
};

typedef std::shared_ptr<session> session_ptr;

class server
{
public:
  server(asio::io_context& io_context, unsigned int port)
    : io_context_(io_context),
      acceptor_(io_context, stream_protocol::endpoint(port))
  {
    session_ptr new_session(new session(io_context_));
    acceptor_.async_accept(new_session->socket(),
        std::bind(&server::handle_accept, this, new_session,
          asio::placeholders::error));
  }

  void handle_accept(session_ptr new_session,
      const asio::error_code& error)
  {
    if (!error)
    {
      new_session->start();
    }

    new_session.reset(new session(io_context_));
    acceptor_.async_accept(new_session->socket(),
        std::bind(&server::handle_accept, this, new_session,
          asio::placeholders::error));
  }

private:
  asio::io_context& io_context_;
  stream_protocol::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: stream_server <port>\n";
      return 1;
    }

    asio::io_context io_context;
    std::remove(argv[1]);
    using namespace std; // For atoi.
    server s(io_context, atoi(argv[1]));
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

#else // defined(ASIO_HAS_VM_SOCKETS)
# error VSOCK sockets not available on this platform.
#endif // defined(ASIO_HAS_VM_SOCKETS)