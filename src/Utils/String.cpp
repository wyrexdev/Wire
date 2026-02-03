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

        std::string &String::ltrim(std::string &s)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                            std::not1(std::ptr_fun<int, int>(std::isspace))));
            return s;
        }

        std::string &String::rtrim(std::string &s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(),
                                 std::not1(std::ptr_fun<int, int>(std::isspace)))
                        .base(),
                    s.end());
            return s;
        }

        std::string String::trim(std::string s)
        {
            return ltrim(rtrim(s));
        }

        std::string String::toLowerCase(std::string s)
        {
            std::string r;
            r.reserve(s.size());

            for (unsigned char c : s)
                r += std::tolower(c);

            return r;
        }

        std::string String::toUpperCase(std::string s)
        {
            std::string r;
            r.reserve(s.size());

            for (unsigned char c : s)
                r += std::toupper(c);

            return r;
        }
    } // namespace Utils
} // namespace Wire
