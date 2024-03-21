//
// Created by kenne on 31/01/2024.
//

#include "_external.hpp"

#include <HEOS.hpp>
#include <IF97.hpp>
#include <KProps.hpp>

#include <format>
#include <iostream>
#include <string>
#include <variant>
#include <iomanip>
#include <numbers>

using namespace sciplot;
namespace rng = std::ranges;

namespace kp = KProps;

struct MyProps
{
    kp::P   p { 0.0 };
    kp::T   t { 0.0 };
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

template<typename T1, typename T2>
void computeProps(auto& fluid, MyProps& props, const T1& prop1, const T2& prop2, const std::string& spec)
{
    using namespace KProps;

    std::cout << std::fixed << std::setprecision(20);

//    try {
        fluid.template setState<MassUnits>(prop1, prop2);

        auto p = property<P>(fluid);
        auto t = property<T>(fluid);
        bool print = false;

//        if (abs(1.0 - p.get() / props.p.get()) > 1e-3) {
//            print = true;
//            std::cout << "P: " << p.get() << " != " << props.p.get() << std::endl;
//        }
//
//
//        if (abs(t.get() - props.t.get()) > 1e-3) {
//            print = true;
//            std::cout << "T: " << t.get() << " != " << props.t.get() << std::endl;
//        }

        props = properties<P, T, V, Rho, H, S, U>(fluid).get<MyProps, MassUnits>();
        // if (print) {
        //     printHeader();
            printProps(props, spec);
        // }
//    } catch (...) {
//        std::cout << "Error computing " << spec << " at:" << prop1 << " and " << prop2 << std::endl;
//    }
}

int main()
{
    using namespace KProps;

    MyProps props;
//    auto    water = FluidWrapper(CoolPropBackend("Water", P{101325.0}, T{298.15}));
    auto    water = FluidWrapper(IF97Backend(P{101325.0}, T{298.15}));

    io::CSVReader<5, io::trim_chars<' ', '\t'>, io::no_quote_escape<';'>> in("C:/Users/kenne/Desktop/Table03.csv");
    in.read_header(io::ignore_extra_column, "P", "t", "v", "h", "s");
    double p, t, v, h, s;

    while (in.read_row(p, t, v, h, s)) {
        props.p   = kp::P { p * 100000 < water.min<P>() ? water.min<P>() : p * 100000 };
        props.t   = kp::T { t + 273.15 };
        props.v   = kp::V { v };
        props.h   = kp::H { h * 1000 };
        props.s   = kp::S { s * 1000 };
        props.rho = kp::Rho { 1.0 / props.v };
        props.u   = kp::U { props.h - props.p * props.v };

        if (p < 50.01) continue;
        if (t < 50.01) continue;

        printHeader();
        printProps(props, "Table");

        computeProps(water, props, props.p, props.t, "PT");
        computeProps(water, props, props.p, props.h, "PH");
        computeProps(water, props, props.p, props.s, "PS");
//        computeProps(water, props, props.p, props.u, "PU");
//        computeProps(water, props, props.rho, props.t, "DT");
//        computeProps(water, props, props.rho, props.u, "DU");
         computeProps(water, props, props.h, props.s, "HS");
//        computeProps(water, props, props.rho, props.h, "DH");
//        computeProps(water, props, props.rho, props.s, "DS");
//         computeProps(water, props, props.t, props.s, "TS");
//         computeProps(water, props, props.p, props.rho, "DP");
    }

    return 0;
}
