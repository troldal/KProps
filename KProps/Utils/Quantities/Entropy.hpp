//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef S
     * @brief Defines a named type for Entropy, enhancing type safety and expressiveness in thermodynamic calculations.
     *
     * The S type encapsulates a FLOAT (commonly a floating-point type such as float or double), designating
     * it as representing entropy. It inherits several behaviors from the Fluent Named Type library, including
     * arithmetic operations like addition, subtraction, and multiplication, along with implicit conversion
     * to FLOAT. These capabilities make the S type both robust and flexible for use in fluid dynamics and
     * thermodynamics, where entropy is a fundamental concept.
     */
    using S = strong::type<FLOAT,
                           struct EntropyTag,
                           strong::regular,
                           strong::equality,
                           strong::arithmetic,
                           strong::iostreamable,
                           strong::implicitly_convertible_to<FLOAT>>;

    using Entropy = S;

}    // namespace KProps