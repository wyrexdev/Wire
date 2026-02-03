#pragma once

#include <algorithm>
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

            static std::string trim(std::string s);

            static std::string toLowerCase(std::string s);
            static std::string toUpperCase(std::string s);

        private:
            static std::string &ltrim(std::string &s);
            static std::string &rtrim(std::string &s);
        };
    } // namespace Utils

} // namespace Wire
