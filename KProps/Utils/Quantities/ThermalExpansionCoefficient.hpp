//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef Alpha
     * @brief Defines a named type for Thermal Expansion, increasing type safety and expressiveness in thermal analysis.
     *
     * The Alpha type wraps a FLOAT (commonly a floating-point type such as float or double), and marks it as representing
     * the coefficient of thermal expansion. It inherits useful operations from the Fluent Named Type library, including
     * addition, subtraction, multiplication, and implicit conversion to FLOAT. These features make Alpha both robust and
     * adaptable for use in a wide range of applications where understanding material behavior in response to temperature
     * changes is critical.
     */
    using Alpha = strong::type<FLOAT,
                               struct AlphaTag,
                               strong::regular,
                               strong::equality,
                               strong::arithmetic,
                               strong::iostreamable,
                           strong::formattable,
                               strong::implicitly_convertible_to<FLOAT>>;

    using ThermalExpansion = Alpha;

}    // namespace KProps
