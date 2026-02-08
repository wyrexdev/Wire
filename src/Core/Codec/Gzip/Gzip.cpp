#include "Core/Codec/Gzip/Gzip.hpp"

namespace Wire
{
    namespace Core
    {
        namespace Codec
        {
            Gzip::Gzip()
            {
                std::memset(&zs, 0, sizeof(zs));
                inflateInit2(&zs, 16 + MAX_WBITS);
                initialized = true;
            }

            Gzip::~Gzip()
            {
                if (initialized)
                    inflateEnd(&zs);
            }

            bool Gzip::feed(const uint8_t *data, size_t len, std::vector<uint8_t> &out)
            {
                zs.next_in = (Bytef *)data;
                zs.avail_in = len;

                while (zs.avail_in > 0)
                {
                    zs.next_out = outBuf;
                    zs.avail_out = sizeof(outBuf);

                    int ret = inflate(&zs, Z_NO_FLUSH);

                    if (ret != Z_OK && ret != Z_STREAM_END)
                        return false;

                    size_t produced = sizeof(outBuf) - zs.avail_out;
                    out.insert(out.end(), outBuf, outBuf + produced);

                    if (ret == Z_STREAM_END)
                        break;
                }
                return true;
            }

            bool Gzip::decode(const uint8_t *in, size_t inSize, std::vector<uint8_t> &out)
            {
                reset();
                return feed(in, inSize, out);
            }

            void Gzip::reset()
            {
                inflateEnd(&zs);
                std::memset(&zs, 0, sizeof(zs));
                inflateInit2(&zs, 16 + MAX_WBITS);
            }
        } // namespace Codec
    } // namespace Core
} // namespace Wire
