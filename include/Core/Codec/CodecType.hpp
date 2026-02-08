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
                enum Types {
                    Indetity = -1,
                    GZip = 0,
                    Brotli = 1
                };

                static Type fromHeader(std::string v);

                int getCodec();

            private:
                void setCodec(int c);

                int codec = -1;
            };
        } // namespace Codec
    } // namespace Core
} // namespace Wire
