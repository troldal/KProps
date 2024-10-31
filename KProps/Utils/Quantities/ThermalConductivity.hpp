//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef TC
     * @brief Defines a named type for Thermal Conductivity, increasing type safety and expressiveness in heat transfer analysis.
     *
     * The TC type wraps a FLOAT (commonly a floating-point type such as float or double), and marks it as representing thermal
     * conductivity. It inherits from the Fluent Named Type library traits, enabling arithmetic operations like addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the TC type robust and adaptable for
     * use in a wide range of applications where thermal conductivity is a critical property for analyzing and predicting heat
     * transfer in materials.
     */
    using TC = strong::type<FLOAT,
                            struct ThermalConductivityTag,
                            strong::regular,
                            strong::equality,
                            strong::arithmetic,
                            strong::iostreamable,
                           strong::formattable,
                            strong::implicitly_convertible_to<FLOAT>>;

    using ThermalConductivity = TC;

}    // namespace KProps
