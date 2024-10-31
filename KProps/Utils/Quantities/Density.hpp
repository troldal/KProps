//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    /**
     * @typedef Rho
     * @brief Defines a named type for Density, enhancing type safety and expressiveness in calculations involving mass and volume.
     *
     * The Rho type wraps a FLOAT (typically a floating-point type like float or double), explicitly marking it as representing
     * density. It inherits useful operations from the Fluent Named Type library, such as addition, subtraction, multiplication,
     * and implicit conversion to FLOAT. These capabilities make the Rho type robust and versatile for use in various scientific
     * and engineering contexts where density is a key property.
     */
  using Rho = strong::type<FLOAT,
                     struct DensityTag,
                     strong::regular,
                     strong::equality,
                     strong::arithmetic,
                     strong::iostreamable,
                           strong::formattable,
                     strong::implicitly_convertible_to<FLOAT>>;

    using Density = Rho;

}    // namespace KProps