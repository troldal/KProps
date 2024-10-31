//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    using Undefined = strong::type<FLOAT,
                                   struct UndefinedTag,
                                   strong::regular,
                                   strong::equality,
                                   strong::arithmetic,
                                   strong::iostreamable,
                           strong::formattable,
                                   strong::implicitly_convertible_to<FLOAT>>;

}    // namespace KProps
