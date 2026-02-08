#include "Core/Codec/CodecFactory.hpp"

namespace Wire
{
    namespace Core
    {
        namespace Codec
        {
            Core::C Factory::create(Type type) {
                Core::C c;
                c.setCodec(type.getCodec());
                
                return c;
            }
        } // namespace Codec
    } // namespace Core
} // namespace Wire