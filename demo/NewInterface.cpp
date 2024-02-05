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

struct Data
{
    ks::P     p;
    ks::T     t;
    ks::H     h;
    ks::S     s;
    ks::U     u;
    ks::A     a;
    ks::G     g;
    ks::Rho   rho;
    ks::V     v;
    ks::PSat  psat;
    ks::TSat  tsat;
    ks::Cp    cp;
    ks::Cv    cv;
    ks::Kappa kappa;
    ks::W     w;
    ks::Z     z;
    ks::X     x;
    ks::Eta   eta;
    ks::Nu    nu;
    ks::TC    tc;
    ks::PR    pr;
};

struct DataRaw
{
    double p;
    double t;
    double h;
    double s;
    double u;
    double a;
    double g;
    double rho;
    double v;
    double psat;
    double tsat;
    double cp;
    double cv;
    double kappa;
    double w;
    double z;
    double x;
    double eta;
    double nu;
    double tc;
    double pr;
};

struct SingleData
{
    ks::Rho rho;
};

int main()
{
    double pressure;
    double temperature_low;
    double temperature_high;

    std::cout << "Enter pressure: ";
    std::cin >> pressure;

    std::cout << "Enter low temperature: ";
    std::cin >> temperature_low;

    std::cout << "Enter high temperature: ";
    std::cin >> temperature_high;

    Vec x = linspace(temperature_low, temperature_high, 10000);

    std::vector<double> density;
    rng::transform(x, std::back_inserter(density), [&](auto val) {
        return ks::flash(ks::P { pressure }, ks::T { val }).properties<ks::Rho>().get<SingleData>().rho;
    });

    Plot2D plot1;
    plot1.palette("paired");
    plot1.drawCurve(x, density).label("Density").lineWidth(4);

    Figure figure = { { plot1 } };
    Canvas canvas = { { figure } };

    canvas.defaultPalette("set1");
    canvas.size(1600, 1200);
    canvas.show();

    // using PROP_T = std::variant<ks::P,
    //                             ks::T,
    //                             ks::H,
    //                             ks::S,
    //                             ks::U,
    //                             ks::A,
    //                             ks::G,
    //                             ks::Rho,
    //                             ks::V,
    //                             ks::PSat,
    //                             ks::TSat,
    //                             ks::Cp,
    //                             ks::Cv,
    //                             ks::Kappa,
    //                             ks::W,
    //                             ks::Z,
    //                             ks::X,
    //                             ks::Eta,
    //                             ks::Nu,
    //                             ks::TC,
    //                             ks::PR>;
    //
    // // auto results = ks::flash<ks::P, ks::X>(6000000.0, 1.0).properties<ks::T, ks::P, ks::H, ks::S>().get<std::vector>();
    // auto results = ks::flash(ks::P { 6000000.0 }, ks::X { 0.5 }).get<DataRaw>();
    //
    // std::cout << results.p << std::endl;
    // std::cout << results.t << std::endl;
    // std::cout << results.h << std::endl;
    // std::cout << results.s << std::endl;
    //
    // // std::cout << std::get<0>(results) << std::endl;
    // // std::cout << std::get<1>(results) << std::endl;
    // // std::cout << std::get<2>(results) << std::endl;
    // // std::cout << std::get<3>(results) << std::endl;
    //
    // // std::cout << std::get<ks::P>(results[0]) << std::endl;
    // // std::cout << std::get<ks::T>(results[1]) << std::endl;
    // // std::cout << std::get<ks::H>(results[2]) << std::endl;
    // // std::cout << std::get<ks::S>(results[3]) << std::endl;
    // //
    // // for (const auto& elem : results)
    // //     std::visit([](auto&& arg) { std::cout << arg << std::endl; }, elem);
    //
    // // auto data = properties.get<Data>();

    return 0;
}
