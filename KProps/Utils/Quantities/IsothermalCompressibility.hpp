//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef Kappa
     * @brief Defines a named type for Isothermal Compressibility, increasing type safety and expressiveness in material and fluid
     * calculations.
     *
     * The Kappa type wraps a FLOAT (typically a floating-point type such as float or double), explicitly marking it as representing
     * isothermal compressibility. It benefits from the Fluent Named Type library traits, enabling arithmetic operations like addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the Kappa type both robust and versatile for use
     * in various scientific and engineering contexts where isothermal compressibility is a key property in understanding material and fluid
     * behavior under pressure changes.
     */
    using Kappa = strong::type<FLOAT,
                               struct KappaTag,
                               strong::regular,
                               strong::equality,
                               strong::arithmetic,
                               strong::iostreamable,
                               strong::implicitly_convertible_to<FLOAT>>;

    using IsothermalCompressibility = Kappa;

}    // namespace KProps
