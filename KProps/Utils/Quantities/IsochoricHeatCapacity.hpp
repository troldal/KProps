//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef Cv
     * @brief Defines a named type for Specific Heat Capacity at Constant Volume, enhancing type safety and code expressiveness.
     *
     * The Cv type wraps a FLOAT (usually a floating-point type such as float or double), and marks it as representing specific
     * heat capacity at constant volume. It inherits various operations from the Fluent Named Type library, including addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These functionalities make the Cv type both robust and
     * versatile for use in a wide range of scientific and engineering applications where specific heat capacity is a crucial property.
     */
    using Cv = strong::type<FLOAT,
                            struct CvTag,
                            strong::regular,
                            strong::equality,
                            strong::arithmetic,
                            strong::iostreamable,
                           strong::formattable,
                            strong::implicitly_convertible_to<FLOAT>>;

    using IsochoricHeatCapacity = Cv;

}    // namespace KProps
