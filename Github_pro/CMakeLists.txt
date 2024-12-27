cmake_minimum_required(VERSION 3.22)

project(github_one)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

# Boost 1.86.0, OpenSSL 3.3.2

set(BOOST_ROOT "/home/recall/Desktop/libraries/boost_1_86_0/")
set(Boost_INCLUDE_DIRS "${BOOST_ROOT}/boost/")

#set(OPENSSL_ROOT "/home/recall/Libraries/openssl-3.3.2/")
#set(CMAKE_PREFIX_PATH "${OPENSSL_ROOT}/")

#include_directories("${OPENSSL_ROOT}/include/")
#link_directories("${OPENSSL_ROOT}/")


#find_package(OpenSSL REQUIRED)
find_package(Boost 1.86.0 REQUIRED)


add_definitions(-DBOOST_ASIO_STANDALONE)
add_executable(server async_server.cpp)
add_executable(client sync_client.cpp)


#target_link_libraries(chat-server PRIVATE OpenSSL::Crypto OpenSSL::SSL)
#target_link_libraries(chat-client PRIVATE OpenSSL::Crypto OpenSSL::SSL)

target_include_directories(server PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(client PRIVATE ${Boost_INCLUDE_DIRS})


