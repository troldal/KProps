//
// Created by kenne on 21/03/2024.
//

#pragma once

#include "PropertyTypes.hpp"

#include <variant>

namespace rng = std::ranges;

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
                                         KProps::Eta,
                                         KProps::Nu,
                                         KProps::TC,
                                         KProps::PR,
                                         KProps::MW,
                                         KProps::Phase,
                                         KProps::Undefined,
                                         KProps::Unknown>
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
                                  KProps::Eta,
                                  KProps::Nu,
                                  KProps::TC,
                                  KProps::PR,
                                  KProps::MW,
                                  KProps::Phase,
                                  KProps::Undefined,
                                  KProps::Unknown>;

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

            Eta              = 16, /**< Dynamic Viscosity */
            DynamicViscosity = 16, /**< Dynamic Viscosity (synonymous with Eta) */

            Nu                 = 17, /**< Kinematic Viscosity */
            KinematicViscosity = 17, /**< Kinematic Viscosity (synonymous with Nu) */

            TC                  = 18, /**< Thermal Conductivity */
            ThermalConductivity = 18, /**< Thermal Conductivity (synonymous with TC) */

            PR            = 19, /**< Prandtl Number */
            PrandtlNumber = 19, /**< Prandtl Number (synonymous with PR) */

            MW              = 20, /**< Molecular Weight */
            MolecularWeight = 20, /**< Molecular Weight (synonymous with MW) */
            MolarMass       = 20, /**< Molecular Weight (synonymous with MW and MolecularWeight) */

            Phase = 21, /**< Phase (e.g., liquid, vapor, two-phase) */

            Undefined = 22, /**< Placeholder for undefined properties */

            Unknown = 23 /**< Placeholder for unknown properties */
        };

    private:
        using StringToTypePair = std::pair<std::string_view, Type>;

        static constexpr std::array<StringToTypePair, 60> StringToType = { { // Basic properties
                                                                             { "T", Type::T },
                                                                             { "TEMPERATURE", Type::T },

                                                                             { "PMIN", Type::P },
                                                                             { "MINIMUM PRESSURE", Type::P },
                                                                             { "PMAX", Type::P },
                                                                             { "MAXIMUM PRESSURE", Type::P },
                                                                             { "PCRIT", Type::P },
                                                                             { "CRITICAL PRESSURE", Type::P },
                                                                             { "PTRIP", Type::P },
                                                                             { "TRIPLE POINT PRESSURE", Type::P },

                                                                             { "TMIN", Type::T },
                                                                             { "MINIMUM TEMPERATURE", Type::T },
                                                                             { "TMAX", Type::T },
                                                                             { "MAXIMUM TEMPERATURE", Type::T },
                                                                             { "TCRIT", Type::T },
                                                                             { "CRITICAL TEMPERATURE", Type::T },
                                                                             { "TTRIP", Type::T },
                                                                             { "TRIPLE POINT TEMPERATURE", Type::T },

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
                                                                             { "ETA", Type::Eta },
                                                                             { "DYNAMIC VISCOSITY", Type::Eta },
                                                                             { "NU", Type::Nu },
                                                                             { "KINEMATIC VISCOSITY", Type::Nu },
                                                                             { "TC", Type::TC },
                                                                             { "THERMAL CONDUCTIVITY", Type::TC },
                                                                             { "PR", Type::PR },
                                                                             { "PRANDTL NUMBER", Type::PR },
                                                                             // Molecular weight
                                                                             { "MW", Type::MW },
                                                                             { "MOLAR MASS", Type::MW },
                                                                             { "MOLECULAR WEIGHT", Type::MW },
                                                                             { "PHASE", Type::Phase } } };

        using TypeToStringPair = std::pair<Type, std::string_view>;

        static constexpr std::array<TypeToStringPair, 24> TypeToString = { { // Basic properties
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
                                                                             { Type::Eta, "ETA" },
                                                                             { Type::Nu, "NU" },
                                                                             { Type::TC, "TC" },
                                                                             { Type::PR, "PR" },
                                                                             // Molecular weight
                                                                             { Type::MW, "MW" },
                                                                             { Type::Phase, "PHASE" },
                                                                             // Unknown or undefined property
                                                                             { Type::Undefined, "UNDEFINED" },
                                                                             { Type::Unknown, "UNKNOWN" } } };

    public:
        Property() : BASE(Unknown { std::nan("") }) {}

        template<typename VALUE_T = double>
        explicit Property(const Type type, VALUE_T value = 0.0) : BASE(Unknown { value })
        {
            switch (type) {
                case Type::T:
                    *this = T { value };
                    break;
                case Type::P:
                    *this = P { value };
                    break;
                case Type::H:
                    *this = H { value };
                    break;
                case Type::S:
                    *this = S { value };
                    break;
                case Type::U:
                    *this = U { value };
                    break;
                case Type::A:
                    *this = A { value };
                    break;
                case Type::G:
                    *this = G { value };
                    break;
                case Type::Rho:
                    *this = Rho { value };
                    break;
                case Type::V:
                    *this = V { value };
                    break;
                case Type::Cp:
                    *this = Cp { value };
                    break;
                case Type::Cv:
                    *this = Cv { value };
                    break;
                case Type::Kappa:
                    *this = Kappa { value };
                    break;
                case Type::Alpha:
                    *this = Alpha { value };
                    break;
                case Type::W:
                    *this = W { value };
                    break;
                case Type::Z:
                    *this = Z { value };
                    break;
                case Type::X:
                    *this = X { value };
                    break;
                case Type::Eta:
                    *this = Eta { value };
                    break;
                case Type::Nu:
                    *this = Nu { value };
                    break;
                case Type::TC:
                    *this = TC { value };
                    break;
                case Type::PR:
                    *this = PR { value };
                    break;
                case Type::MW:
                    *this = MW { value };
                    break;
                case Type::Phase:
                    *this = Phase { Phase::State::Unknown };
                    break;
                case Type::Undefined:
                    *this = Undefined { std::nan("") };
                    break;
                case Type::Unknown:
                    *this = Unknown { std::nan("") };
                    break;
                // Add more cases as needed
                default:
                    throw std::invalid_argument("Unsupported property");
            }
        }

        explicit Property(const std::string& str) : Property(typeFromString(str)) {}

        // template<typename TYPE = Type>
        //     requires std::same_as<TYPE, Type> || std::same_as<TYPE, std::string>
        // [[nodiscard]]
        // auto type() const
        // {
        //     if constexpr (std::same_as<TYPE, Type>)
        //         return static_cast<Type>(index());
        //     else {
        //         auto       t  = type<Type>();
        //         const auto it = rng::find_if(TypeToString, [=](const auto& pair) { return t == pair.first; });
        //
        //         if (it != TypeToString.end())
        //             return it->second;
        //         else
        //             return TypeToString.back().second;
        //     }
        // }

        template<typename TYPE = Type>
            requires std::same_as<TYPE, Type>
        [[nodiscard]]
        auto type() const
        {
            return static_cast<Type>(index());
        }

        template<typename TYPE = Type>
            requires std::same_as<TYPE, std::string>
        [[nodiscard]]
        auto type() const
        {
            auto       t  = type<Type>();
            const auto it = rng::find_if(TypeToString, [=](const auto& pair) { return t == pair.first; });

            if (it != TypeToString.end())
                return it->second;
            else
                return TypeToString.back().second;
        }

        static Type typeFromString(std::string str)
        {
            if (str.empty()) return Type::Unknown;

            rng::transform(str, str.begin(), ::toupper);

            if (const auto it = rng::find_if(StringToType, [&](const auto& pair) { return str == pair.first; }); it != StringToType.end())
                return it->second;
            return Type::Unknown;
        }

        static std::string typeToString(Type type)
        {
            if (const auto it = rng::find_if(TypeToString, [=](const auto& pair) { return type == pair.first; }); it != TypeToString.end())
                return std::string { it->second };
            return std::string { TypeToString.back().second };
        }

        template<IsProperty PROPERTY_T>
        static std::string aliasToString()
        {
            if constexpr (std::same_as<PROPERTY_T, P>)
                return typeToString(Type::P);
            else if constexpr (std::same_as<PROPERTY_T, T>)
                return typeToString(Type::T);
            else if constexpr (std::same_as<PROPERTY_T, Rho>)
                return typeToString(Type::Rho);
            else if constexpr (std::same_as<PROPERTY_T, H>)
                return typeToString(Type::H);
            else if constexpr (std::same_as<PROPERTY_T, S>)
                return typeToString(Type::S);
            else if constexpr (std::same_as<PROPERTY_T, U>)
                return typeToString(Type::U);
            else if constexpr (std::same_as<PROPERTY_T, A>)
                return typeToString(Type::A);
            else if constexpr (std::same_as<PROPERTY_T, G>)
                return typeToString(Type::G);
            else if constexpr (std::same_as<PROPERTY_T, Cp>)
                return typeToString(Type::Cp);
            else if constexpr (std::same_as<PROPERTY_T, Cv>)
                return typeToString(Type::Cv);
            else if constexpr (std::same_as<PROPERTY_T, Kappa>)
                return typeToString(Type::Kappa);
            else if constexpr (std::same_as<PROPERTY_T, Alpha>)
                return typeToString(Type::Alpha);
            else if constexpr (std::same_as<PROPERTY_T, W>)
                return typeToString(Type::W);
            else if constexpr (std::same_as<PROPERTY_T, Eta>)
                return typeToString(Type::Eta);
            else if constexpr (std::same_as<PROPERTY_T, Nu>)
                return typeToString(Type::Nu);
            else if constexpr (std::same_as<PROPERTY_T, TC>)
                return typeToString(Type::TC);
            else if constexpr (std::same_as<PROPERTY_T, PR>)
                return typeToString(Type::PR);
            else if constexpr (std::same_as<PROPERTY_T, Z>)
                return typeToString(Type::Z);
            else if constexpr (std::same_as<PROPERTY_T, X>)
                return typeToString(Type::X);
            else if constexpr (std::same_as<PROPERTY_T, MW>)
                return typeToString(Type::MW);
            else if constexpr (std::same_as<PROPERTY_T, Phase>)
                return typeToString(Type::Phase);
            else if constexpr (std::same_as<PROPERTY_T, Undefined>)
                return typeToString(Type::Undefined);
            return typeToString(Type::Unknown);
        }

        template<IsProperty PROPERTY_T>
        static Type aliasToType()
        {
            if constexpr (std::same_as<PROPERTY_T, P>)
                return Type::P;
            else if constexpr (std::same_as<PROPERTY_T, T>)
                return Type::T;
            else if constexpr (std::same_as<PROPERTY_T, Rho>)
                return Type::Rho;
            else if constexpr (std::same_as<PROPERTY_T, H>)
                return Type::H;
            else if constexpr (std::same_as<PROPERTY_T, S>)
                return Type::S;
            else if constexpr (std::same_as<PROPERTY_T, U>)
                return Type::U;
            else if constexpr (std::same_as<PROPERTY_T, A>)
                return Type::A;
            else if constexpr (std::same_as<PROPERTY_T, G>)
                return Type::G;
            else if constexpr (std::same_as<PROPERTY_T, Cp>)
                return Type::Cp;
            else if constexpr (std::same_as<PROPERTY_T, Cv>)
                return Type::Cv;
            else if constexpr (std::same_as<PROPERTY_T, Kappa>)
                return Type::Kappa;
            else if constexpr (std::same_as<PROPERTY_T, Alpha>)
                return Type::Alpha;
            else if constexpr (std::same_as<PROPERTY_T, W>)
                return Type::W;
            else if constexpr (std::same_as<PROPERTY_T, Eta>)
                return Type::Eta;
            else if constexpr (std::same_as<PROPERTY_T, Nu>)
                return Type::Nu;
            else if constexpr (std::same_as<PROPERTY_T, TC>)
                return Type::TC;
            else if constexpr (std::same_as<PROPERTY_T, PR>)
                return Type::PR;
            else if constexpr (std::same_as<PROPERTY_T, Z>)
                return Type::Z;
            else if constexpr (std::same_as<PROPERTY_T, X>)
                return Type::X;
            else if constexpr (std::same_as<PROPERTY_T, MW>)
                return Type::MW;
            else if constexpr (std::same_as<PROPERTY_T, Phase>)
                return Type::Phase;
            else if constexpr (std::same_as<PROPERTY_T, Undefined>)
                return Type::Undefined;
            return Type::Unknown;
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Property& prop)
    {
        std::visit([&os](const auto& p) { os << p; }, prop);
        return os;
    }

}    // namespace KProps