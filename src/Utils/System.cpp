#include "Utils/System.hpp"

namespace Wire
{
    namespace Utils
    {
        std::string System::getLanguage() {
            std::string lang = std::locale("").name();
            lang = String::split(lang, ".")[0];
            lang = String::split(lang, "_")[0] + "-" + String::split(lang, "_")[1];

            return lang;
        }
    } // namespace Utils
} // namespace Wire