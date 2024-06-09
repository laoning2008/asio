//
// vm/cid.hpp
//

#ifndef ASIO_VM_CID_HPP
#define ASIO_VM_CID_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <asio/detail/config.hpp>

#if defined(ASIO_HAS_VM_SOCKETS)

#include <asio/detail/cstdint.hpp>
#include <asio/detail/socket_types.hpp>

#if !defined(ASIO_NO_IOSTREAM)
# include <iosfwd>
#endif // !defined(ASIO_NO_IOSTREAM)

#include <asio/detail/push_options.hpp>

namespace asio {
namespace vm {

/// Implements VSOCK style context ID.
/**
 * The asio::vm::cid class provides the ability to use and
 * manipulate VSOCK context IDs.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
class cid
{
public:
  /// The type used to represent an address as an unsigned integer.
  typedef uint_least32_t uint_type;

  /// Default constructor.
  cid() ASIO_NOEXCEPT
  {
    addr_.svm_cid = VMADDR_CID_ANY;
  }

  /// Construct an address from an unsigned integer.
  ASIO_DECL explicit cid(uint_type c);

  /// Copy constructor.
  cid(const cid& other) ASIO_NOEXCEPT
    : addr_(other.addr_)
  {
  }

#if defined(ASIO_HAS_MOVE)
  /// Move constructor.
  cid(cid&& other) ASIO_NOEXCEPT
    : addr_(other.addr_)
  {
  }
#endif // defined(ASIO_HAS_MOVE)

  /// Assign from another address.
  cid& operator=(const cid& other) ASIO_NOEXCEPT
  {
    addr_ = other.addr_;
    return *this;
  }

#if defined(ASIO_HAS_MOVE)
  /// Move-assign from another address.
  cid& operator=(cid&& other) ASIO_NOEXCEPT
  {
    addr_ = other.addr_;
    return *this;
  }
#endif // defined(ASIO_HAS_MOVE)

  /// Get the address as an unsigned integer
  ASIO_DECL uint_type to_uint() const ASIO_NOEXCEPT;

  /// Determine whether the address is a loopback address.
  ASIO_DECL bool is_local() const ASIO_NOEXCEPT;

  /// Determine whether the address is unspecified.
  ASIO_DECL bool is_hypervisor() const ASIO_NOEXCEPT;

  /// Determine whether the address is a any address.
  ASIO_DECL bool is_any() const ASIO_NOEXCEPT;

  /// Compare two addresses for equality.
  friend bool operator==(const cid& a1,
      const cid& a2) ASIO_NOEXCEPT
  {
    return a1.addr_.svm_cid == a2.addr_.svm_cid;
  }

  /// Compare two addresses for inequality.
  friend bool operator!=(const cid& a1,
      const cid& a2) ASIO_NOEXCEPT
  {
    return a1.addr_.svm_cid != a2.addr_.svm_cid;
  }

  /// Compare addresses for ordering.
  friend bool operator<(const cid& a1,
      const cid& a2) ASIO_NOEXCEPT
  {
    return a1.to_uint() < a2.to_uint();
  }

  /// Compare addresses for ordering.
  friend bool operator>(const cid& a1,
      const cid& a2) ASIO_NOEXCEPT
  {
    return a1.to_uint() > a2.to_uint();
  }

  /// Compare addresses for ordering.
  friend bool operator<=(const cid& a1,
      const cid& a2) ASIO_NOEXCEPT
  {
    return a1.to_uint() <= a2.to_uint();
  }

  /// Compare addresses for ordering.
  friend bool operator>=(const cid& a1,
      const cid& a2) ASIO_NOEXCEPT
  {
    return a1.to_uint() >= a2.to_uint();
  }

  /// Obtain an address object that represents any address.
  static cid any() ASIO_NOEXCEPT
  {
    return cid();
  }

  /// Obtain an address object that represents the loopback address.
  static cid local() ASIO_NOEXCEPT
  {
    return cid(VMADDR_CID_LOCAL);
  }

  /// Obtain an address object that represents the broadcast address.
  static cid hypervisor() ASIO_NOEXCEPT
  {
    return cid(VMADDR_CID_HYPERVISOR);
  }

private:
  // The underlying VSOCK address.
  asio::detail::sockaddr_vm_type addr_;
};

/// Create an IPv4 address from an unsigned integer in host byte order.
/**
 * @relates cid
 */
inline cid make_cid(cid::uint_type id)
{
  return cid(id);
}

#if !defined(ASIO_NO_IOSTREAM)

/// Output an address as a string.
/**
 * Used to output a human-readable string for a specified address.
 *
 * @param os The output stream to which the string will be written.
 *
 * @param addr The address to be written.
 *
 * @return The output stream.
 *
 * @relates asio::vm::cid
 */
template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const cid& addr);

#endif // !defined(ASIO_NO_IOSTREAM)

} // namespace vm
} // namespace asio

#include <asio/detail/pop_options.hpp>

#include <asio/vm/impl/cid.hpp>
#if defined(ASIO_HEADER_ONLY)
# include <asio/vm/impl/cid.ipp>
#endif // defined(ASIO_HEADER_ONLY)

#endif // defined(ASIO_HAS_VM_SOCKETS)

#endif // ASIO_VM_CID_HPP