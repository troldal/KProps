//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef Z
     * @brief Defines a named type for Compressibility Factor, enhancing type safety and expressiveness in gas behavior calculations.
     *
     * The Z type wraps a FLOAT (typically a floating-point type such as float or double), and marks it as representing the
     * compressibility factor. It inherits from the Fluent Named Type library traits, enabling arithmetic operations like addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the Z type both robust and adaptable for
     * use in a broad range of applications where the compressibility factor is a critical parameter for describing the deviation
     * of real gas behavior from ideal gas law predictions.
     */
    using Z = strong::type<FLOAT,
                           struct CompressibilityFactorTag,
                           strong::regular,
                           strong::equality,
                           strong::arithmetic,
                           strong::iostreamable,
                           strong::implicitly_convertible_to<FLOAT>>;

    using CompressibilityFactor = Z;

}    // namespace KProps