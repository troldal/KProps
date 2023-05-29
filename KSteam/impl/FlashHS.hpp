/*
KKKKKKKKK    KKKKKKK   SSSSSSSSSSSSSSS      tttt
K:::::::K    K:::::K SS:::::::::::::::S  ttt:::t
K:::::::K    K:::::KS:::::SSSSSS::::::S  t:::::t
K:::::::K   K::::::KS:::::S     SSSSSSS  t:::::t
KK::::::K  K:::::KKKS:::::S        ttttttt:::::ttttttt        eeeeeeeeeeee    aaaaaaaaaaaaa      mmmmmmm    mmmmmmm
  K:::::K K:::::K   S:::::S        t:::::::::::::::::t      ee::::::::::::ee  a::::::::::::a   mm:::::::m  m:::::::mm
  K::::::K:::::K     S::::SSSS     t:::::::::::::::::t     e::::::eeeee:::::eeaaaaaaaaa:::::a m::::::::::mm::::::::::m
  K:::::::::::K       SS::::::SSSSStttttt:::::::tttttt    e::::::e     e:::::e         a::::a m::::::::::::::::::::::m
  K:::::::::::K         SSS::::::::SS    t:::::t          e:::::::eeeee::::::e  aaaaaaa:::::a m:::::mmm::::::mmm:::::m
  K::::::K:::::K           SSSSSS::::S   t:::::t          e:::::::::::::::::e aa::::::::::::a m::::m   m::::m   m::::m
  K:::::K K:::::K               S:::::S  t:::::t          e::::::eeeeeeeeeee a::::aaaa::::::a m::::m   m::::m   m::::m
KK::::::K  K:::::KKK            S:::::S  t:::::t    tttttte:::::::e         a::::a    a:::::a m::::m   m::::m   m::::m
K:::::::K   K::::::KSSSSSSS     S:::::S  t::::::tttt:::::te::::::::e        a::::a    a:::::a m::::m   m::::m   m::::m
K:::::::K    K:::::KS::::::SSSSSS:::::S  tt::::::::::::::t e::::::::eeeeeeeea:::::aaaa::::::a m::::m   m::::m   m::::m
K:::::::K    K:::::KS:::::::::::::::SS     tt:::::::::::tt  ee:::::::::::::e a::::::::::aa:::am::::m   m::::m   m::::m
KKKKKKKKK    KKKKKKK SSSSSSSSSSSSSSS         ttttttttttt      eeeeeeeeeeeeee  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm

MIT License

Copyright (c) 2023 Kenneth Troldal Balslev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef KSTEAM_FLASHHS_HPP
#define KSTEAM_FLASHHS_HPP

#include "Config.hpp"
#include "FlashPSpec.hpp"
#include <multiroots/Multiroots.hpp>
#include <numerixx.hpp>

namespace KSteam
{

    inline double calcPropertyHS(double Enthalpy, double Entropy, Property property)
    {
        using namespace nxx::roots;
        using namespace nxx::multiroots;

        auto eq1 = [&](std::vector<double> guess) { return calcPropertyPT(guess[0], guess[1], "H") - Enthalpy; };
        auto eq2 = [&](std::vector<double> guess) { return calcPropertyPT(guess[0], guess[1], "S") - Entropy; };

        auto guessP = IF97::p_hsmass(Enthalpy, Entropy);
        auto guessT = IF97::T_hsmass(Enthalpy, Entropy);

        std::vector<FLOAT> guess = { guessP, guessT};
        std::vector<std::pair<FLOAT, FLOAT>> limits = { { std::max(1000.0, guessP * 0.9), std::min(100E6, guessP * 1.1) },
                                                        { std::max(273.16, guessT * 0.9), std::min(1073.15, guessT * 1.1) } };

        std::vector<std::function<double(std::vector<double>)>> fns = { eq1, eq2 };

        auto solver = nxx::multiroots::DMultiNewton(fns, limits);
        solver.init(guess);
        auto result = solver.result();
        auto tempResult = result;

        auto calcEPS = [&](auto res) {
            auto  fvals = solver.evaluate(res);
            FLOAT eps   = 0.0;
            for (auto& fval : fvals) eps += abs(fval);
            return eps;
        };

        int counter = 1;
        FLOAT multiplier = 1.0;
        while (true) {
            solver.iterate(multiplier);
            tempResult = solver.result();

            if (calcEPS(tempResult) < calcEPS(result)) {
                result = tempResult;
                multiplier = 1.0;
            }
            else {
                multiplier *= 0.5;
                solver.init(result);
            }


            // Check for convergence
            if (calcEPS(result) < EPS) break;
            if (multiplier < EPS) break;
            if (counter >= 100) break;

            // Perform one iteration
            ++counter;

        }


        //        auto result = multisolve(solver, guess, EPS, 1000);

//        auto calcH = calcPropertyPT(result[0], result[1], "H");
//        auto calcS = calcPropertyPT(result[0], result[1], "S");
//
//        if (std::abs(calcH - Enthalpy) > EPS || std::abs(calcS - Entropy) > EPS)
//            return calcPropertyPT(guessP, guessT, property);

        return calcPropertyPT(result[0], result[1], property);
    }
}

#endif    // KSTEAM_FLASHHS_HPP
