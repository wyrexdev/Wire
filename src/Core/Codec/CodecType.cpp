#include "Core/Codec/CodecType.hpp"

namespace Wire
{
    namespace Core
    {
        namespace Codec
        {
            Type Type::fromHeader(std::string v) {
                Type t;
                if(v == "gzip") {
                    t.setCodec(0);
                }

                t.setCodec(-1);

                return t;
            }

            void Type::setCodec(int i) {
                codec = i;
            }

            int Type::getCodec() {
                return codec;
            }
        } // namespace Codec
    } // namespace Core
} // namespace Wire