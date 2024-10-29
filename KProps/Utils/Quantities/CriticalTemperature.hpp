//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <strong_type/strong_type.hpp>

namespace KProps
{

    using TCrit = strong::type<FLOAT,
                       struct TCritTag,
                       strong::regular,
                       strong::equality,
                       strong::arithmetic,
                       strong::iostreamable,
                       strong::implicitly_convertible_to<FLOAT>>;

}    // namespace KProps