//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <ranges>
#include <string>
#include <troldal/StringEnum.hpp>

namespace KProps
{
    class Phase : public troldal::StringEnum<Phase, "LIQUID", "GAS", "TWOPHASE", "CRITICAL", "SUPERCRITICAL", "UNKNOWN">
    {
    public:
        using BASE = troldal::StringEnum<Phase, "LIQUID", "GAS", "TWOPHASE", "CRITICAL", "SUPERCRITICAL", "UNKNOWN">;

        // Conversion constructor to implicitly convert StringEnum<Phase> to Phase
        constexpr Phase(const BASE& base) : BASE(base) {}

        // Static constexpr instances
        static constexpr BASE Liquid        = BASE::Create("LIQUID").value();
        static constexpr BASE Gas           = BASE::Create("GAS").value();
        static constexpr BASE TwoPhase      = BASE::Create("TWOPHASE").value();
        static constexpr BASE Critical      = BASE::Create("CRITICAL").value();
        static constexpr BASE Supercritical = BASE::Create("SUPERCRITICAL").value();
        static constexpr BASE Unknown       = BASE::Create("UNKNOWN").value();

    private:
        using BASE::BASE;
    };
}    // namespace KProps