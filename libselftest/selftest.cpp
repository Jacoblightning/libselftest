#include "libselftest/selftest.h"

#include <cpr/cpr.h>
#include <boost/dll/runtime_symbol_info.hpp>

#include "libselftest/sha256.h"

std::string HashSelf() {
    char My_Hash[65];

    const std::string path = boost::dll::program_location().string();
    sha256_file(path.c_str(), My_Hash);
    std::string My_CPP_Hash = My_Hash;
    return My_CPP_Hash;
}