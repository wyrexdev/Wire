#include "HTTP/HttpParser.hpp"

namespace Wire
{
    namespace HTTP
    {
        Core::Response Parser::parse(const std::string& raw) {
            Core::Response res;

            auto lines = Utils::String::split(raw, "\n");

            for(auto line : lines) {
                std::cout << "Line: " << line << std::endl;
            }

            return res;
        }
    } // namespace HTTP
} // namespace Wire
