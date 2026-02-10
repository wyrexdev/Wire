#pragma once
#include <string>

namespace Wire::HTTP
{
    std::string decodeChunked(const std::string &in);
}
