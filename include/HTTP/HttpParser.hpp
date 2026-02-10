#pragma once
#include <string>
#include <unordered_map>
#include <optional>

#include "Core/Response.hpp"

namespace Wire::HTTP
{
    class Parser
    {
    public:
        static Core::Response parse(const std::string& raw);
    };
}
