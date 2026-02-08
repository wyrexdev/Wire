#pragma once

#include <iostream>

#include "Core/Response.hpp"
#include "Utils/String.hpp"

#include "Core/Codec/Codec.hpp"
#include "Core/Codec/CodecFactory.hpp"
#include "Core/Codec/CodecType.hpp"

namespace Wire
{
    namespace HTTP
    {
        class Parser
        {
        public:
            static Core::Response parse(const std::string& raw);
        };
    } // namespace HTTP
} // namespace Wire
