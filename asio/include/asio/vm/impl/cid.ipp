//
// vm/impl/cid.ipp
//

#ifndef ASIO_VM_IMPL_CID_IPP
#define ASIO_VM_IMPL_CID_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <asio/detail/config.hpp>
#include <asio/vm/cid.hpp>

#include <asio/detail/push_options.hpp>

namespace asio {
namespace vm {

cid::cid(cid::uint_type c)
{
  addr_.svm_cid = c;
}

cid::uint_type cid::to_uint() const ASIO_NOEXCEPT
{
  return addr_.svm_cid;
}

bool cid::is_local() const ASIO_NOEXCEPT
{
  return VMADDR_CID_LOCAL == to_uint();
}

bool cid::is_hypervisor() const ASIO_NOEXCEPT
{
  return VMADDR_CID_HYPERVISOR == to_uint();
}

bool cid::is_any() const ASIO_NOEXCEPT
{
  return VMADDR_CID_ANY == to_uint();
}

} // namespace vm
} // namespace asio

#include <asio/detail/pop_options.hpp>

#endif // ASIO_VM_IMPL_CID_IPP