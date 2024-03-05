//
// Created by kenne on 31/01/2024.
//

#include "_external.hpp"

#include <HEOS.hpp>
#include <KProps.hpp>

#include <format>
#include <iostream>
#include <string>
#include <variant>
#include <iomanip>
#include <numbers>

using namespace sciplot;
namespace rng = std::ranges;

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

    auto water = FluidWrapper(CoolPropBackend("Water"));
    water.setState(P{101325.0}, T{298.15});
    // water.setState(P { 101325.0 }, T { 298.15 });

    std::cout << std::fixed << std::setprecision(20);

    //std::cout << "LIQ: "<< phase<Liquid>(water).property<H, MassUnits>() << std::endl;
    //std::cout << "MIX:" << phase<Mixture>(water).property<H, MassUnits>() << std::endl;
    //std::cout << "VAP:" << phase<Gas>(water).property<H, MassUnits>() << std::endl;

    //auto v1 = phase<Liquid>(water).properties<P, T, V, Rho, H, S, U>().get<MyProps, MassUnits>();
    //auto v2 = phase<Mixture>(water).properties<P, T, V, Rho, H, S, U>().get<MyProps, MassUnits>();
    //auto v3 = phase<Gas>(water).properties<P, T, V, Rho, H, S, U>().get<MyProps, MassUnits>();

    std::cout << "MW    :" << property<MW>(water) << std::endl;
//    std::cout << "W     :" << property<W>(water) << std::endl;
//    std::cout << "Kappa :" << property<Kappa>(water) << std::endl;
//    std::cout << "Alpha :" << property<Alpha>(water) << std::endl;
    std::cout << "Cp    :" << property<Cp>(water) << std::endl;
    std::cout << "Cv    :" << property<Cv>(water) << std::endl;
    std::cout << "Rho   :" << property<Rho>(water) << std::endl;
    std::cout << "P     :" << property<P>(water) << std::endl;
    std::cout << "T     :" << property<T>(water) << std::endl;
    std::cout << "G     :" << property<G>(water) << std::endl;
    std::cout << "A     :" << property<A>(water) << std::endl;
    std::cout << "H     :" << property<H>(water) << std::endl;
    std::cout << "U     :" << property<U>(water) << std::endl;
    std::cout << "S     :" << property<S>(water) << std::endl;
    std::cout << "TSat  :" << saturation<T>(water) << std::endl;
    std::cout << "PSat  :" << saturation<P>(water) << std::endl;
    std::cout << "Z     :" << property<Z>(water) << std::endl;
    std::cout << "dPdT  :" << derivative<Of<P>, Wrt<T>, AtConst<V>>(water) << std::endl;
    std::cout << "dPdRho:" << derivative<Of<P>, Wrt<Rho>, AtConst<T>>(water) << std::endl;



    // std::cout << property<T>(water) << std::endl;
    // std::cout << property<Q>(water) << std::endl;
    // std::cout << property<H, MassUnits>(water) / 1000<< std::endl;
    // std::cout << property<U, MassUnits>(water) / 1000<< std::endl;
    // std::cout << property<S, MassUnits>(water) / 1000 << std::endl;
    // std::cout << property<Rho, MassUnits>(water) << std::endl;
    // std::cout << property<Cp>(water) << std::endl;
    // std::cout << property<Cv>(water) << std::endl;
    //
    // std::cout << saturation<P>(water) << std::endl;
    // std::cout << saturation<T>(water) << std::endl;
    // std::cout << critical<T>(water) << std::endl;
    // std::cout << critical<P>(water) << std::endl;
    // std::cout << min<T>(water) << std::endl;
    // std::cout << max<T>(water) << std::endl;
    // std::cout << min<P>(water) << std::endl;
    // std::cout << max<P>(water) << std::endl;
    //
    // std::cout << std::endl;
    //
    // water.setState(property<T>(water), property<S>(water));
    // std::cout << property<T>(water) << std::endl;
    // std::cout << property<Q>(water) << std::endl;
    // std::cout << property<H>(water) << std::endl;
    // std::cout << property<U>(water) << std::endl;
    // std::cout << property<S>(water) << std::endl;
    // std::cout << property<Rho>(water) << std::endl;
    // std::cout << property<Cp>(water) << std::endl;
    // std::cout << property<Cv>(water) << std::endl;


    return 0;
}
