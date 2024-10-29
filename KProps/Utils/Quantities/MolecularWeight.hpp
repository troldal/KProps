//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef MW
     * @brief Defines a named type for Molar Weight, providing strong typing and additional functionality.
     *
     * The MW type encapsulates a FLOAT (typically a floating-point type like float or double) and associates
     * it with the concept of molar weight. It inherits behaviors from the Fluent Named Type library, including
     * arithmetic operations and implicit conversion to the underlying FLOAT type, while maintaining the
     * semantic distinction from other floating-point quantities.
     */
    using MW = strong::type<FLOAT,
                            struct MolarWeightTag,
                            strong::regular,
                            strong::equality,
                            strong::arithmetic,
                            strong::iostreamable,
                            strong::implicitly_convertible_to<FLOAT>>;

    using MolecularWeight = MW;
    using MolarMass       = MW;

}    // namespace KProps