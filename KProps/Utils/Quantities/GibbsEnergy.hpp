//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef G
     * @brief Defines a named type for Gibbs Energy, enriching type safety and expressiveness in thermodynamic and chemical calculations.
     *
     * The G type strongly encapsulates a FLOAT (typically a floating-point type such as float or double), designating it
     * as representing Gibbs energy. It benefits from the Fluent Named Type library traits, enabling operations like addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the G type both robust and flexible
     * for use across various scenarios in thermodynamics and chemical thermodynamics, where Gibbs energy plays a pivotal role
     * in determining the spontaneity of reactions and the equilibrium of phases.
     */
    using G = strong::type<FLOAT,
                           struct GibbsEnergyTag,
                           strong::regular,
                           strong::equality,
                           strong::arithmetic,
                           strong::iostreamable,
                           strong::formattable,
                           strong::implicitly_convertible_to<FLOAT>>;

    using GibbsEnergy = G;

}    // namespace KProps
