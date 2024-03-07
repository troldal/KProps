//
// Created by kenne on 05/02/2024.
//

#pragma once

#include <IF97/IF97.h>

namespace KSteam
{

    template<typename FLOAT_T = double>
    class Water
    {
    public:
         Water() = default;
        ~Water() = default;

        FLOAT_T criticalPressure() const { return IF97::Pcrit; }

        FLOAT_T criticalTemperature() const { return IF97::Tcrit; }

        FLOAT_T saturationPressureAtT(FLOAT_T t) const { return std::max(IF97::psat97(t), IF97::Pmin); }

        FLOAT_T saturationTemperatureAtP(FLOAT_T p) const { return std::max(IF97::Tsat97(p), IF97::Tmin); }

        FLOAT_T enthalpyAtPT(FLOAT_T p, FLOAT_T t) const { return IF97::hmass_Tp(t, p); }

        FLOAT_T entropyAtPT(FLOAT_T p, FLOAT_T t) const { return IF97::smass_Tp(t, p); }

        FLOAT_T densityAtPT(FLOAT_T p, FLOAT_T t) const { return IF97::rhomass_Tp(t, p); }

        FLOAT_T internalEnergyAtPT(FLOAT_T p, FLOAT_T t) const { return IF97::umass_Tp(t, p); }

        FLOAT_T cpAtPT(FLOAT_T p, FLOAT_T t) const { return IF97::cpmass_Tp(t, p); }

        FLOAT_T cvAtPT(FLOAT_T p, FLOAT_T t) const { return IF97::cvmass_Tp(t, p); }

        FLOAT_T omegaAtPT(FLOAT_T p, FLOAT_T t) const { return IF97::speed_sound_Tp(t, p); }

        FLOAT_T liquidEnthalpyAtPSat(FLOAT_T p) const { return IF97::hliq_p(p); }

        FLOAT_T liquidEntropyAtPSat(FLOAT_T p) const { return IF97::sliq_p(p); }

        FLOAT_T liquidDensityAtPSat(FLOAT_T p) const { return IF97::rholiq_p(p); }

        FLOAT_T liquidInternalEnergyAtPSat(FLOAT_T p) const { return IF97::uliq_p(p); }

        FLOAT_T liquidCpAtPSat(FLOAT_T p) const { return IF97::cpliq_p(p); }

        FLOAT_T liquidCvAtPSat(FLOAT_T p) const { return IF97::cvliq_p(p); }

        FLOAT_T liquidOmegaAtPSat(FLOAT_T p) const { return IF97::speed_soundliq_p(p); }

        FLOAT_T vaporEnthalpyAtPSat(FLOAT_T p) const { return IF97::hvap_p(p); }

        FLOAT_T vaporEntropyAtPSat(FLOAT_T p) const { return IF97::svap_p(p); }

        FLOAT_T vaporDensityAtPSat(FLOAT_T p) const { return IF97::rhovap_p(p); }

        FLOAT_T vaporInternalEnergyAtPSat(FLOAT_T p) const { return IF97::uvap_p(p); }

        FLOAT_T vaporCpAtPSat(FLOAT_T p) const { return IF97::cpvap_p(p); }

        FLOAT_T vaporCvAtPSat(FLOAT_T p) const { return IF97::cvvap_p(p); }

        FLOAT_T vaporOmegaAtPSat(FLOAT_T p) const { return IF97::speed_soundvap_p(p); }

        FLOAT_T temperatureGuessAtPH(FLOAT_T p, FLOAT_T h) const { return IF97::T_phmass(p, h); }

        FLOAT_T densityGuessAtPH(FLOAT_T p, FLOAT_T h) const { return IF97::rhomass_phmass(p, h); }

        FLOAT_T temperatureGuessAtPS(FLOAT_T p, FLOAT_T s) const { return IF97::T_psmass(p, s); }

        FLOAT_T densityGuessAtPS(FLOAT_T p, FLOAT_T s) const { return IF97::rhomass_psmass(p, s); }

        FLOAT_T temperatureGuessAtHS(FLOAT_T h, FLOAT_T s) const { return IF97::T_hsmass(h, s); }

        FLOAT_T pressureGuessAtHS(FLOAT_T h, FLOAT_T s) const { return IF97::p_hsmass(h, s); }

        FLOAT_T minTemperature() const { return IF97::Tmin; }

        FLOAT_T maxTemperature() const { return IF97::Tmax; }

        FLOAT_T minPressure() const { return IF97::Pmin; }

        FLOAT_T maxPressure() const { return IF97::Pmax; }
    };

  Water() -> Water<double>;

}    // namespace KSteam