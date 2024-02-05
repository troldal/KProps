//
// Created by kenne on 31/01/2024.
//

#pragma once

#include "_external.hpp"

#include "Config.hpp"

namespace KSteam
{

    using T           = fluent::NamedType<FLOAT, struct TemperatureTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Temperature = T;

    using P        = fluent::NamedType<FLOAT, struct PressureTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Pressure = P;

    using H        = fluent::NamedType<FLOAT, struct EnthalpyTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Enthalpy = H;

    using S       = fluent::NamedType<FLOAT, struct EntropyTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Entropy = S;

    using U = fluent::NamedType<FLOAT, struct InternalEnergyTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using InternalEnergy = U;

    using A = fluent::NamedType<FLOAT, struct HelmholtzEnergyTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using HelmholtzEnergy = A;

    using G           = fluent::NamedType<FLOAT, struct GibbsEnergyTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using GibbsEnergy = G;

    using Rho     = fluent::NamedType<FLOAT, struct DensityTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Density = Rho;

    using V      = fluent::NamedType<FLOAT, struct VolumeTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Volume = V;
    using Vol    = V;

    using PSat               = fluent::NamedType<FLOAT, struct PSatTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using SaturationPressure = PSat;

    using TSat = fluent::NamedType<FLOAT, struct TSatTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using SaturationTemperature = TSat;

    using Cp = fluent::NamedType<FLOAT, struct CpTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    using Cv = fluent::NamedType<FLOAT, struct CvTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    using Kappa = fluent::NamedType<FLOAT, struct KappaTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using IsentropicExponent = Kappa;

    using W = fluent::NamedType<FLOAT, struct SpeedOfSoundTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using SpeedOfSound = W;

    using Z = fluent::NamedType<FLOAT, struct CompressibilityFactorTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using CompressibilityFactor = Z;

    using X = fluent::NamedType<FLOAT, struct VaporQualityTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Q = X;
    using VaporQuality = X;

    using Eta = fluent::NamedType<FLOAT, struct DynamicViscosityTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using DynamicViscosity = Eta;

    using Nu = fluent::NamedType<FLOAT, struct KinematicViscosityTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using KinematicViscosity = Nu;

    using TC = fluent::NamedType<FLOAT, struct ThermalConductivityTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using ThermalConductivity = TC;

    using PR = fluent::NamedType<FLOAT, struct PrandtlNumberTag, fluent::Printable, fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using PrandtlNumber = PR;

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
    concept IsSpecification =
        IsSpecificationPT<S1, S2> || IsSpecificationPH<S1, S2> || IsSpecificationPS<S1, S2> || IsSpecificationPU<S1, S2> ||
        IsSpecificationPD<S1, S2> || IsSpecificationPV<S1, S2> || IsSpecificationPX<S1, S2> || IsSpecificationTH<S1, S2> ||
        IsSpecificationTS<S1, S2> || IsSpecificationTU<S1, S2> || IsSpecificationTD<S1, S2> || IsSpecificationTV<S1, S2> ||
        IsSpecificationTX<S1, S2> || IsSpecificationHS<S1, S2> || IsSpecificationUV<S1, S2> || IsSpecificationHV<S1, S2>;


}    // namespace KSteam
