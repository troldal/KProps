//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef Cp
     * @brief Defines a named type for Specific Heat Capacity at Constant Pressure, increasing type safety and expressiveness.
     *
     * The Cp type wraps a FLOAT (typically a floating-point type such as float or double), explicitly marking it as representing
     * specific heat capacity at constant pressure. It inherits useful operations from the Fluent Named Type library, such as
     * addition, subtraction, multiplication, and implicit conversion to FLOAT. These features make the Cp type robust and
     * adaptable for use in various scientific and engineering contexts where specific heat capacity is a key property.
     */
    using Cp = strong::type<FLOAT,
                            struct CpTag,
                            strong::regular,
                            strong::equality,
                            strong::arithmetic,
                            strong::iostreamable,
                           strong::formattable,
                            strong::implicitly_convertible_to<FLOAT>>;

    using IsobaricHeatCapacity = Cp;

}    // namespace KProps
