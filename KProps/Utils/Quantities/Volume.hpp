//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef V
     * @brief Defines a named type for Volume, increasing type safety and expressiveness in volume calculations.
     *
     * The V type encapsulates a FLOAT (commonly a floating-point type such as float or double), specifically
     * labeling it as representing volume. It benefits from the Fluent Named Type library traits, enabling
     * arithmetic operations such as addition, subtraction, multiplication, and implicit conversion to FLOAT.
     * These features make the V type both robust and flexible for use in a wide array of applications where
     * volume is a critical property.
     */
    using V = strong::type<FLOAT,
                           struct VolumeTag,
                           strong::regular,
                           strong::equality,
                           strong::arithmetic,
                           strong::iostreamable,
                           strong::implicitly_convertible_to<FLOAT>>;

    using Volume = V;
    using Vol    = V;

}    // namespace KProps
