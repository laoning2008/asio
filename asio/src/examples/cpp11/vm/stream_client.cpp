#include <cstdlib>
#include <cstring>
#include <iostream>
#include <asio.hpp>

#if defined(ASIO_HAS_VM_SOCKETS)

using asio::vm::stream_protocol;
using asio::vm::cid;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: stream_client <port>\n";
      return 1;
    }

    asio::io_context io_context;

    stream_protocol::socket s(io_context);
    s.connect(stream_protocol::endpoint(cid::local(), atoi(argv[1])));

    using namespace std; // For strlen.
    std::cout << "Enter message: ";
    char request[max_length];
    std::cin.getline(request, max_length);
    size_t request_length = strlen(request);
    asio::write(s, asio::buffer(request, request_length));

    char reply[max_length];
    size_t reply_length = asio::read(s,
        asio::buffer(reply, request_length));
    std::cout << "Reply is: ";
    std::cout.write(reply, reply_length);
    std::cout << "\n";
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