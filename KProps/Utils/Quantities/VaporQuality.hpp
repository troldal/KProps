//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef X
     * @brief Defines a named type for Vapor Quality, increasing type safety and expressiveness in two-phase flow and heat transfer.
     *
     * The X type wraps a FLOAT (typically a floating-point type such as float or double), and marks it as representing vapor quality,
     * the ratio of the mass of vapor to the total mass of the mixture. It inherits from the Fluent Named Type library traits, enabling
     * arithmetic operations such as addition, subtraction, multiplication, and implicit conversion to FLOAT. These features make the X
     * type both robust and adaptable for use in various applications where vapor quality is a critical parameter, including refrigeration,
     * boiling, and condensation processes.
     */
    using X = strong::type<FLOAT,
                           struct VaporQualityTag,
                           strong::regular,
                           strong::equality,
                           strong::arithmetic,
                           strong::iostreamable,
                           strong::implicitly_convertible_to<FLOAT>>;

    using Q            = X;
    using VaporQuality = X;

}    // namespace KProps
