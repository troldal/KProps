#include "_external.hpp"
#include <KSteam.hpp>


#include <cmath>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <ranges>

int main()
{

    using namespace sciplot;
    namespace rng = std::ranges;

    double t = 563.15;
    double p = IF97::psat97(t) + 1e-8;

    Vec x = linspace(p, 100000000.0, 200);

    std::vector< double > y_lin;
    rng::transform(x, std::back_inserter(y_lin), [&](auto val) { return KSteam::calcPropertyPT(val, t, KSteam::Property::Enthalpy); });

    Plot2D plot1;
    plot1.palette("paired");
    plot1.drawCurve(x, y_lin).label("Linear").lineWidth(4);

    Figure figure = { { plot1 } };
    Canvas canvas = { { figure } };

    canvas.defaultPalette("set1");
    canvas.size(1600, 1200);
    canvas.show();

    return 0;
}
