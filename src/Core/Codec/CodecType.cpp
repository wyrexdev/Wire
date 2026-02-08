#include "Core/Codec/CodecType.hpp"

namespace Wire
{
    namespace Core
    {
        namespace Codec
        {
            int Type::fromHeader(std::string v) {
                if(v == "gzip") {
                    return 0;
                }

                return -1;
            }
        } // namespace Codec
    } // namespace Core
} // namespace Wire