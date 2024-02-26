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

#include <KSteam.hpp>
#include <PCProps.hpp>

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

    // using namespace sciplot;
    // namespace rng = std::ranges;
    //
    // double p = 220.0 * 100000;
    //
    // Vec t = sciplot::linspace(271.45, 646.85, 200);
    //
    // std::vector< double > y_lin;
    // auto water = Fluid(CoolPropBackend("Water"));
    // rng::transform(t, std::back_inserter(y_lin), [&](auto val) {
    //     water.setState(P{p}, T{val});
    //     return property<H>(water) - H{27055.32};
    // });
    //
    // Plot2D plot1;
    // plot1.palette("paired");
    // plot1.drawCurve(t, y_lin).label("Linear").lineWidth(4);
    //
    // Figure figure = { { plot1 } };
    // Canvas canvas = { { figure } };
    //
    // canvas.defaultPalette("set1");
    // canvas.size(1600, 1200);
    // canvas.show();

    // std::cout << std::fixed << std::setprecision(20);
    //
    // auto water = Fluid(CoolPropBackend("Water"));
    // //water.setState(P { 101325.0 }, T { 298.15 });
    // water.setState(P { 101325.0 }, H { 1890.164 });
    // std::cout << property<Cp>(water) / property<MW>(water) << std::endl;
    //
    // auto pip = derivative<Of<P>, Wrt<V, T>>(water) / derivative<Of<P>, Wrt<T>, AtConst<V>>(water);
    // pip -= derivative<Of<P>, Wrt<V, V>, AtConst<T>>(water) / derivative<Of<P>, Wrt<V>, AtConst<T>>(water);
    // pip *= property<V>(water);
    //
    // std::cout << pip << std::endl;
    //
    // std::cout << derivative<Of<H>, Wrt<T>, AtConst<P>>(water) << std::endl;
    // std::cout << derivative<Of<P>, Wrt<Rho, Rho>, AtConst<T>>(water) << std::endl;
    // std::cout << derivative<Of<P>, Wrt<V, T>>(water) << std::endl;
    // std::cout << derivative<Of<S>, Wrt<T>, AtConst<V>>(water) << std::endl;
    // std::cout << derivative<Of<S>, Wrt<T>, AtConst<P>>(water) << std::endl;
    //
    // std::cout << property<H>(water) << std::endl;
    // std::cout << property<MW>(water) * 1000 << std::endl;
    //
    // auto props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();

    MyProps props;
    auto    water = Fluid(CoolPropBackend("Water"));

    io::CSVReader<5, io::trim_chars<' ', '\t'>, io::no_quote_escape<';'>> in("C:/Users/kenne/Desktop/Table03.csv");
    // in.read_header(io::ignore_extra_column, "P", "t", "v", "h", "s", "cp", "w", "k", "eta", "lambda");
    in.read_header(io::ignore_extra_column, "P", "t", "v", "h", "s");
    double p, t, v, h, s;
    while (in.read_row(p, t, v, h, s)) {
        props.p   = pc::P { p * 100000 < water.min<P>() ? water.min<P>() : p * 100000 };
        props.t   = pc::T { t + 273.15 };
        props.v   = pc::V { v };
        props.h   = pc::H { h * 1000 };
        props.s   = pc::S { s * 1000 };
        props.rho = pc::Rho { 1.0 / props.v };
        props.u   = pc::U { props.h - props.p * props.v };

        if (p <= 1.01) continue;
        if (t <= 2.01) continue;

        // auto tsat = water.property<TSat>();

        // if (p < 220.0) continue;
        // if (t < 603.15 - 273.15) continue;

        printHeader();
        printProps(props, "Table");

        water.setState(props.p, props.t);
        props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();
        printProps(props, "PT");

        water.setState(props.p, props.h);
        props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();
        printProps(props, "PH");

        water.setState(props.p, props.s);
        props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();
        printProps(props, "PS");

        water.setState(props.p, props.u);
        props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();
        printProps(props, "PU");

        water.setState(props.rho, props.t);
        props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();
        printProps(props, "DT");

        water.setState(props.rho, props.u);
        props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();
        printProps(props, "DU");

        // if (t > tsat.get()) {
        //     water.setState(props.h, props.s);
        //     props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();
        //     printProps(props, "HS");
        // }

        water.setState(props.rho, props.h);
        props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();
        printProps(props, "DH");

        water.setState(props.rho, props.s);
        props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();
        printProps(props, "DS");

        // water.setState(props.t, props.s);
        // props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();
        // printProps(props, "TS");

        // water.setState(props.p, props.rho);
        // props = properties<P, T, V, Rho, H, S, U>(water).get<MyProps>();
        // printProps(props, "DP");

    }

    return 0;
}
