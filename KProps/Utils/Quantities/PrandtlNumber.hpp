//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef PR
     * @brief Defines a named type for Prandtl Number, increasing type safety and expressiveness in fluid dynamics and heat transfer
     * analysis.
     *
     * The PR type wraps a FLOAT (typically a floating-point type such as float or double), and labels it as representing the Prandtl
     * number, a dimensionless number that characterizes the relative thickness of the momentum and thermal boundary layers in fluid flow.
     * It inherits from the Fluent Named Type library traits, enabling arithmetic operations like addition, subtraction, multiplication, and
     * implicit conversion to FLOAT. These features make the PR type both robust and adaptable for use in a wide range of scientific and
     * engineering contexts where the Prandtl number is a key parameter for analyzing heat transfer in fluid flows.
     */
    using PR = strong::type<FLOAT,
                            struct PrandtlNumberTag,
                            strong::regular,
                            strong::equality,
                            strong::arithmetic,
                            strong::iostreamable,
                            strong::implicitly_convertible_to<FLOAT>>;

    using PrandtlNumber = PR;

}    // namespace KProps
