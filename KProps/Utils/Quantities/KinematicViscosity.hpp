//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef Nu
     * @brief Defines a named type for Kinematic Viscosity, increasing type safety and expressiveness in fluid dynamics.
     *
     * The Nu type wraps a FLOAT (typically a floating-point type such as float or double), and labels it as representing
     * kinematic viscosity. It benefits from the Fluent Named Type library traits, enabling arithmetic operations like
     * addition, subtraction, multiplication, and implicit conversion to FLOAT. These features make the Nu type both
     * robust and adaptable for use in a wide range of scientific and engineering contexts where kinematic viscosity is
     * a key parameter for describing the ratio of dynamic viscosity to fluid density, affecting flow and diffusion.
     */
    using Nu = strong::type<FLOAT,
                            struct KinematicViscosityTag,
                            strong::regular,
                            strong::equality,
                            strong::arithmetic,
                            strong::iostreamable,
                            strong::implicitly_convertible_to<FLOAT>>;

    using KinematicViscosity = Nu;

}    // namespace KProps
