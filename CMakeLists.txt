set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(examples CXX)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/asio/include)


add_executable(vsock_stream_server ${CMAKE_CURRENT_SOURCE_DIR}/asio/src/examples/cpp11/vm/stream_server.cpp)
add_executable(vsock_stream_client ${CMAKE_CURRENT_SOURCE_DIR}/asio/src/examples/cpp11/vm/stream_client.cpp)

add_executable(vsock_datagram_server ${CMAKE_CURRENT_SOURCE_DIR}/asio/src/examples/cpp11/vm/datagram_server.cpp)
add_executable(vsock_datagram_client ${CMAKE_CURRENT_SOURCE_DIR}/asio/src/examples/cpp11/vm/datagram_client.cpp)

