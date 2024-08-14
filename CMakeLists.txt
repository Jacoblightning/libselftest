cmake_minimum_required(VERSION 3.28)
project(libselftest)

set(CMAKE_CXX_STANDARD 23)

add_library(libselftest STATIC
        libselftest/selftest.cpp
        libselftest/sha256.cpp
        libselftest/sha256.h
)

# Set include directories for the library (public for external use)
target_include_directories(libselftest
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libselftest
)

# Set the public header files
set_target_properties(libselftest PROPERTIES
        PUBLIC_HEADER include/libselftest/selftest.h
)

# Include directories for dependencies
target_include_directories(libselftest
        PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${OpenSSL_INCLUDE_DIR}
)

include(GNUInstallDirs)

# Fetch and make available the cpr library
include(FetchContent)
FetchContent_Declare(cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
)
FetchContent_MakeAvailable(cpr)

# Find and link against Boost and OpenSSL
find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(OpenSSL REQUIRED COMPONENTS SSL Crypto)

target_link_libraries(libselftest PRIVATE
        cpr::cpr
        OpenSSL::SSL
        OpenSSL::Crypto
        Boost::filesystem
        Boost::system
)

# Install the library and public headers
install(TARGETS libselftest
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libselftest
)
