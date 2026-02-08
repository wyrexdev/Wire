#pragma once

#include <zlib.h>
#include <cstdint>
#include <vector>
#include <string>
#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>

namespace Wire
{
    namespace Core
    {
        namespace Codec
        {
            class Gzip
            {
            public:
                Gzip();
                ~Gzip();

                bool decode(const uint8_t *in, size_t inSize, std::vector<uint8_t> &out);
                bool feed(const uint8_t *data, size_t len, std::vector<uint8_t> &out);

                void reset();

            private:
                z_stream zs{};
                bool initialized = false;
                uint8_t outBuf[8192];
            };
        } // namespace Codec
    } // namespace Core
} // namespace Wire
