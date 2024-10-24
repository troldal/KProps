/*
    888    d8P  8888888b.
    888   d8P   888   Y88b
    888  d8P    888    888
    888d88K     888   d88P 888d888 .d88b.  88888b.  .d8888b
    8888888b    8888888P"  888P"  d88""88b 888 "88b 88K
    888  Y88b   888        888    888  888 888  888 "Y8888b.
    888   Y88b  888        888    Y88..88P 888 d88P      X88
    888    Y88b 888        888     "Y88P"  88888P"   88888P'
                                           888
                                           888
                                           888

    MIT License

    Copyright (c) 2024 Kenneth Troldal Balslev

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

/**
 * @file Flash.hpp
 * @brief This file contains the implementation of the flash function template.
 *
 * This file contains the implementation of the flash function template, which performs a flash calculation on a fluid
 * based on two specified properties. The function template is part of the KProps namespace, which is a collection of
 * functions and classes for performing thermodynamic calculations on fluids.
 */

#pragma once

#include <KPropsUtils.hpp>

#include "../Interfaces/IFluid.hpp"
#include "FlashResults.hpp"

namespace KProps
{

    /**
     * @brief Performs a flash calculation on the fluid with specified properties.
     *
     * @details This function template performs a flash calculation based on two specified properties. A flash calculation
     * determines the equilibrium state (e.g., temperature and pressure) of a fluid when subjected to certain conditions.
     * The function utilizes the given properties (P1 and P2) as inputs for the flash calculation and returns the results
     * in a FlashResults object. This method allows for flexible flash calculations across various fluid models, accepting
     * any two valid properties that define a unique state of the fluid.
     *
     * The template parameter UNITS_T specifies the unit system to be used for the calculation, allowing for results to be
     * returned in either MolarUnits or MassUnits. This adds flexibility in how results are interpreted and used in subsequent
     * calculations or analyses.
     *
     * @tparam UNITS_T The unit system in which the flash calculation results are expressed. Defaults to MolarUnits.
     * @tparam P1 The type of the first property used for the flash calculation, conforming to the IsProperty concept.
     * @tparam P2 The type of the second property used for the flash calculation, also conforming to the IsProperty concept.
     * @requires IsSpecification<P1, P2> - Ensures that the combination of P1 and P2 constitutes a valid specification
     * for performing a flash calculation.
     *
     * @param fluid The fluid on which to perform the flash calculation. It represents the fluid before the state change.
     * @param p1 The first property value, of type P1, used as an input for the flash calculation.
     * @param p2 The second property value, of type P2, used as an input for the flash calculation.
     *
     * @return FlashResults object containing the results of the flash calculation, including any relevant properties
     * of the fluid in the specified units after the equilibrium state is reached.
     *
     * @note The function doesn't actually perform the calculation, but rather initializes a FlashResults object with the
     * given properties. The actual flash calculation is performed when the FlashResults object is used to access the results.
     */
    template<typename UNITS_T = MolarUnits, IsProperty P1, IsProperty P2>
        requires IsSpecification<P1, P2>
    detail::FlashResults flash(IFluid fluid, P1 p1, P2 p2)
    {
        return detail::FlashResults(std::move(fluid), p1, p2, detail::UnitsType<UNITS_T> {});
    }
}    // namespace KProps
