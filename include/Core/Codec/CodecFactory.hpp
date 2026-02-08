#pragma once

#include "Core/Codec/Codec.hpp"
#include "Core/Codec/CodecType.hpp"

namespace Wire
{
    namespace Core
    {
        namespace Codec
        {
            class Factory
            {
            public:
                static Core::C create(Codec::Type type);
            };
        } // namespace Codec
    } // namespace Core
} // namespace Wire
