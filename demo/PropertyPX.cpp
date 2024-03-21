//
// Created by kenne on 31/01/2024.
//

#include "_external.hpp"

#include <format>
#include <iostream>
#include <ranges>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

#include <KProps.hpp>
#include <HEOS.hpp>

#include "AbstractState.h"
#include <iomanip>
#include <iostream>
#include <memory>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <ranges>

using namespace sciplot;
namespace rng = std::ranges;

namespace kp = KProps;

struct MyProps
{
    kp::P   p { 0.0 };
    kp::T   t { 0.0 };
    kp::X   x { 0.0 };
    kp::V   v { 0.0 };
    kp::Rho rho { 0.0 };
    kp::H   h { 0.0 };
    kp::S   s { 0.0 };
    kp::U   u { 0.0 };
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
                             "T [K]",
                             "X [-]",
                             "Rho [kg/m3]",
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
                             props.x.get(),
                             props.rho.get(),
                             props.h.get(),
                             props.s.get(),
                             props.u.get())
              << std::endl;
}

template<typename T1, typename T2>
void computeProps(auto& fluid, MyProps& props, const T1& prop1, const T2& prop2, const std::string& spec)
{
    using namespace KProps;

    std::cout << std::fixed << std::setprecision(20);

    try {
        auto results = flash<MassUnits>(fluid, prop1, prop2);
        // fluid.setState(prop1, prop2);
        //auto p     = property<P>(fluid);
        //auto x     = property<X>(fluid);
        //bool print = false;

        // if (abs(1.0 - p.get() / props.p.get()) > 1e-3) {
        //     print = true;
        //     std::cout << "P: " << p.get() << " != " << props.p.get() << std::endl;
        // }
        //
        // if (abs(x.get() - props.x.get()) > 1e-3) {
        //     print = true;
        //     std::cout << "X: " << x.get() << " != " << props.x.get() << std::endl;
        // }

        // auto tmp = properties<P, T, X, V, Rho, H, S, U>(fluid).template get<MassUnits>();
        props = results.template properties<P, T, X, V, Rho, H, S, U>().template get<MyProps, MassUnits>();
        // if (print) {
        //     printHeader();
            printProps(props, spec);
        // }
    }
    catch (...) {
        std::cout << "Error computing " << spec << " at:" << prop1 << " and " << prop2 << std::endl;
    }
}

int main()
{
    using namespace KProps;

    std::cout << std::fixed << std::setprecision(20);

    MyProps props;
    auto    water = FluidWrapper(HEOS("Water"));

    // printHeader();
    // water.setState(P { 0.01 * 100000.0 }, X { 0.0 });
    // props = properties<P, T, X, V, Rho, H, S, U>(water).get<MyProps>();
    // printProps(props, "PX");
    //
    // water.setState(props.rho, props.u);
    // props = properties<P, T, X, V, Rho, H, S, U>(water).get<MyProps>();
    // printProps(props, "DU");

    io::CSVReader<9, io::trim_chars<' ', '\t'>, io::no_quote_escape<';'>> in("C:/Users/kenne/Desktop/IAPWS95Sat.csv");
    in.read_header(io::ignore_extra_column, "T", "P", "X", "Rho", "H", "S", "Cv", "Cp", "W");
    double p, t, x, rho, h, s, cv, cp, w;

    while (in.read_row(t, p, x, rho, h, s, cv, cp, w)) {
        props.p   = P { p < water.min<P>() ? water.min<P>() : p };
        props.t   = T { t };
        props.x   = X { x };
        props.v   = V { 1.0 / rho };
        props.h   = H { h };
        props.s   = S { s };
        props.rho = Rho { rho };
        props.u   = U { 0.0 };

        printHeader();
        printProps(props, "Table");

        computeProps(water, props, props.p, X { x }, "PX");
        computeProps(water, props, props.p, props.h, "PH");
        computeProps(water, props, props.p, props.s, "PS");
        //computeProps(water, props, props.p, props.u, "PU");
        computeProps(water, props, props.rho, props.t, "DT");
        //computeProps(water, props, props.rho, props.u, "DU");
        // computeProps(water, props, props.h, props.s, "HS");
        //computeProps(water, props, props.rho, props.h, "DH");
        //computeProps(water, props, props.rho, props.s, "DS");
        //computeProps(water, props, props.t, props.s, "TS");
        computeProps(water, props, props.p, props.rho, "DP");
    }

    return 0;
}
