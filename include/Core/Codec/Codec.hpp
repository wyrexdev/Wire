#pragma once

#include "Core/Codec/Gzip/Gzip.hpp"
#include "Core/Codec/CodecType.hpp"

#include <string>

namespace Wire
{
    namespace Core
    {
        class C
        {
        public:
            void decode(std::string input, std::string& output);

            void setCodec(int codec);

        private:
            int codec;
        };
        
    } // namespace Core
} // namespace Wire
