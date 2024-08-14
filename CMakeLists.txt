cmake_minimum_required(VERSION 3.28)
project(libselftest)

set(CMAKE_CXX_STANDARD 23)

add_library(libselftest STATIC selftest.cpp
        sha256.cpp
        sha256.h)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git)
FetchContent_MakeAvailable(cpr)

find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(OpenSSL REQUIRED COMPONENTS SSL Crypto)

target_link_libraries(libselftest PRIVATE cpr::cpr OpenSSL::SSL OpenSSL::Crypto Boost::filesystem Boost::system)
