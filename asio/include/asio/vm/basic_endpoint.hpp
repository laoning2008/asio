//
// vm/basic_endpoint.hpp
//

#ifndef ASIO_VM_BASIC_ENDPOINT_HPP
#define ASIO_VM_BASIC_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <asio/detail/config.hpp>

#if defined(ASIO_HAS_VM_SOCKETS)

#include <asio/vm/cid.hpp>
#include <asio/vm/detail/endpoint.hpp>

#if !defined(ASIO_NO_IOSTREAM)
# include <iosfwd>
#endif // !defined(ASIO_NO_IOSTREAM)

#include <asio/detail/push_options.hpp>

namespace asio {
namespace vm {

/// Type used for storing port numbers.
typedef uint_least16_t port_type;

/// Describes an endpoint for a VSOCK socket.
/**
 * The :asio::vm::basic_endpoint class template describes an endpoint
 * that may be associated with a particular VSOCK socket.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * Endpoint.
 */
template <typename Protocol>
class basic_endpoint
{
public:
  /// The protocol type associated with the endpoint.
  typedef Protocol protocol_type;

  /// The type of the endpoint structure. This type is dependent on the
  /// underlying implementation of the socket layer.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined data_type;
#else
  typedef asio::detail::socket_addr_type data_type;
#endif

  /// Default constructor.
  basic_endpoint() ASIO_NOEXCEPT
  {
  }

  /// Construct an endpoint using the specified port.
  basic_endpoint(port_type port_num) ASIO_NOEXCEPT
    : impl_(port_num)
  {
  }

  /// Construct an endpoint using the specified context ID and port.
  basic_endpoint(const asio::vm::cid& cid, port_type port_num) ASIO_NOEXCEPT
    : impl_(cid, port_num)
  {
  }

  /// Copy constructor.
  basic_endpoint(const basic_endpoint& other) ASIO_NOEXCEPT
    : impl_(other.impl_)
  {
  }

#if defined(ASIO_HAS_MOVE)
  /// Move constructor.
  basic_endpoint(basic_endpoint&& other) ASIO_NOEXCEPT
    : impl_(other.impl_)
  {
  }
#endif // defined(ASIO_HAS_MOVE)

  /// Assign from another endpoint.
  basic_endpoint& operator=(const basic_endpoint& other)
  {
    impl_ = other.impl_;
    return *this;
  }

#if defined(ASIO_HAS_MOVE)
  /// Move-assign from another endpoint.
  basic_endpoint& operator=(basic_endpoint&& other) ASIO_NOEXCEPT
  {
    impl_ = other.impl_;
    return *this;
  }
#endif // defined(ASIO_HAS_MOVE)

  /// The protocol associated with the endpoint.
  protocol_type protocol() const ASIO_NOEXCEPT
  {
    return protocol_type();
  }

  /// Get the underlying endpoint in the native type.
  data_type* data() ASIO_NOEXCEPT
  {
    return impl_.data();
  }

  /// Get the underlying endpoint in the native type.
  const data_type* data() const
  {
    return impl_.data();
  }

  /// Get the underlying size of the endpoint in the native type.
  std::size_t size() const ASIO_NOEXCEPT
  {
    return impl_.size();
  }

  /// Set the underlying size of the endpoint in the native type.
  void resize(std::size_t new_size)
  {
    impl_.resize(new_size);
  }

  /// Get the capacity of the endpoint in the native type.
  std::size_t capacity() const ASIO_NOEXCEPT
  {
    return impl_.capacity();
  }

  /// Get the port associated with the endpoint.
  port_type port() const ASIO_NOEXCEPT
  {
    return impl_.port();
  }

  /// Set the port associated with the endpoint.
  void port(port_type port_num) ASIO_NOEXCEPT
  {
    impl_.port(port_num);
  }

  /// Get the CID associated with the endpoint.
  asio::vm::cid cid() const ASIO_NOEXCEPT
  {
    return impl_.cid();
  }

  /// Set the CID associated with the endpoint.
  void cid(const asio::vm::cid& cid) ASIO_NOEXCEPT
  {
    impl_.cid(cid);
  }

  /// Compare two endpoints for equality.
  friend bool operator==(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2) ASIO_NOEXCEPT
  {
    return e1.impl_ == e2.impl_;
  }

  /// Compare two endpoints for inequality.
  friend bool operator!=(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2) ASIO_NOEXCEPT
  {
    return !(e1.impl_ == e2.impl_);
  }

  /// Compare endpoints for ordering.
  friend bool operator<(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2) ASIO_NOEXCEPT
  {
    return e1.impl_ < e2.impl_;
  }

  /// Compare endpoints for ordering.
  friend bool operator>(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2) ASIO_NOEXCEPT
  {
    return e2.impl_ < e1.impl_;
  }

  /// Compare endpoints for ordering.
  friend bool operator<=(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2) ASIO_NOEXCEPT
  {
    return !(e2 < e1);
  }

  /// Compare endpoints for ordering.
  friend bool operator>=(const basic_endpoint<Protocol>& e1,
      const basic_endpoint<Protocol>& e2) ASIO_NOEXCEPT
  {
    return !(e1 < e2);
  }

private:
  // The underlying vm endpoint.
  asio::vm::detail::endpoint impl_;
};

/// Output an endpoint as a string.
/**
 * Used to output a human-readable string for a specified endpoint.
 *
 * @param os The output stream to which the string will be written.
 *
 * @param endpoint The endpoint to be written.
 *
 * @return The output stream.
 *
 * @relates asio::vm::basic_endpoint
 */
template <typename Elem, typename Traits, typename Protocol>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os,
    const basic_endpoint<Protocol>& endpoint)
{
  os << endpoint.cid() << ":"<< endpoint.port();
  return os;
}

} // namespace vm
} // namespace asio

#include <asio/detail/pop_options.hpp>

#endif // defined(ASIO_HAS_VM_SOCKETS)

#endif // ASIO_VM_BASIC_ENDPOINT_HPP