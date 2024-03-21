//
// Created by kenne on 21/03/2024.
//

#pragma once

#include "PropertyTypes.hpp"

#include <variant>

namespace KProps
{
    class Property : public std::variant<KProps::T,
                                          KProps::P,
                                          KProps::H,
                                          KProps::S,
                                          KProps::U,
                                          KProps::A,
                                          KProps::G,
                                          KProps::Rho,
                                          KProps::V,
                                          KProps::Cp,
                                          KProps::Cv,
                                          KProps::Kappa,
                                          KProps::Alpha,
                                          KProps::W,
                                          KProps::Z,
                                          KProps::X,
                                          /*Eta, Nu, TC, PR,*/
                                          KProps::MW,
                                          KProps::Phase>
    {
        using BASE = std::variant<KProps::T,
                                  KProps::P,
                                  KProps::H,
                                  KProps::S,
                                  KProps::U,
                                  KProps::A,
                                  KProps::G,
                                  KProps::Rho,
                                  KProps::V,
                                  KProps::Cp,
                                  KProps::Cv,
                                  KProps::Kappa,
                                  KProps::Alpha,
                                  KProps::W,
                                  KProps::Z,
                                  KProps::X,
                                  /*Eta, Nu, TC, PR,*/
                                  KProps::MW,
                                  KProps::Phase>;

    public:
        using BASE::BASE;

        enum class Type {
            T           = 0, /**< Temperature */
            Temperature = 0, /**< Temperature (synonymous with T) */

            P        = 1, /**< Pressure */
            Pressure = 1, /**< Pressure (synonymous with P) */

            H        = 2, /**< Enthalpy */
            Enthalpy = 2, /**< Enthalpy (synonymous with H) */

            S       = 3, /**< Entropy */
            Entropy = 3, /**< Entropy (synonymous with S) */

            U              = 4, /**< Internal Energy */
            InternalEnergy = 4, /**< Internal Energy (synonymous with U) */

            A               = 5, /**< Helmholtz Energy */
            HelmholtzEnergy = 5, /**< Helmholtz Energy (synonymous with A) */

            G           = 6, /**< Gibbs Energy */
            GibbsEnergy = 6, /**< Gibbs Energy (synonymous with G) */

            Rho     = 7, /**< Density */
            Density = 7, /**< Density (synonymous with Rho) */

            V      = 8, /**< Volume */
            Volume = 8, /**< Volume (synonymous with V) */
            Vol    = 8, /**< Volume (synonymous with V and Volume) */

            Cp = 9, /**< Specific Heat at Constant Pressure */

            Cv = 10, /**< Specific Heat at Constant Volume */

            Kappa                     = 11, /**< Isothermal Compressibility */
            IsothermalCompressibility = 11, /**< Isothermal Compressibility (synonymous with Kappa) */

            Alpha            = 12, /**< Thermal Expansion */
            ThermalExpansion = 12, /**< Thermal Expansion (synonymous with Alpha) */

            W            = 13, /**< Speed of Sound */
            SpeedOfSound = 13, /**< Speed of Sound (synonymous with W) */

            Z                     = 14, /**< Compressibility Factor */
            CompressibilityFactor = 14, /**< Compressibility Factor (synonymous with Z) */

            X            = 15, /**< Vapor Quality */
            Q            = 15, /**< Vapor Quality (synonymous with X) */
            VaporQuality = 15, /**< Vapor Quality (synonymous with X and Q) */

            //             Eta              = 16, /**< Dynamic Viscosity */
            //             DynamicViscosity = 16, /**< Dynamic Viscosity (synonymous with Eta) */
            //
            //             Nu                 = 17, /**< Kinematic Viscosity */
            //             KinematicViscosity = 17, /**< Kinematic Viscosity (synonymous with Nu) */
            //
            //             TC                  = 18, /**< Thermal Conductivity */
            //             ThermalConductivity = 18, /**< Thermal Conductivity (synonymous with TC) */
            //
            //             PR            = 19, /**< Prandtl Number */
            //             PrandtlNumber = 19, /**< Prandtl Number (synonymous with PR) */

            MW              = 16, /**< Molecular Weight */
            MolecularWeight = 16, /**< Molecular Weight (synonymous with MW) */
            MolarMass       = 16, /**< Molecular Weight (synonymous with MW and MolecularWeight) */

            Phase = 17, /**< Phase (e.g., liquid, vapor, two-phase) */

            Undefined = 99 /**< Placeholder for undefined or unknown properties */
        };

    private:
        using StringToTypePair = std::pair<std::string_view, Type>;

        static constexpr std::array<StringToTypePair, 44> StringToType = { { // Basic properties
                                                                             { "T", Type::T },
                                                                             { "TEMPERATURE", Type::T },
                                                                             { "P", Type::P },
                                                                             { "PRESSURE", Type::P },
                                                                             { "H", Type::H },
                                                                             { "ENTHALPY", Type::H },
                                                                             { "S", Type::S },
                                                                             { "ENTROPY", Type::S },
                                                                             { "U", Type::U },
                                                                             { "INTERNAL ENERGY", Type::U },
                                                                             { "A", Type::A },
                                                                             { "HELMHOLTZ ENERGY", Type::A },
                                                                             { "G", Type::G },
                                                                             { "GIBBS ENERGY", Type::G },
                                                                             // Density and volume
                                                                             { "RHO", Type::Rho },
                                                                             { "DENSITY", Type::Rho },
                                                                             { "V", Type::V },
                                                                             { "VOLUME", Type::V },
                                                                             { "VOL", Type::V },
                                                                             // Specific heats
                                                                             { "CP", Type::Cp },
                                                                             { "CV", Type::Cv },
                                                                             // Compressibility and expansion
                                                                             { "KAPPA", Type::Kappa },
                                                                             { "ISOTHERMAL COMPRESSIBILITY", Type::Kappa },
                                                                             { "ALPHA", Type::Alpha },
                                                                             { "THERMAL EXPANSION", Type::Alpha },
                                                                             // Speed of sound and compressibility factor
                                                                             { "W", Type::W },
                                                                             { "SPEED OF SOUND", Type::W },
                                                                             { "Z", Type::Z },
                                                                             { "COMPRESSIBILITY FACTOR", Type::Z },
                                                                             // Vapor quality
                                                                             { "X", Type::X },
                                                                             { "Q", Type::X },
                                                                             { "VAPOR QUALITY", Type::X },
                                                                             // Viscosity, conductivity, and Prandtl number
                                                                             // { "ETA", Type::Eta },
                                                                             // { "DYNAMIC VISCOSITY", Type::Eta },
                                                                             // { "NU", Type::Nu },
                                                                             // { "KINEMATIC VISCOSITY", Type::Nu },
                                                                             // { "TC", Type::TC },
                                                                             // { "THERMAL CONDUCTIVITY", Type::TC },
                                                                             // { "PR", Type::PR },
                                                                             // { "PRANDTL NUMBER", Type::PR },
                                                                             // Molecular weight
                                                                             { "MW", Type::MW },
                                                                             { "MOLAR MASS", Type::MW },
                                                                             { "MOLECULAR WEIGHT", Type::MW },
                                                                             { "PHASE", Type::Phase } } };

        using TypeToStringPair = std::pair<Type, std::string_view>;

        static constexpr std::array<TypeToStringPair, 44> TypeToString = { { // Basic properties
                                                                             { Type::T, "T" },
                                                                             { Type::P, "P" },
                                                                             { Type::H, "H" },
                                                                             { Type::S, "S" },
                                                                             { Type::U, "U" },
                                                                             { Type::A, "A" },
                                                                             { Type::G, "G" },
                                                                             // Density and volume
                                                                             { Type::Rho, "RHO" },
                                                                             { Type::V, "V" },
                                                                             // Specific heats
                                                                             { Type::Cp, "CP" },
                                                                             { Type::Cv, "CV" },
                                                                             // Compressibility and expansion
                                                                             { Type::Kappa, "KAPPA" },
                                                                             { Type::Alpha, "ALPHA" },
                                                                             // Speed of sound and compressibility factor
                                                                             { Type::W, "W" },
                                                                             { Type::Z, "Z" },
                                                                             // Vapor quality
                                                                             { Type::X, "X" },
                                                                             // Viscosity, conductivity, and Prandtl number
                                                                             // { "ETA", Type::Eta },
                                                                             // { "DYNAMIC VISCOSITY", Type::Eta },
                                                                             // { "NU", Type::Nu },
                                                                             // { "KINEMATIC VISCOSITY", Type::Nu },
                                                                             // { "TC", Type::TC },
                                                                             // { "THERMAL CONDUCTIVITY", Type::TC },
                                                                             // { "PR", Type::PR },
                                                                             // { "PRANDTL NUMBER", Type::PR },
                                                                             // Molecular weight
                                                                             { Type::MW, "MW" },
                                                                             { Type::Phase, "PHASE" },
                                                                             // Unknown or undefined property
                                                                             { Type::Undefined, "UNDEFINED" } } };

    public:

        explicit Property(Type t) : BASE(T{0.0})
        {
            switch (t) {
                case Type::T:
                    *this = T { 0.0 };
                break;
                case Type::P:
                    *this = P { 0.0 };
                break;
                case Type::H:
                    *this = H { 0.0 };
                break;
                case Type::S:
                    *this = S { 0.0 };
                break;
                case Type::U:
                    *this = U { 0.0 };
                break;
                case Type::A:
                    *this = A { 0.0 };
                break;
                case Type::G:
                    *this = G { 0.0 };
                break;
                case Type::Rho:
                    *this = Rho { 0.0 };
                break;
                case Type::V:
                    *this = V { 0.0 };
                break;
                case Type::Cp:
                    *this = Cp { 0.0 };
                break;
                case Type::Cv:
                    *this = Cv { 0.0 };
                break;
                case Type::Kappa:
                    *this = Kappa { 0.0 };
                break;
                case Type::Alpha:
                    *this = Alpha { 0.0 };
                break;
                case Type::W:
                    *this = W { 0.0 };
                break;
                case Type::Z:
                    *this = Z { 0.0 };
                break;
                case Type::X:
                    *this = X { 0.0 };
                break;
                    //            case Property::Eta:
                    //                return Eta{0.0};
                    //            case Property::Nu:
                    //                return Nu{0.0};
                    //            case Property::TC:
                    //                return TC{0.0};
                    //            case Property::PR:
                    //                return PR{0.0};
                case Type::MW:
                    *this = MW { 0.0 };
                break;
                case Type::Phase:
                    *this = Phase { Phase::Unknown };
                break;
                // Add more cases as needed
                default:
                    throw std::invalid_argument("Unsupported property");
            }
        }

        template <typename TYPE = Type>
        requires std::same_as<TYPE, Type> || std::same_as<TYPE, std::string>
        auto type() const
        {
            if constexpr (std::same_as<TYPE, Type>)
                return static_cast<Type>(index());
            else {
                auto t = type<Type>();
                auto it = std::find_if(TypeToString.begin(), TypeToString.end(), [=](const auto& pair) {
                    return t == pair.first;
                });

                if (it != TypeToString.end())
                    return it->second;
                else
                    return TypeToString.back().second;

            }
        }

        static Type typeFromString(const std::string& str)
        {
            auto it = std::find_if(StringToType.begin(), StringToType.end(), [&](const auto& pair) {
                return str == pair.first;
            });

            if (it != StringToType.end())
                return it->second;
            else
                return Type::Undefined;
        }

        static std::string typeAsString(Type type) {
            auto it = std::find_if(TypeToString.begin(), TypeToString.end(), [=](const auto& pair) {
                return type == pair.first;
            });

            if (it != TypeToString.end())
                return std::string{it->second};
            else
                return std::string{TypeToString.back().second};
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Property& prop)
    {
        std::visit([&os](const auto& p) { os << p; }, prop);
        return os;
    }

}    // namespace KProps