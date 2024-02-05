//
// Created by kenne on 01/02/2024.
//

#pragma once

#include "Properties.hpp"
#include "PropertyProxy.hpp"

namespace KSteam
{


    template<typename SPEC1, typename SPEC2>
        requires IsSpecification<SPEC1, SPEC2>
    detail::FlashResults<SPEC1, SPEC2> flash(SPEC1 p1, SPEC2 p2)
    {
        return detail::FlashResults(p1, p2);
    }

    template<typename SPEC1, typename SPEC2>
        requires IsSpecification<SPEC1, SPEC2>
    detail::FlashResults<SPEC1, SPEC2> flash(double p1, double p2)
    {
        return detail::FlashResults(SPEC1 { p1 }, SPEC2 { p2 });
    }

}    // namespace KSteam
