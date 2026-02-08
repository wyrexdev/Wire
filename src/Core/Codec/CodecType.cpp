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
                    t.setCodec(Types::GZip);
                }

                t.setCodec(Types::Indetity);

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