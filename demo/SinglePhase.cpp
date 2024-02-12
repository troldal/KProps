//
// Created by Troldal on 01/10/2022.
//

#include "_external.hpp"

#include <KSteam.hpp>
#include <array>

#include <functional>
#include <iostream>



auto computeProps(const std::function<double(double, double, const char*)>& func, double arg1, double arg2)
{
    std::array<double, 8> props {};
    props[0] = func(arg1, arg2, "P");
    props[1] = func(arg1, arg2, "T");
    props[2] = KSteam::calcPropertyPT(props[0], props[1], "V");
    props[3] = KSteam::calcPropertyPT(props[0], props[1], "H");
    props[4] = KSteam::calcPropertyPT(props[0], props[1], "S");
    props[5] = KSteam::calcPropertyPT(props[0], props[1], "Cp");
    props[6] = KSteam::calcPropertyPT(props[0], props[1], "U");
    props[7] = KSteam::calcPropertyPT(props[0], props[1], "X");

    return props;
}

auto computeProps(const std::function<double(double, double, const char*, double)>& func, double arg1, double arg2, double guess)
{
    std::array<double, 8> props {};
    props[0] = func(arg1, arg2, "P", guess);
    props[1] = func(arg1, arg2, "T", guess);
    props[2] = KSteam::calcPropertyPT(props[0], props[1], "V");
    props[3] = KSteam::calcPropertyPT(props[0], props[1], "H");
    props[4] = KSteam::calcPropertyPT(props[0], props[1], "S");
    props[5] = KSteam::calcPropertyPT(props[0], props[1], "Cp");
    props[6] = KSteam::calcPropertyPT(props[0], props[1], "U");
    props[7] = KSteam::calcPropertyPT(props[0], props[1], "X");

    return props;
}

void printHeader()
{
    auto printLine = [](size_t colCount) {
        for (int i = 0; i < (colCount * 15 + (colCount - 1) * 3); ++i) std::cout << "-";
        std::cout << std::endl;
    };

    printLine(9);
    std::cout << fmt::format("{:>15} | {:>15} | {:>15} | {:>15} | {:>15} | {:>15} | {:>15} | {:>15} | {:>15} ",
                             "SPEC",
                             "P [bar]",
                             "T [C]",
                             "V [m3/kg]",
                             "RHO [kg/m3]",
                             "H [J/kg]",
                             "S [J/kg-K]",
                             "U [J/kg]",
                             "X [-]")
              << std::endl;
    printLine(9);
}

void printProps(const std::array<double, 8>& props, const std::string& spec)
{
    std::cout << fmt::format("{:15} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} | {:15.5f} ",
                             spec,
                             props[0] / 1.0e+05,
                             props[1],
                             props[2],
                             1.0 / props[2],
                             props[3],
                             props[4],
                             props[6],
                             props[7])
              << std::endl;
}

int main()
{
    // auto funcBase = [](double arg1, double arg2, const char* arg3) { return KSteam::calcPropertyPX(arg1, arg2, arg3); };
    auto funcBase = [](double arg1, double arg2, const char* arg3) { return KSteam::calcPropertyPT(arg1, arg2, arg3); };
    auto funcPH   = [](double arg1, double arg2, const char* arg3) { return KSteam::calcPropertyPH(arg1, arg2, arg3); };
    auto funcPS   = [](double arg1, double arg2, const char* arg3) { return KSteam::calcPropertyPS(arg1, arg2, arg3); };
    auto funcPU   = [](double arg1, double arg2, const char* arg3) { return KSteam::calcPropertyPU(arg1, arg2, arg3); };
    auto funcPD   = [](double arg1, double arg2, const char* arg3, double tg) { return KSteam::calcPropertyPRHO(arg1, arg2, arg3, tg); };
    auto funcPV   = [](double arg1, double arg2, const char* arg3, double tg) { return KSteam::calcPropertyPV(arg1, arg2, arg3, tg); };
    auto funcTD   = [](double arg1, double arg2, const char* arg3) { return KSteam::calcPropertyTRHO(arg1, arg2, arg3); };
    auto funcTV   = [](double arg1, double arg2, const char* arg3) { return KSteam::calcPropertyTV(arg1, arg2, arg3); };
    auto funcTH   = [](double arg1, double arg2, const char* arg3, double g) { return KSteam::calcPropertyTH(arg1, arg2, arg3, g); };
    auto funcTS   = [](double arg1, double arg2, const char* arg3, double g) { return KSteam::calcPropertyTS(arg1, arg2, arg3, g); };
    auto funcTU   = [](double arg1, double arg2, const char* arg3, double g) { return KSteam::calcPropertyTU(arg1, arg2, arg3, g); };

    io::CSVReader<10, io::trim_chars<' ', '\t'>, io::no_quote_escape<';'>> in("C:/Users/kenne/Desktop/Table03.csv");
    in.read_header(io::ignore_extra_column, "P", "t", "v", "h", "s", "cp", "w", "k", "eta", "lambda");
    double P, t, v, h, s, cp, w, k, eta, lambda;
    while (in.read_row(P, t, v, h, s, cp, w, k, eta, lambda)) {

        if (P <= 0.01) continue;
        if (t <= 0.01) continue;

        // if (P < 80.0) continue;
        // if (t < 290.0) continue;

        // if (P < 40.0) continue;
        // if (t < 250.0) continue;

        if (P >= 1000.0) continue;
        if (t >= 800.0) continue;

        printHeader();

        // double temp = 634.723;
        // double pres = IF97::psat97(temp);

        double temp    = t + 273.15;
        double pres    = P * 100000;

        auto baseProps = computeProps(funcBase, pres, temp);
        // baseProps[0]   = pres;
        // baseProps[1]   = temp;
        // baseProps[2] = v;
        // baseProps[3] = h * 1000;
        // baseProps[4] = s * 1000;


        printProps(baseProps, "PT");
        //printProps(computeProps(funcPH, pres, baseProps[3]), "PH");
        //printProps(computeProps(funcPS, pres, baseProps[4]), "PS");
        //printProps(computeProps(funcPU, pres, baseProps[6]), "PU");
        printProps(computeProps(funcPD, pres, 1.0 / baseProps[2], baseProps[1]), "PD");
        printProps(computeProps(funcPV, pres, baseProps[2], baseProps[1]), "PV");
        //printProps(computeProps(funcTD, temp, 1.0 / baseProps[2]), "TD");
        //printProps(computeProps(funcTV, temp, baseProps[2]), "TV");
        printProps(computeProps(funcTH, temp, baseProps[3], baseProps[0]), "TH");
        printProps(computeProps(funcTS, temp, baseProps[4], baseProps[0]), "TS");
        printProps(computeProps(funcTU, temp, baseProps[6], baseProps[0]), "TU");
    }

    return 0;
}