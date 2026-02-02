#include "Utils/String.hpp"

namespace Wire
{
    namespace Utils
    {
        std::vector<std::string> String::split(const std::string &str, std::string delimiter)
        {
            std::vector<std::string> result;

            if (delimiter.empty())
                return result;

            size_t start = 0;
            size_t pos;

            while ((pos = str.find(delimiter, start)) != std::string::npos)
            {
                if (pos > start)
                    result.emplace_back(str.substr(start, pos - start));

                start = pos + delimiter.length();
            }

            if (start < str.length())
                result.emplace_back(str.substr(start));

            return result;
        }
    } // namespace Utils
} // namespace Wire
