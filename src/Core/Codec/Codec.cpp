#include "Core/Codec/Codec.hpp"

namespace Wire
{
    namespace Core
    {
        void C::decode(std::string input, std::string &output)
        {
            if (codec == Codec::Type::Types::GZip)
            {
                Codec::Gzip gzip;

                std::vector<uint8_t> decoded;

                if (!gzip.decode(reinterpret_cast<const uint8_t *>(input.data()), input.size(), decoded))
                {
                    return;
                }

                output.assign(decoded.begin(), decoded.end());
            } else {
                output = input;
            }
        }

        void C::setCodec(int c)
        {
            codec = c;
        }
    } // namespace Core
} // namespace Wire
