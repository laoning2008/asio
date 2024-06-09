//
// vm/stream_protocol.hpp
//

#ifndef ASIO_VM_STREAM_PROTOCOL_HPP
#define ASIO_VM_STREAM_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <asio/detail/config.hpp>

#if defined(ASIO_HAS_VM_SOCKETS)

#include <asio/basic_socket_acceptor.hpp>
#include <asio/basic_socket_iostream.hpp>
#include <asio/basic_stream_socket.hpp>
#include <asio/detail/socket_types.hpp>
#include <asio/vm/basic_endpoint.hpp>
#include <asio/vm/cid.hpp>

#include <asio/detail/push_options.hpp>

namespace asio {
namespace vm {

/// Encapsulates the flags needed for stream-oriented VSOCK sockets.
/**
 * The asio::vm::stream_protocol class contains flags necessary for
 * stream-oriented VSOCK sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class stream_protocol
{
public:
  /// Obtain an identifier for the type of the protocol.
  int type() const ASIO_NOEXCEPT
  {
    return SOCK_STREAM;
  }

  /// Obtain an identifier for the protocol.
  int protocol() const ASIO_NOEXCEPT
  {
    return 0;
  }

  /// Obtain an identifier for the protocol family.
  int family() const ASIO_NOEXCEPT
  {
    return AF_VSOCK;
  }

  /// The type of a VSOCK endpoint.
  typedef basic_endpoint<stream_protocol> endpoint;

  /// The VSOCK socket type.
  typedef basic_stream_socket<stream_protocol> socket;

  /// The VSOCK acceptor type.
  typedef basic_socket_acceptor<stream_protocol> acceptor;

#if !defined(ASIO_NO_IOSTREAM)
  /// The VSOCK iostream type.
  typedef basic_socket_iostream<stream_protocol> iostream;
#endif // !defined(ASIO_NO_IOSTREAM)
};

} // namespace vm
} // namespace asio

#include <asio/detail/pop_options.hpp>

#endif // defined(ASIO_HAS_VM_SOCKETS)

#endif // ASIO_VM_STREAM_PROTOCOL_HPP