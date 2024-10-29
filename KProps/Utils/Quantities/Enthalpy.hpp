//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef H
     * @brief Defines a named type for Enthalpy, incorporating additional functionality for thermodynamic calculations.
     *
     * The `H` type encapsulates a FLOAT (usually a floating-point type such as float or double), explicitly
     * representing enthalpy. It inherits from the Fluent Named Type library, which provides useful operations
     * like addition, subtraction, multiplication, and implicit conversion to the base FLOAT type. These
     * capabilities make the `H` type well-suited for use in a wide range of thermodynamic calculations, where
     * enthalpy is a key quantity.
     */
    using H = strong::type<FLOAT,
                           struct EnthalpyTag,
                           strong::regular,
                           strong::equality,
                           strong::arithmetic,
                           strong::iostreamable,
                           strong::implicitly_convertible_to<FLOAT>>;

    using Enthalpy = H;

}    // namespace KProps