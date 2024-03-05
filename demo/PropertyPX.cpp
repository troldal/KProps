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
#include <KSteam.hpp>

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

namespace ks = KSteam;
namespace pc = pcprops;

struct MyProps
{
    pc::P   p { 0.0 };
    pc::T   t { 0.0 };
    pc::X   x { 0.0 };
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
                             "X [-]",
                             "V [m3/kg]",
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
                             props.v.get(),
                             props.h.get(),
                             props.s.get(),
                             props.u.get())
              << std::endl;
}

template<typename T1, typename T2>
void computeProps(auto& fluid, MyProps& props, const T1& prop1, const T2& prop2, const std::string& spec)
{
    using namespace pcprops;

    std::cout << std::fixed << std::setprecision(20);

    try {
        fluid.setState(prop1, prop2);
        auto p     = property<P>(fluid);
        auto x     = property<X>(fluid);
        bool print = false;

        if (abs(1.0 - p.get() / props.p.get()) > 1e-3) {
            print = true;
            std::cout << "P: " << p.get() << " != " << props.p.get() << std::endl;
        }

        if (abs(x.get() - props.x.get()) > 1e-3) {
            print = true;
            std::cout << "X: " << x.get() << " != " << props.x.get() << std::endl;
        }

        // auto tmp = properties<P, T, X, V, Rho, H, S, U>(fluid).template get<MassUnits>();
        props = properties<P, T, X, V, Rho, H, S, U>(fluid).template get<MyProps>();
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
    using namespace pcprops;

    std::cout << std::fixed << std::setprecision(20);

    MyProps props;
    auto    water = Fluid(CoolPropBackend("Water"));
    auto    q     = 0.0;

    // printHeader();
    // water.setState(P { 0.01 * 100000.0 }, X { 0.0 });
    // props = properties<P, T, X, V, Rho, H, S, U>(water).get<MyProps>();
    // printProps(props, "PX");
    //
    // water.setState(props.rho, props.u);
    // props = properties<P, T, X, V, Rho, H, S, U>(water).get<MyProps>();
    // printProps(props, "DU");

    io::CSVReader<10, io::trim_chars<' ', '\t'>, io::no_quote_escape<';'>> in("C:/Users/kenne/Desktop/Table02.csv");
    in.read_header(io::ignore_extra_column, "P", "ts", "v_liq", "v_vap", "h_liq", "h_vap", "Delta h", "s_liq", "s_vap", "Delta s");
    double p, t, v_liq, v_vap, h_liq, h_vap, dh, s_liq, s_vap, ds;

    while (in.read_row(p, t, v_liq, v_vap, h_liq, h_vap, dh, s_liq, s_vap, ds)) {
        props.p   = P { p * 100000 < water.min<P>() ? water.min<P>() : p * 100000 };
        props.t   = T { t + 273.15 };
        props.x   = X { q };
        props.v   = V { v_vap * q + v_liq * (1 - q) };
        props.h   = H { (h_vap * q + h_liq * (1 - q)) * 1000 };
        props.s   = S { (s_vap * q + s_liq * (1 - q)) * 1000 };
        props.rho = Rho { 1.0 / props.v };
        props.u   = U { props.h - props.p * props.v };

        printHeader();
        printProps(props, "Table");

        computeProps(water, props, props.p, X { q }, "PX");
        computeProps(water, props, props.p, props.h, "PH");
        computeProps(water, props, props.p, props.s, "PS");
        computeProps(water, props, props.p, props.u, "PU");
        computeProps(water, props, props.rho, props.t, "DT");
        computeProps(water, props, props.rho, props.u, "DU");
        // computeProps(water, props, props.h, props.s, "HS");
        computeProps(water, props, props.rho, props.h, "DH");
        computeProps(water, props, props.rho, props.s, "DS");
        computeProps(water, props, props.t, props.s, "TS");
        computeProps(water, props, props.p, props.rho, "DP");
    }

    return 0;
}
