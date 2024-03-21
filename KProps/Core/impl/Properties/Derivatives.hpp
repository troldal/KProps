//
// Created by kenne on 18/02/2024.
//

#pragma once

#include <KPropsUtils.hpp>

#include "../Interfaces/IFluid.hpp"

#include <Deriv.hpp>

namespace KProps
{

    template<typename T>
    struct Of
    {
        using type = T;
    };

    template<typename...>
    struct Wrt
    {
    };

    template<typename T>
    struct Wrt<T>
    {
        using type = T;
    };

    template<typename T, typename U>
    struct Wrt<T, U>
    {
        using type1 = T;
        using type2 = U;
    };

    template<typename T>
    struct AtConst
    {
        using type = T;
    };

    /**
     * @brief Calculates the derivative of a property with respect to another property at a constant property.
     *
     * This function calculates the derivative of a property (OF_T) with respect to another property (WRT_T) at a constant property
     * (CONST_T). The derivative is calculated using the Order1CentralRichardson method from the nxx::deriv namespace.
     *
     * @tparam OF_T The type of the property the derivative is calculated of.
     * @tparam WRT_T The type of the property the derivative is calculated with respect to.
     * @tparam CONST_T The type of the property that is held constant.
     *
     * @param model The model object.
     * @param of The property the derivative is calculated of.
     * @param wrt The property the derivative is calculated with respect to.
     * @param atConst The property that is held constant.
     * @return The calculated derivative as a FLOAT.
     */
    template<IsProperty OF_T, IsProperty WRT_T, IsProperty CONST_T>
    auto derivative(IFluid model, Of<OF_T> of, Wrt<WRT_T> wrt, AtConst<CONST_T> atConst)
    {
        using namespace nxx::deriv;

        auto constant = model.property<CONST_T>();

        auto func = [&](double x) {
            model.setState(WRT_T { x }, constant);
            return model.property<OF_T>().get();
        };

        return *diff<Order1CentralRichardson>(func, model.property<WRT_T>().get());
    }

    /**
     * @brief Calculates the derivative of a property with respect to another property at a constant property using the Order2Central5Point
     * method.
     *
     * This function calculates the derivative of a property (OF_T) with respect to another property (WRT_T) at a constant property
     * (CONST_T). The derivative is calculated using the Order2Central5Point method from the nxx::deriv namespace.
     *
     * @tparam OF_T The type of the property the derivative is calculated of.
     * @tparam WRT_T The type of the property the derivative is calculated with respect to.
     * @tparam CONST_T The type of the property that is held constant.
     *
     * @param model The model object.
     * @param of The property the derivative is calculated of.
     * @param wrt The property the derivative is calculated with respect to.
     * @param atConst The property that is held constant.
     * @return The calculated derivative as a FLOAT.
     */
    template<IsProperty OF_T, IsProperty WRT_T, IsProperty CONST_T>
    auto derivative(IFluid model, Of<OF_T> of, Wrt<WRT_T, WRT_T> wrt, AtConst<CONST_T> atConst)
    {
        using namespace nxx::deriv;

        auto constant = model.property<CONST_T>();

        auto func = [&](double x) {
            model.setState(WRT_T { x }, constant);
            return model.property<OF_T>().get();
        };

        return *diff<Order2Central5Point>(func, model.property<WRT_T>().get());
    }

    /**
     * @brief Calculates the derivative of a property with respect to two different properties.
     *
     * This function calculates the derivative of a property (OF_T) with respect to two different properties (WRT1_T and WRT2_T).
     * The derivative is calculated using the mdiff method from the nxx::deriv namespace.
     *
     * @tparam OF_T The type of the property the derivative is calculated of.
     * @tparam WRT1_T The first type of the property the derivative is calculated with respect to.
     * @tparam WRT2_T The second type of the property the derivative is calculated with respect to.
     *
     * @param model The model object.
     * @param of The property the derivative is calculated of.
     * @param wrt The properties the derivative is calculated with respect to.
     * @return The calculated derivative as a FLOAT.
     */
    template<IsProperty OF_T, IsProperty WRT1_T, IsProperty WRT2_T>
        requires(!std::same_as<WRT1_T, WRT2_T>)
    auto derivative(IFluid model, Of<OF_T> of, Wrt<WRT1_T, WRT2_T> wrt)
    {
        using namespace nxx::deriv;

        auto func = [&](std::pair<double, double> point) {
            model.setState(WRT1_T { point.first }, WRT2_T { point.second });
            return model.property<OF_T>().get();
        };

        return mdiff(func, std::make_pair(model.property<WRT1_T>().get(), model.property<WRT2_T>().get()));
    }

    /**
     * @brief Calculates the derivative of a property with respect to another property at a constant property.
     *
     * This function calculates the derivative of a property (OF_T) with respect to another property (WRT_T) at a constant property
     * (CONST_T). The derivative is calculated using the appropriate derivative function based on the types of the properties.
     *
     * @tparam OF_T The type of the property the derivative is calculated of.
     * @tparam WRT_T The type of the property the derivative is calculated with respect to.
     * @tparam CONST_T The type of the property that is held constant.
     *
     * @param model The model object.
     * @return The calculated derivative as a FLOAT.
     */
    template<typename OF_T, typename WRT_T, typename CONST_T>
        requires std::same_as<OF_T, Of<typename OF_T::type>> && std::same_as<WRT_T, Wrt<typename WRT_T::type>> &&
                 std::same_as<CONST_T, AtConst<typename CONST_T::type>> && IsProperty<typename OF_T::type> &&
                 IsProperty<typename WRT_T::type> && IsProperty<typename CONST_T::type>
    auto derivative(IFluid model)
    {
        return derivative(model, OF_T(), WRT_T(), CONST_T());
    }

    /**
     * @brief Calculates the derivative of a property with respect to two different properties at a constant property.
     *
     * This function calculates the derivative of a property (OF_T) with respect to two different properties (WRT_T::type1 and WRT_T::type2)
     * at a constant property (CONST_T). The derivative is calculated using the appropriate derivative function based on the types of the
     * properties.
     *
     * @tparam OF_T The type of the property the derivative is calculated of.
     * @tparam WRT_T The types of the properties the derivative is calculated with respect to.
     * @tparam CONST_T The type of the property that is held constant.
     *
     * @param model The model object.
     * @return The calculated derivative as a FLOAT.
     */
    template<typename OF_T, typename WRT_T, typename CONST_T>
        requires std::same_as<OF_T, Of<typename OF_T::type>> && std::same_as<WRT_T, Wrt<typename WRT_T::type1, typename WRT_T::type2>> &&
                 std::same_as<CONST_T, AtConst<typename CONST_T::type>> && IsProperty<typename OF_T::type> &&
                 IsProperty<typename WRT_T::type1> && IsProperty<typename WRT_T::type2> && IsProperty<typename CONST_T::type> &&
                 std::same_as<typename WRT_T::type1, typename WRT_T::type2>
    auto derivative(IFluid model)
    {
        return derivative(model, OF_T(), WRT_T(), CONST_T());
    }

    /**
     * @brief Calculates the derivative of a property with respect to two different properties.
     *
     * This function calculates the derivative of a property (OF_T) with respect to two different properties (WRT_T::type1 and
     * WRT_T::type2). The derivative is calculated using the appropriate derivative function based on the types of the properties.
     *
     * @tparam OF_T The type of the property the derivative is calculated of.
     * @tparam WRT_T The types of the properties the derivative is calculated with respect to.
     *
     * @param model The model object.
     * @return The calculated derivative as a FLOAT.
     */
    template<typename OF_T, typename WRT_T>
        requires std::same_as<OF_T, Of<typename OF_T::type>> && std::same_as<WRT_T, Wrt<typename WRT_T::type1, typename WRT_T::type2>> &&
                 IsProperty<typename OF_T::type> && IsProperty<typename WRT_T::type1> && IsProperty<typename WRT_T::type2> &&
                 (!std::same_as<typename WRT_T::type1, typename WRT_T::type2>)
    auto derivative(IFluid model)
    {
        return derivative(model, OF_T(), WRT_T());
    }

    inline FLOAT derivative(const IFluid& model, Of<A>, Wrt<V>, AtConst<T>)
    {
        return -model.property<P>();
    }

    inline FLOAT derivative(const IFluid& model, Of<A>, Wrt<T>, AtConst<V>)
    {
        return -model.property<S>();
    }

//    inline FLOAT derivative(const IFluid& model, Of<U>, Wrt<T>, AtConst<V>)
//    {
//        return model.property<Cv>();
//    }

    inline FLOAT derivative(const IFluid& model, Of<S>, Wrt<T>, AtConst<V>)
    {
        return model.property<Cv>() / model.property<T>();
    }

//    inline FLOAT derivative(const IFluid& model, Of<H>, Wrt<T>, AtConst<P>)
//    {
//        return model.property<Cp>();
//    }

    inline FLOAT derivative(const IFluid& model, Of<S>, Wrt<T>, AtConst<P>)
    {
        return model.property<Cp>() / model.property<T>();
    }

    inline FLOAT derivative(const IFluid& model, Of<G>, Wrt<P>, AtConst<T>)
    {
        return model.property<V>();
    }

    inline FLOAT derivative(const IFluid& model, Of<G>, Wrt<T>, AtConst<P>)
    {
        return -model.property<S>();
    }

}    // namespace pcprops