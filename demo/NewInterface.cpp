//
// Created by kenne on 31/01/2024.
//

#include "_external.hpp"

#include <HEOS.hpp>
#include <IF97.hpp>
#include <KProps.hpp>

#include <deque>
#include <format>
#include <iomanip>
#include <iostream>

namespace kp = KProps;

struct MyProps
{
    kp::Cp    cp { 0.0 };
    kp::Cv    cv { 0.0 };
    kp::P     p { 0.0 };
    kp::T     t { 0.0 };
    kp::V     v { 0.0 };
    kp::Rho   rho { 0.0 };
    kp::H     h { 0.0 };
    kp::S     s { 0.0 };
    kp::U     u { 0.0 };
    kp::X     x { 0.0 };
    kp::Phase phase { kp::Phase::Unknown };
};

void printProperty(kp::Property prop)
{
    auto propName = prop.type<std::string>();
    std::cout << propName;
    for (size_t i = 0; i < 10 - propName.size(); ++i) std::cout << " ";
    std::cout << ": " << prop << std::endl;
}

int main()
{
    using namespace KProps;
    std::cout << std::fixed << std::setprecision(20);

    auto water = FluidWrapper(HEOS("Water"));
    water.setState(P { 101325.0 }, T { 298.15 });

    auto propsStatic = properties<Cp, Cv, P, T, V, Rho, H, S, U, X, Phase>(water).get<MyProps, MassUnits>();

    auto val = property(water, "H");

    // auto results     = flash(water, P { 101325.0 }, T { 298.15 });
    // auto results     = flash(water, P { 101325.0 }, X { 0.5 });
    // auto results = flash(water, P { 101325.0 * 250 }, T { 700.0 });
    // auto results     = flash(water, P { 101325.0 }, T { 398.15 });
    // auto propsStatic = results.properties<Cp, Cv, P, T, V, Rho, H, S, U, X, Phase>().get<MyProps, MassUnits>();


    std::cout << "Cp        : " << propsStatic.cp << std::endl;
    std::cout << "Cv        : " << propsStatic.cv << std::endl;
    std::cout << "P         : " << propsStatic.p << std::endl;
    std::cout << "T         : " << propsStatic.t << std::endl;
    std::cout << "V         : " << propsStatic.v << std::endl;
    std::cout << "Rho       : " << propsStatic.rho << std::endl;
    std::cout << "H         : " << propsStatic.h << std::endl;
    std::cout << "S         : " << propsStatic.s << std::endl;
    std::cout << "U         : " << propsStatic.u << std::endl;
    std::cout << "X         : " << propsStatic.x << std::endl;
    std::cout << "Phase     : " << propsStatic.phase << std::endl;

    std::cout << std::endl;

    //auto propsStaticDeque = results.properties<Cp, Cv, P, T, V, Rho, H, S, U, X, Phase>().get<std::deque, MassUnits>();
    auto propsStaticDeque = properties<Cp, Cv, P, T, V, Rho, H, S, U, X, Phase>(water).get<std::deque, MassUnits>();
    for (auto prop : propsStaticDeque) printProperty(prop);
    std::cout << std::endl;

    using Type = Property::Type;
    // auto propsDynamic =
    //     results.properties({ Type::Cp, Type::Cv, Type::P, Type::T, Type::V, Type::Rho, Type::H, Type::S, Type::U, Type::X, Type::Phase, Type::Undefined })
    //         .get<std::deque, MassUnits>();
    auto propsDynamic =
    properties(water, { Type::Cp, Type::Cv, Type::P, Type::T, Type::V, Type::Rho, Type::H, Type::S, Type::U, Type::X, Type::Phase })
        .get<std::deque, MassUnits>();
    for (auto prop : propsDynamic) printProperty(prop);
    std::cout << std::endl;

    //auto propsString = results.properties({ "Cp", "Cv", "P", "T", "V", "Rho", "H", "S", "U", "X", "PHASE", "UNDEFINED" }).get<std::deque, MassUnits>();
    auto propsString = properties(water, { "Cp", "Cv", "P", "T", "V", "Rho", "H", "S", "U", "X", "PHASE" }).get<std::deque, MassUnits>();
    for (auto prop : propsString) printProperty(prop);
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
