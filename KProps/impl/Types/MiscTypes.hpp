//
// Created by kenne on 29/02/2024.
//

#pragma once

namespace pcprops
{
    struct MolarUnits
    {
    };
    struct MassUnits
    {
    };

    struct Liquid
    {
    };
    struct Gas
    {
    };
    struct Mixture
    {
    };

    enum class Phase
    {
        Liquid,
        Gas,
        TwoPhase,
        Critical,
        Supercritical,
        Unknown
    };

}    // namespace pcprops
