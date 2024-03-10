//
// Created by kenne on 31/01/2024.
//

#pragma once

// #include "../_external.hpp"

#include <algorithm>
#include <array>
#include <variant>

#include <NamedType/named_type.hpp>

#include "../Utils/Config.hpp"

namespace pcprops
{

    enum class Property {
        T           = 0,
        Temperature = 0,

        P        = 1,
        Pressure = 1,

        H        = 2,
        Enthalpy = 2,

        S       = 3,
        Entropy = 3,

        U              = 4,
        InternalEnergy = 4,

        A               = 5,
        HelmholtzEnergy = 5,

        G           = 6,
        GibbsEnergy = 6,

        Rho     = 7,
        Density = 7,

        V      = 8,
        Volume = 8,
        Vol    = 8,

        Cp = 9,

        Cv = 10,

        Kappa                     = 11,
        IsothermalCompressibility = 11,

        Alpha            = 12,
        ThermalExpansion = 12,

        W            = 13,
        SpeedOfSound = 13,

        Z                     = 14,
        CompressibilityFactor = 14,

        X            = 15,
        Q            = 15,
        VaporQuality = 15,

        Eta              = 16,
        DynamicViscosity = 16,

        Nu                 = 17,
        KinematicViscosity = 17,

        TC                  = 18,
        ThermalConductivity = 18,

        PR            = 19,
        PrandtlNumber = 19,

        MW              = 20,
        MolecularWeight = 20,
        MolarMass       = 20,

        Undefined = 99

    };

    using MW = fluent::NamedType<FLOAT,
                                 struct MolarWeightTag,
                                 fluent::Printable,
                                 fluent::Addable,
                                 fluent::Subtractable,
                                 fluent::Multiplicable,
                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    using MolecularWeight = MW;
    using MolarMass       = MW;

    using T           = fluent::NamedType<FLOAT,
                                          struct TemperatureTag,
                                          fluent::Printable,
                                          fluent::Addable,
                                          fluent::Subtractable,
                                          fluent::Multiplicable,
                                          fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Temperature = T;

    using P        = fluent::NamedType<FLOAT,
                                       struct PressureTag,
                                       fluent::Printable,
                                       fluent::Addable,
                                       fluent::Subtractable,
                                       fluent::Multiplicable,
                                       fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Pressure = P;

    using H        = fluent::NamedType<FLOAT,
                                       struct EnthalpyTag,
                                       fluent::Printable,
                                       fluent::Addable,
                                       fluent::Subtractable,
                                       fluent::Multiplicable,
                                       fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Enthalpy = H;

    using S       = fluent::NamedType<FLOAT,
                                      struct EntropyTag,
                                      fluent::Printable,
                                      fluent::Addable,
                                      fluent::Subtractable,
                                      fluent::Multiplicable,
                                      fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Entropy = S;

    using U              = fluent::NamedType<FLOAT,
                                             struct InternalEnergyTag,
                                             fluent::Printable,
                                             fluent::Addable,
                                             fluent::Subtractable,
                                             fluent::Multiplicable,
                                             fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using InternalEnergy = U;

    using A               = fluent::NamedType<FLOAT,
                                              struct HelmholtzEnergyTag,
                                              fluent::Printable,
                                              fluent::Addable,
                                              fluent::Subtractable,
                                              fluent::Multiplicable,
                                              fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using HelmholtzEnergy = A;

    using G           = fluent::NamedType<FLOAT,
                                          struct GibbsEnergyTag,
                                          fluent::Printable,
                                          fluent::Addable,
                                          fluent::Subtractable,
                                          fluent::Multiplicable,
                                          fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using GibbsEnergy = G;

    using Rho     = fluent::NamedType<FLOAT,
                                      struct DensityTag,
                                      fluent::Printable,
                                      fluent::Addable,
                                      fluent::Subtractable,
                                      fluent::Multiplicable,
                                      fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Density = Rho;

    using V      = fluent::NamedType<FLOAT,
                                     struct VolumeTag,
                                     fluent::Printable,
                                     fluent::Addable,
                                     fluent::Subtractable,
                                     fluent::Multiplicable,
                                     fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Volume = V;
    using Vol    = V;

    using Cp = fluent::NamedType<FLOAT,
                                 struct CpTag,
                                 fluent::Printable,
                                 fluent::Addable,
                                 fluent::Subtractable,
                                 fluent::Multiplicable,
                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    using Cv = fluent::NamedType<FLOAT,
                                 struct CvTag,
                                 fluent::Printable,
                                 fluent::Addable,
                                 fluent::Subtractable,
                                 fluent::Multiplicable,
                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    using Kappa                     = fluent::NamedType<FLOAT,
                                                        struct KappaTag,
                                                        fluent::Printable,
                                                        fluent::Addable,
                                                        fluent::Subtractable,
                                                        fluent::Multiplicable,
                                                        fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using IsothermalCompressibility = Kappa;

    using Alpha            = fluent::NamedType<FLOAT,
                                               struct AlphaTag,
                                               fluent::Printable,
                                               fluent::Addable,
                                               fluent::Subtractable,
                                               fluent::Multiplicable,
                                               fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using ThermalExpansion = Alpha;

    using W            = fluent::NamedType<FLOAT,
                                           struct SpeedOfSoundTag,
                                           fluent::Printable,
                                           fluent::Addable,
                                           fluent::Subtractable,
                                           fluent::Multiplicable,
                                           fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using SpeedOfSound = W;

    using Z                     = fluent::NamedType<FLOAT,
                                                    struct CompressibilityFactorTag,
                                                    fluent::Printable,
                                                    fluent::Addable,
                                                    fluent::Subtractable,
                                                    fluent::Multiplicable,
                                                    fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using CompressibilityFactor = Z;

    using X            = fluent::NamedType<FLOAT,
                                           struct VaporQualityTag,
                                           fluent::Printable,
                                           fluent::Addable,
                                           fluent::Subtractable,
                                           fluent::Multiplicable,
                                           fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Q            = X;
    using VaporQuality = X;

    using Eta              = fluent::NamedType<FLOAT,
                                               struct DynamicViscosityTag,
                                               fluent::Printable,
                                               fluent::Addable,
                                               fluent::Subtractable,
                                               fluent::Multiplicable,
                                               fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using DynamicViscosity = Eta;

    using Nu                 = fluent::NamedType<FLOAT,
                                                 struct KinematicViscosityTag,
                                                 fluent::Printable,
                                                 fluent::Addable,
                                                 fluent::Subtractable,
                                                 fluent::Multiplicable,
                                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using KinematicViscosity = Nu;

    using TC                  = fluent::NamedType<FLOAT,
                                                  struct ThermalConductivityTag,
                                                  fluent::Printable,
                                                  fluent::Addable,
                                                  fluent::Subtractable,
                                                  fluent::Multiplicable,
                                                  fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using ThermalConductivity = TC;

    using PR            = fluent::NamedType<FLOAT,
                                            struct PrandtlNumberTag,
                                            fluent::Printable,
                                            fluent::Addable,
                                            fluent::Subtractable,
                                            fluent::Multiplicable,
                                            fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using PrandtlNumber = PR;

    template<typename PROPERTY>
    concept IsProperty =
        std::same_as<PROPERTY, T> || std::same_as<PROPERTY, P> || std::same_as<PROPERTY, H> || std::same_as<PROPERTY, S> ||
        std::same_as<PROPERTY, U> || std::same_as<PROPERTY, A> || std::same_as<PROPERTY, G> || std::same_as<PROPERTY, Rho> ||
        std::same_as<PROPERTY, V> || std::same_as<PROPERTY, Cp> || std::same_as<PROPERTY, Cv> || std::same_as<PROPERTY, Kappa> ||
        std::same_as<PROPERTY, W> || std::same_as<PROPERTY, Z> || std::same_as<PROPERTY, X> || std::same_as<PROPERTY, Eta> ||
        std::same_as<PROPERTY, Nu> || std::same_as<PROPERTY, TC> || std::same_as<PROPERTY, PR> || std::same_as<PROPERTY, MW> ||
        std::same_as<PROPERTY, Alpha>;

    template<typename S1, typename S2>
    concept IsSpecificationPT = (std::same_as<S1, P> && std::same_as<S2, T>) || (std::same_as<S1, T> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPH = (std::same_as<S1, P> && std::same_as<S2, H>) || (std::same_as<S1, H> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPS = (std::same_as<S1, P> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPU = (std::same_as<S1, P> && std::same_as<S2, U>) || (std::same_as<S1, U> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPD = (std::same_as<S1, P> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPV = (std::same_as<S1, P> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPX = (std::same_as<S1, P> && std::same_as<S2, X>) || (std::same_as<S1, X> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationTH = (std::same_as<S1, T> && std::same_as<S2, H>) || (std::same_as<S1, H> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationTS = (std::same_as<S1, T> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationTU = (std::same_as<S1, T> && std::same_as<S2, U>) || (std::same_as<S1, U> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationTD = (std::same_as<S1, T> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationTV = (std::same_as<S1, T> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationTX = (std::same_as<S1, T> && std::same_as<S2, X>) || (std::same_as<S1, X> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationHS = (std::same_as<S1, H> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, H>);

    template<typename S1, typename S2>
    concept IsSpecificationUV = (std::same_as<S1, U> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, U>);

    template<typename S1, typename S2>
    concept IsSpecificationHV = (std::same_as<S1, H> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, H>);

    template<typename S1, typename S2>
    concept IsSpecificationDS = (std::same_as<S1, S> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, S>);

    template<typename S1, typename S2>
    concept IsSpecificationDH = (std::same_as<S1, H> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, H>);

    template<typename S1, typename S2>
    concept IsSpecificationDU = (std::same_as<S1, U> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, U>);

    template<typename S1, typename S2>
    concept IsSpecificationSU = (std::same_as<S1, U> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, U>);

    template<typename S1, typename S2>
    concept IsSpecification =
        IsSpecificationPT<S1, S2> || IsSpecificationPH<S1, S2> || IsSpecificationPS<S1, S2> || IsSpecificationPU<S1, S2> ||
        IsSpecificationPD<S1, S2> || IsSpecificationPV<S1, S2> || IsSpecificationPX<S1, S2> || IsSpecificationTH<S1, S2> ||
        IsSpecificationTS<S1, S2> || IsSpecificationTU<S1, S2> || IsSpecificationTD<S1, S2> || IsSpecificationTV<S1, S2> ||
        IsSpecificationTX<S1, S2> || IsSpecificationHS<S1, S2> || IsSpecificationUV<S1, S2> || IsSpecificationHV<S1, S2>;

    using PropertyVariant = std::variant<T, P, H, S, U, A, G, Rho, V, Cp, Cv, Kappa, Alpha, W, Z, X, /*Eta, Nu, TC, PR,*/ MW>;

    inline PropertyVariant mapPropertyToVariant(Property prop)
    {
        switch (prop) {
            case Property::T:
                return T { 0.0 };
            case Property::P:
                return P { 0.0 };
            case Property::H:
                return H { 0.0 };
            case Property::S:
                return S { 0.0 };
            case Property::U:
                return U { 0.0 };
            case Property::A:
                return A { 0.0 };
            case Property::G:
                return G { 0.0 };
            case Property::Rho:
                return Rho { 0.0 };
            case Property::V:
                return V { 0.0 };
            case Property::Cp:
                return Cp { 0.0 };
            case Property::Cv:
                return Cv { 0.0 };
            case Property::Kappa:
                return Kappa { 0.0 };
            case Property::Alpha:
                return Alpha { 0.0 };
            case Property::W:
                return W { 0.0 };
            case Property::Z:
                return Z { 0.0 };
            case Property::X:
                return X { 0.0 };
                //            case Property::Eta:
                //                return Eta{0.0};
                //            case Property::Nu:
                //                return Nu{0.0};
                //            case Property::TC:
                //                return TC{0.0};
                //            case Property::PR:
                //                return PR{0.0};
            case Property::MW:
                return MW { 0.0 };
            // Add more cases as needed
            default:
                throw std::invalid_argument("Unsupported property");
        }
    }

    inline Property mapStringToProperty(std::string propString)
    {
        using prop = std::pair<std::string_view, Property>;
        std::transform(propString.begin(), propString.end(), propString.begin(), [](unsigned char c) { return std::toupper(c); });

        static constexpr std::array<prop, 43> propMap = { { { "T", Property::T },
                                                            { "TEMPERATURE", Property::T },
                                                            { "P", Property::P },
                                                            { "PRESSURE", Property::P },
                                                            { "H", Property::H },
                                                            { "ENTHALPY", Property::H },
                                                            { "S", Property::S },
                                                            { "ENTROPY", Property::S },
                                                            { "U", Property::U },
                                                            { "INTERNAL ENERGY", Property::U },
                                                            { "A", Property::A },
                                                            { "HELMHOLTZ ENERGY", Property::A },
                                                            { "G", Property::G },
                                                            { "GIBBS ENERGY", Property::G },
                                                            { "RHO", Property::Rho },
                                                            { "DENSITY", Property::Rho },
                                                            { "V", Property::V },
                                                            { "VOLUME", Property::V },
                                                            { "VOL", Property::V },
                                                            { "CP", Property::Cp },
                                                            { "CV", Property::Cv },
                                                            { "KAPPA", Property::Kappa },
                                                            { "ISOTHERMAL COMPRESSIBILITY", Property::Kappa },
                                                            { "ALPHA", Property::Alpha },
                                                            { "THERMAL EXPANSION", Property::Alpha },
                                                            { "W", Property::W },
                                                            { "SPEED OF SOUND", Property::W },
                                                            { "Z", Property::Z },
                                                            { "COMPRESSIBILITY FACTOR", Property::Z },
                                                            { "X", Property::X },
                                                            { "Q", Property::X },
                                                            { "VAPOR QUALITY", Property::X },
                                                            { "ETA", Property::Eta },
                                                            { "DYNAMIC VISCOSITY", Property::Eta },
                                                            { "NU", Property::Nu },
                                                            { "KINEMATIC VISCOSITY", Property::Nu },
                                                            { "TC", Property::TC },
                                                            { "THERMAL CONDUCTIVITY", Property::TC },
                                                            { "PR", Property::PR },
                                                            { "PRANDTL NUMBER", Property::PR },
                                                            { "MW", Property::MW },
                                                            { "MOLAR MASS", Property::MW },
                                                            { "MOLECULAR WEIGHT", Property::MW } } };

        auto it = std::find_if(propMap.begin(), propMap.end(), [&propString](const prop& p) { return p.first == propString; });

        if (it != propMap.end()) {
            return it->second;
        }
        else {
            return Property::Undefined;
        }
    }

}    // namespace pcprops
