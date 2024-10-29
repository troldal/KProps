//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef A
     * @brief Defines a named type for Helmholtz Energy, enhancing type safety and expressiveness in thermodynamic calculations.
     *
     * The A type encapsulates a FLOAT (commonly a floating-point type such as float or double), and is specifically tagged
     * to represent Helmholtz energy. It inherits from the Fluent Named Type library, gaining useful operations like addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the A type robust and adaptable
     * for a broad spectrum of thermodynamic calculations where Helmholtz energy is a crucial concept, particularly in the
     * analysis of systems in equilibrium at constant temperature and volume.
     */
    using A = strong::type<FLOAT,
                           struct HelmholtzEnergyTag,
                           strong::regular,
                           strong::equality,
                           strong::arithmetic,
                           strong::iostreamable,
                           strong::implicitly_convertible_to<FLOAT>>;

    using HelmholtzEnergy = A;

}    // namespace KProps
