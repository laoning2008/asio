//
// vm/impl/cid.hpp
//

#ifndef ASIO_VM_IMPL_CID_HPP
#define ASIO_VM_IMPL_CID_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if !defined(ASIO_NO_IOSTREAM)

#include <asio/detail/throw_error.hpp>

#include <asio/detail/push_options.hpp>

namespace asio {
namespace vm {

template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const cid& addr)
{
  return os << addr.to_uint();
}

} // namespace vm
} // namespace asio

#include <asio/detail/pop_options.hpp>

#endif // !defined(ASIO_NO_IOSTREAM)

#endif // ASIO_VM_IMPL_CID_HPP