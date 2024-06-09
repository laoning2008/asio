//
// vm/detail/impl/endpoint.hpp
//

#ifndef ASIO_VM_DETAIL_IMPL_ENDPOINT_IPP
#define ASIO_VM_DETAIL_IMPL_ENDPOINT_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <asio/detail/config.hpp>

#if defined(ASIO_HAS_VM_SOCKETS)

#include <asio/detail/socket_ops.hpp>
#include <asio/detail/throw_error.hpp>
#include <asio/error.hpp>
#include <asio/vm/detail/endpoint.hpp>

#include <asio/detail/push_options.hpp>

namespace asio {
namespace vm {
namespace detail {

endpoint::endpoint() ASIO_NOEXCEPT
{
  memset(&data_, 0, sizeof(data_));
  data_.vm.svm_family = AF_VSOCK;
  data_.vm.svm_port = 0;
  data_.vm.svm_cid = VMADDR_CID_ANY;
}

endpoint::endpoint(unsigned short port_num) ASIO_NOEXCEPT
{
  memset(&data_, 0, sizeof(data_));
  data_.vm.svm_family = AF_VSOCK;
  data_.vm.svm_port = port_num;
  data_.vm.svm_cid = VMADDR_CID_ANY;
}

endpoint::endpoint(const asio::vm::cid& cid, unsigned short port_num) ASIO_NOEXCEPT
{
  memset(&data_, 0, sizeof(data_));
  data_.vm.svm_family = AF_VSOCK;
  data_.vm.svm_port = port_num;
  data_.vm.svm_cid = cid.to_uint();
}

void endpoint::resize(std::size_t new_size)
{
  if (new_size > sizeof(asio::detail::sockaddr_storage_type))
  {
    asio::error_code ec(asio::error::invalid_argument);
    asio::detail::throw_error(ec);
  }
}

unsigned short endpoint::port() const ASIO_NOEXCEPT
{
  return data_.vm.svm_port;
}

void endpoint::port(unsigned short port_num) ASIO_NOEXCEPT
{
    data_.vm.svm_port = port_num;
}

asio::vm::cid endpoint::cid() const ASIO_NOEXCEPT
{
    return asio::vm::cid(data_.vm.svm_cid);
}

void endpoint::cid(const asio::vm::cid& cid) ASIO_NOEXCEPT
{
  endpoint tmp_endpoint(cid, port());
  data_ = tmp_endpoint.data_;
}

bool operator==(const endpoint& e1, const endpoint& e2) ASIO_NOEXCEPT
{
  return e1.cid() == e2.cid() && e1.port() == e2.port();
}

bool operator<(const endpoint& e1, const endpoint& e2) ASIO_NOEXCEPT
{
  if (e1.cid() < e2.cid())
    return true;
  if (e1.cid() != e2.cid())
    return false;
  return e1.port() < e2.port();
}

} // namespace detail
} // namespace vm
} // namespace asio

#include <asio/detail/pop_options.hpp>

#endif // defined(ASIO_HAS_VM_SOCKETS)

#endif // ASIO_VM_DETAIL_IMPL_ENDPOINT_IPP