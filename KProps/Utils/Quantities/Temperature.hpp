//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef T
     * @brief Defines a named type for Temperature, providing strong typing and additional functionality.
     *
     * The T type encapsulates a FLOAT (typically a floating-point type such as float or double) and labels
     * it as representing a temperature. It inherits several behaviors from the Fluent Named Type library,
     * including arithmetic operations and implicit conversion to FLOAT, while preserving its distinct identity
     * as a temperature value.
     */
    using T = strong::type<FLOAT,
                           struct TemperatureTag,
                           strong::regular,
                           strong::equality,
                           strong::arithmetic,
                           strong::iostreamable,
                           strong::implicitly_convertible_to<FLOAT>>;

    using Temperature = T;

}    // namespace KProps