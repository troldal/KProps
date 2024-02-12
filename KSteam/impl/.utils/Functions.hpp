//
// Created by kenne on 05/02/2024.
//

#pragma once

#include <tuple>

namespace KSteam::detail {

    /**
     * @brief Helper function to unpack a tuple and initialize a struct.
     *
     * This function template unpacks the elements of a tuple and uses them to initialize
     * a struct of type Struct.
     *
     * @tparam Struct The struct type to be initialized.
     * @tparam Tuple The tuple type from which the struct is initialized.
     * @tparam I Indices of the tuple elements.
     * @param tuple Tuple containing the values for struct initialization.
     * @return Struct An instance of Struct initialized with values from the tuple.
     */
    template<typename Struct, typename Tuple, std::size_t... I>
    Struct tupleToStructImpl(Tuple&& tuple, std::index_sequence<I...>)
    {
        return Struct { std::get<I>(std::forward<Tuple>(tuple))... };
    }

    /**
     * @brief Public function to convert a tuple to a struct.
     *
     * This function template provides a convenient way to convert a tuple into
     * a struct of type Struct.
     *
     * @tparam Struct The struct type to be initialized.
     * @tparam Tuple The tuple type from which the struct is initialized.
     * @param tuple Tuple containing the values for struct initialization.
     * @return Struct An instance of Struct initialized with values from the tuple.
     */
    template<typename Struct, typename Tuple>
    Struct tupleToStruct(Tuple&& tuple)
    {
        return tupleToStructImpl<Struct>(std::forward<Tuple>(tuple),
                                         std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>> {});
    }
}