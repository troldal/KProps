//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef U
     * @brief Defines a named type for Internal Energy, enhancing type safety and code expressiveness.
     *
     * The U type encapsulates a FLOAT (typically a floating-point type such as float or double), and labels
     * it as representing internal energy. It inherits from the Fluent Named Type library, which adds useful
     * operations like addition, subtraction, multiplication, and implicit conversion to FLOAT. These capabilities
     * make the U type robust and adaptable for use across a wide range of thermodynamic calculations and fluid dynamics
     * scenarios where internal energy is a key concept.
     */
    using U = strong::type<FLOAT,
                           struct InternalEnergyTag,
                           strong::regular,
                           strong::equality,
                           strong::arithmetic,
                           strong::iostreamable,
                           strong::implicitly_convertible_to<FLOAT>>;

    using InternalEnergy = U;

}    // namespace KProps