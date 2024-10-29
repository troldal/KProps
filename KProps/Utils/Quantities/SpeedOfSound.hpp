//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef W
     * @brief Defines a named type for Speed of Sound, increasing type safety and expressiveness in acoustics and fluid dynamics.
     *
     * The W type wraps a FLOAT (typically a floating-point type such as float or double), clearly indicating it as representing
     * the speed of sound. It benefits from the Fluent Named Type library traits, enabling arithmetic operations such as addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the W type both robust and adaptable for
     * use in a wide range of applications where the speed of sound is a critical parameter, including acoustics, aerodynamics,
     * and material science.
     */
    using W = strong::type<FLOAT,
                           struct SpeedOfSoundTag,
                           strong::regular,
                           strong::equality,
                           strong::arithmetic,
                           strong::iostreamable,
                           strong::implicitly_convertible_to<FLOAT>>;

    using SpeedOfSound = W;

}    // namespace KProps
