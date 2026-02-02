#pragma once

#include <string>
#include <vector>

namespace Wire
{
    namespace Utils
    {
        class String
        {
        public:
            static std::vector<std::string> split(const std::string &str, std::string delimiter);
        };
    } // namespace Utils

} // namespace Wire
