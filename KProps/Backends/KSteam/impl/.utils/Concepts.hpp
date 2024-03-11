//
// Created by kenne on 05/02/2024.
//

#pragma once

#include <tuple>

namespace KSteam::detail {

    // Concept to check for tuple-like types
    template<typename T>
    concept IsTuple = requires { typename std::tuple_size<T>::type; };

    // Concept to check for homogeneous containers (like std::vector)
    template<typename T>
    concept IsContainer = requires(T t) {
        typename T::value_type;
        { t.emplace_back(std::declval<typename T::value_type>()) };
    };

}
