//
// vm/detail/endpoint.hpp
//

#ifndef ASIO_VM_DETAIL_ENDPOINT_HPP
#define ASIO_VM_DETAIL_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <asio/detail/config.hpp>

#if defined(ASIO_HAS_VM_SOCKETS)

#include <cstddef>
#include <asio/detail/socket_types.hpp>
#include <asio/detail/push_options.hpp>
#include <asio/vm/cid.hpp>

namespace asio {
namespace vm {
namespace detail {

// Helper class for implementing a VSOCK endpoint.
class endpoint
{
public:
  // Default constructor.
  ASIO_DECL endpoint() ASIO_NOEXCEPT;

  // Construct an endpoint using the specified path name.
  ASIO_DECL endpoint(unsigned short port_num) ASIO_NOEXCEPT;

  // Construct an endpoint using the specified path name.
  ASIO_DECL endpoint(const asio::vm::cid& cid, unsigned short port_num) ASIO_NOEXCEPT;

  // Copy constructor.
  endpoint(const endpoint& other) ASIO_NOEXCEPT
    : data_(other.data_)
  {
  }

  // Assign from another endpoint.
  endpoint& operator=(const endpoint& other) ASIO_NOEXCEPT
  {
    data_ = other.data_;
    return *this;
  }

  // Get the underlying endpoint in the native type.
  asio::detail::socket_addr_type* data() ASIO_NOEXCEPT
  {
    return &data_.base;
  }

  // Get the underlying endpoint in the native type.
  const asio::detail::socket_addr_type* data() const ASIO_NOEXCEPT
  {
    return &data_.base;
  }

  // Get the underlying size of the endpoint in the native type.
  std::size_t size() const ASIO_NOEXCEPT
  {
    return sizeof(asio::detail::sockaddr_vm_type);
  }

  // Set the underlying size of the endpoint in the native type.
  ASIO_DECL void resize(std::size_t size);

  // Get the capacity of the endpoint in the native type.
  std::size_t capacity() const ASIO_NOEXCEPT
  {
    return sizeof(data_);
  }

  // Get the port associated with the endpoint.
  ASIO_DECL unsigned short port() const ASIO_NOEXCEPT;

  // Set the port associated with the endpoint.
  ASIO_DECL void port(unsigned short port_num) ASIO_NOEXCEPT;

  // Get the CID associated with the endpoint.
  ASIO_DECL asio::vm::cid cid() const ASIO_NOEXCEPT;

  // Set the CID associated with the endpoint.
  ASIO_DECL void cid(
      const asio::vm::cid& addr) ASIO_NOEXCEPT;

  // Compare two endpoints for equality.
  ASIO_DECL friend bool operator==(const endpoint& e1,
      const endpoint& e2) ASIO_NOEXCEPT;

  // Compare endpoints for ordering.
  ASIO_DECL friend bool operator<(
      const endpoint& e1, const endpoint& e2) ASIO_NOEXCEPT;

private:
  // The underlying VSOCK socket address.
  union data_union
  {
    asio::detail::socket_addr_type base;
    asio::detail::sockaddr_vm_type vm;
  } data_;

  // The length of the path associated with the endpoint.
  std::size_t path_length_;

  // Initialise with a specified path.
  ASIO_DECL void init(const char* path, std::size_t path_length);
};

} // namespace detail
} // namespace vm
} // namespace asio

#include <asio/detail/pop_options.hpp>

#if defined(ASIO_HEADER_ONLY)
# include <asio/vm/detail/impl/endpoint.ipp>
#endif // defined(ASIO_HEADER_ONLY)

#endif // defined(ASIO_HAS_VM_SOCKETS)

#endif // ASIO_VM_DETAIL_ENDPOINT_HPP