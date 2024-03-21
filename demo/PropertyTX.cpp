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
    using namespace KProps;

    std::cout << std::fixed << std::setprecision(20);

    try {
        fluid.setState(prop1, prop2);
        auto t     = property<T>(fluid);
        auto x     = property<X>(fluid);
        bool print = false;

        if (abs(1.0 - t.get() / props.t.get()) > 1e-3) {
            print = true;
            std::cout << "T: " << t.get() << " != " << props.t.get() << std::endl;
        }

        if (abs(x.get() - props.x.get()) > 1e-3) {
            print = true;
            std::cout << "X: " << x.get() << " != " << props.x.get() << std::endl;
        }

        props = properties<P, T, X, V, Rho, H, S, U>(fluid).template get<MyProps>();
        // if (print) {
            printHeader();
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
    auto    water = Fluid(CoolPropBackend("Water"));
    auto    q     = 0.0;

    // printHeader();
    // water.setState(T { 487.15 }, X { 0.0 });
    // props = properties<P, T, X, V, Rho, H, S, U>(water).get<MyProps>();
    // printProps(props, "TX");
    //
    // water.setState(props.t, props.s);
    // props = properties<P, T, X, V, Rho, H, S, U>(water).get<MyProps>();
    // printProps(props, "TS");
    //
    // water.setState(props.rho, props.p);
    // props = properties<P, T, X, V, Rho, H, S, U>(water).get<MyProps>();
    // printProps(props, "DP");

    io::CSVReader<9, io::trim_chars<' ', '\t'>, io::no_quote_escape<';'>> in("C:/Users/kenne/Desktop/Table01.csv");
    in.read_header(io::ignore_extra_column, "t", "Ps", "v_liq", "v_vap", "h_liq", "h_vap", "Delta h", "s_liq", "s_vap");
    double t, Ps, v_liq, v_vap, h_liq, h_vap, dh, s_liq, s_vap;

    while (in.read_row(t, Ps, v_liq, v_vap, h_liq, h_vap, dh, s_liq, s_vap)) {
        props.p   = P { Ps * 100000 < water.min<P>() ? water.min<P>() : Ps * 100000 };
        props.t   = T { t + 273.15 };
        props.x   = X { q };
        props.v   = V { v_vap * q + v_liq * (1 - q) };
        props.h   = H { (h_vap * q + v_liq * (1 - q)) * 1000 };
        props.s   = S { (s_vap * q + s_liq * (1 - q)) * 1000 };
        props.rho = Rho { 1.0 / props.v };
        props.u   = U { props.h - props.p * props.v };

        // printHeader();
        // printProps(props, "Table");

        computeProps(water, props, props.t, X { q }, "TX");
        computeProps(water, props, props.p, props.h, "PH");
        computeProps(water, props, props.p, props.s, "PS");
        computeProps(water, props, props.p, props.u, "PU");
        computeProps(water, props, props.rho, props.t, "DT");
        computeProps(water, props, props.rho, props.u, "DU");
        //computeProps(water, props, props.h, props.s, "HS");
        computeProps(water, props, props.rho, props.h, "DH");
        computeProps(water, props, props.rho, props.s, "DS");
        computeProps(water, props, props.t, props.s, "TS");
        computeProps(water, props, props.p, props.rho, "DP");
    }

    return 0;
}
