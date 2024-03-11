//
// Created by kenne on 05/02/2024.
//

#pragma once

#include ".utils/Properties.hpp"
#include "FlashResults.hpp"

namespace KSteam
{

    template<typename MODEL_T, typename SPEC1, typename SPEC2>
    requires IsSpecification<SPEC1, SPEC2>
    detail::FlashResults<MODEL_T, SPEC1, SPEC2> flash(SPEC1 p1, SPEC2 p2)
    {
        return detail::FlashResults<MODEL_T, SPEC1, SPEC2>(p1, p2);
    }

    template<typename MODEL_T, typename SPEC1, typename SPEC2>
        requires IsSpecification<SPEC1, SPEC2>
    detail::FlashResults<MODEL_T, SPEC1, SPEC2> flash(double p1, double p2)
    {
        return detail::FlashResults<MODEL_T, SPEC1, SPEC2>(SPEC1 { p1 }, SPEC2 { p2 });
    }
}    // namespace KSteam