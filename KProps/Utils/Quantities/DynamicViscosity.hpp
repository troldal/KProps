//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef Eta
     * @brief Defines a named type for Dynamic Viscosity, increasing type safety and expressiveness in fluid dynamics calculations.
     *
     * The Eta type wraps a FLOAT (typically a floating-point type such as float or double), and labels it as representing dynamic
     * viscosity. It inherits from the Fluent Named Type library traits, enabling arithmetic operations like addition, subtraction,
     * multiplication, and implicit conversion to FLOAT. These features make the Eta type both robust and versatile for use in various
     * scientific and engineering contexts where dynamic viscosity is a crucial fluid property for characterizing flow behavior and
     * resistance.
     */
  using Eta = strong::type<FLOAT,
                     struct DynamicViscosityTag,
                     strong::regular,
                     strong::equality,
                     strong::arithmetic,
                     strong::iostreamable,
                     strong::implicitly_convertible_to<FLOAT>>;

    using DynamicViscosity = Eta;

}    // namespace KProps