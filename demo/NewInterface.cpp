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
#include <numbers>
#include <string>
#include <variant>

using namespace sciplot;
namespace rng = std::ranges;

namespace pc = pcprops;

struct MyProps
{
    pc::Cp  cp { 0.0 };
    pc::Cv  cv { 0.0 };
    pc::P   p { 0.0 };
    pc::T   t { 0.0 };
    pc::V   v { 0.0 };
    pc::Rho rho { 0.0 };
    pc::H   h { 0.0 };
    pc::S   s { 0.0 };
    pc::U   u { 0.0 };
};

void printHeader()
{
    auto printLine = [](size_t colCount) {
        for (int i = 0; i < (colCount * 15 + (colCount - 1) * 3); ++i) std::cout << "-";
        std::cout << std::endl;
    };

    printLine(8);
    std::cout << std::format("{:>15} | {:>15} | {:>15} | {:>15} | {:>15} | {:>15} | {:>15} | {:>15} ",
                             "SPEC",
                             "P [bar]",
                             "T [C]",
                             "V [m3/kg]",
                             "RHO [kg/m3]",
                             "H [J/kg]",
                             "S [J/kg-K]",
                             "U [J/kg]")
              << std::endl;
    printLine(8);
}

void printProps(const MyProps& props, const std::string& spec)
{
    std::cout << std::format("{:15} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} ",
                             spec,
                             props.p.get() / 1.0e+05,
                             props.t.get(),
                             props.v.get(),
                             props.rho.get(),
                             props.h.get(),
                             props.s.get(),
                             props.u.get())
              << std::endl;
}

int main()
{
    using namespace pcprops;
    std::cout << std::fixed << std::setprecision(20);

    auto water = FluidWrapper(HEOS("Water"));
    // water.setState(P { 101325.0 }, T { 298.15 });

    auto results     = flash(water, P { 101325.0 }, T { 298.15 });
    auto propsStatic = results.properties<Cp, Cv, P, T, V, Rho, H, S, U>().get<MyProps, MassUnits>();

    std::cout << "Cp        : " << propsStatic.cp << std::endl;
    std::cout << "Cv        : " << propsStatic.cv << std::endl;
    std::cout << "P         : " << propsStatic.p << std::endl;
    std::cout << "T         : " << propsStatic.t << std::endl;
    std::cout << "V         : " << propsStatic.v << std::endl;
    std::cout << "Rho       : " << propsStatic.rho << std::endl;
    std::cout << "H         : " << propsStatic.h << std::endl;
    std::cout << "S         : " << propsStatic.s << std::endl;
    std::cout << "U         : " << propsStatic.u << std::endl;

    std::cout << std::endl;

    auto propsDynamic =
        results
            .properties(
                { Property::Cp, Property::Cv, Property::P, Property::T, Property::V, Property::Rho, Property::H, Property::S, Property::U })
            .get<std::deque, MassUnits>();

    std::cout << "Cp        : " << propsDynamic[0] << std::endl;
    std::cout << "Cv        : " << propsDynamic[1] << std::endl;
    std::cout << "P         : " << propsDynamic[2] << std::endl;
    std::cout << "T         : " << propsDynamic[3] << std::endl;
    std::cout << "V         : " << propsDynamic[4] << std::endl;
    std::cout << "Rho       : " << propsDynamic[5] << std::endl;
    std::cout << "H         : " << propsDynamic[6] << std::endl;
    std::cout << "S         : " << propsDynamic[7] << std::endl;
    std::cout << "U         : " << propsDynamic[8] << std::endl;

    std::cout << std::endl;

    auto propsString = results.properties({ "Cp", "Cv", "P", "T", "V", "Rho", "H", "S", "U" }).get<std::deque, MassUnits>();

    std::cout << "Cp        : " << propsString[0] << std::endl;
    std::cout << "Cv        : " << propsString[1] << std::endl;
    std::cout << "P         : " << propsString[2] << std::endl;
    std::cout << "T         : " << propsString[3] << std::endl;
    std::cout << "V         : " << propsString[4] << std::endl;
    std::cout << "Rho       : " << propsString[5] << std::endl;
    std::cout << "H         : " << propsString[6] << std::endl;
    std::cout << "S         : " << propsString[7] << std::endl;
    std::cout << "U         : " << propsString[8] << std::endl;

    return EXIT_SUCCESS;
}
