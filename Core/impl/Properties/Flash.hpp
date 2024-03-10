//
// Created by kenne on 08/03/2024.
//

#pragma once

#include "../interfaces/IFluid.hpp"

#include "../Utils/Config.hpp"
#include "../Types/PropertyTypes.hpp"

#include "../Utils/Concepts.hpp"
#include "../Types/MiscTypes.hpp"

#include "FlashResults.hpp"

namespace pcprops {

    template<IsProperty P1, IsProperty P2>
    FlashResults flash(IFluid fluid, P1 p1, P2 p2)
    {
        return FlashResults(fluid, p1, p2);
    }
}
