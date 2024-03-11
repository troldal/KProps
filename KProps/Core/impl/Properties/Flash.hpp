//
// Created by kenne on 08/03/2024.
//

#pragma once

#include <KPropsUtils.hpp>

#include "../Interfaces/IFluid.hpp"

#include "../Utils/Concepts.hpp"

#include "FlashResults.hpp"

namespace pcprops {

    template<IsProperty P1, IsProperty P2>
    FlashResults flash(IFluid fluid, P1 p1, P2 p2)
    {
        return FlashResults(std::move(fluid), p1, p2);
    }
}
