//
// Created by kenne on 31/01/2024.
//

#include "_external.hpp"

#include <iostream>
#include <ranges>
#include <tuple>
#include <variant>
#include <vector>

#include <KSteam.hpp>

using namespace sciplot;
namespace rng = std::ranges;

namespace ks = KSteam;

struct MyProps
{
    ks::P   p { 0.0 };
    ks::T   t { 0.0 };
    ks::V   v { 0.0 };
    ks::Rho rho { 0.0 };
    ks::H   h { 0.0 };
    ks::S   s { 0.0 };
    ks::U   u { 0.0 };
};

void printHeader()
{
    auto printLine = [](size_t colCount) {
        for (int i = 0; i < (colCount * 15 + (colCount - 1) * 3); ++i) std::cout << "-";
        std::cout << std::endl;
    };

    printLine(8);
    std::cout << fmt::format("{:>15} | {:>15} | {:>15} | {:>15} | {:>15} | {:>15} | {:>15} | {:>15} ",
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
    std::cout << fmt::format("{:15} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} ",
                             spec,
                             props.p / 1.0e+05,
                             props.t,
                             props.v,
                             props.rho,
                             props.h,
                             props.s,
                             props.u)
              << std::endl;
}

int main()
{
    MyProps    props {};
    using Water = ks::ThermoModel<ks::Water>;

    io::CSVReader<5, io::trim_chars<' ', '\t'>, io::no_quote_escape<';'>> in("C:/Users/kenne/Desktop/Table03.csv");
    // in.read_header(io::ignore_extra_column, "P", "t", "v", "h", "s", "cp", "w", "k", "eta", "lambda");
    in.read_header(io::ignore_extra_column, "P", "t", "v", "h", "s");
    double p, t, v, h, s;
    while (in.read_row(p, t, v, h, s)) {
        props.p = ks::P{p * 100000 < Water{}.min<ks::P>() ? Water{}.min<ks::P>() : p * 100000};
        props.t = ks::T{t + 273.15};
        props.v  = ks::V{v};
        props.h  = ks::H{h * 1000};
        props.s  = ks::S{s * 1000};
        props.rho = ks::Rho{1.0 / props.v};
        props.u  = ks::U{props.h - props.p*props.v};

        // if (p < 0.01) continue;
        // if (t < 380.0) continue;

        // const auto p = ks::P { 101325.0 };
        // const auto t = ks::T { 473.15 };

        std::string tmp;

        printHeader();
        printProps(props, "Table");

        props = ks::flash<Water>(props.t, props.p).properties<ks::P, ks::T, ks::V, ks::Rho, ks::H, ks::S, ks::U>().get<MyProps>();
        printProps(props, "PT");

        props = ks::flash<Water>(props.p, props.h).properties<ks::P, ks::T, ks::V, ks::Rho, ks::H, ks::S, ks::U>().get<MyProps>();
        printProps(props, "PH");

        props = ks::flash<Water>(props.p, props.s).properties<ks::P, ks::T, ks::V, ks::Rho, ks::H, ks::S, ks::U>().get<MyProps>();
        printProps(props, "PS");

        props = ks::flash<Water>(props.p, props.u).properties<ks::P, ks::T, ks::V, ks::Rho, ks::H, ks::S, ks::U>().get<MyProps>();
        printProps(props, "PU");

        props = ks::flash<Water>(props.t, props.rho).properties<ks::P, ks::T, ks::V, ks::Rho, ks::H, ks::S, ks::U>().get<MyProps>();
        printProps(props, "TD");

        props = ks::flash<Water>(props.t, props.v).properties<ks::P, ks::T, ks::V, ks::Rho, ks::H, ks::S, ks::U>().get<MyProps>();
        printProps(props, "TV");
    }

    return 0;
}
