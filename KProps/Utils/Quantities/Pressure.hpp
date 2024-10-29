//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef P
     * @brief Defines a named type for Pressure, enhancing type safety and code clarity.
     *
     * The P type strongly encapsulates a FLOAT (commonly a floating-point type such as float or double),
     * designating it as representing pressure. It inherits from the Fluent Named Type library, enabling
     * arithmetic operations like addition, subtraction, and multiplication, along with implicit conversion
     * to the underlying FLOAT type. These capabilities make the P type both robust and flexible for use
     * in fluid dynamics and thermodynamics calculations, where pressure is a fundamental quantity.
     */
    using P = strong::type<FLOAT,
                           struct PressureTag,
                           strong::regular,
                           strong::equality,
                           strong::arithmetic,
                           strong::iostreamable,
                           strong::implicitly_convertible_to<FLOAT>>;

    using Pressure = P;

}    // namespace KProps