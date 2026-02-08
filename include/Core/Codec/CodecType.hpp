#pragma once

#include <string>

namespace Wire
{
    namespace Core
    {
        namespace Codec
        {
            class Type
            {
            public:
                static int fromHeader(std::string v);
            };
        } // namespace Codec
    } // namespace Core
} // namespace Wire
