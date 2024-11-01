//
// Created by kenne on 21/03/2024.
//

#pragma once

#include "PropertyTypes.hpp"

#include <variant>

namespace rng = std::ranges;

namespace KProps
{

    namespace detail
    {
        using PropertyVariant = std::variant<KProps::T,
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
    }

    class Property
    {
        detail::PropertyVariant m_property;

    public:
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
        class Type2
        {
            // enum class State { Liquid, Gas, TwoPhase, Critical, Supercritical, Unknown };
            Type m_type { Type::Unknown };

            using TypeList                      = std::array<std::pair<std::string_view, Type>, 60>;
            static constexpr TypeList typeList = StringToType;

            constexpr explicit Type2(Type type) : m_type(type) {}

        public:
            static constexpr Type2 Temperature() { return Type2 { Type::Temperature }; }
            static constexpr Type2 Pressure() { return Type2 { Type::Pressure }; }
            static constexpr Type2 Enthalpy() { return Type2 { Type::Enthalpy }; }
            static constexpr Type2 Entropy() { return Type2 { Type::Entropy }; }
            static constexpr Type2 InternalEnergy() { return Type2 { Type::InternalEnergy }; }
            static constexpr Type2 HelmholtzEnergy() { return Type2 { Type::HelmholtzEnergy }; }
            static constexpr Type2 GibbsEnergy() { return Type2 { Type::GibbsEnergy }; }
            static constexpr Type2 Density() { return Type2 { Type::Density }; }
            static constexpr Type2 Volume() { return Type2 { Type::Volume }; }
            static constexpr Type2 Cp() { return Type2 { Type::Cp }; }
            static constexpr Type2 Cv() { return Type2 { Type::Cv }; }
            static constexpr Type2 IsothermalCompressibility() { return Type2 { Type::Kappa }; }
            static constexpr Type2 ThermalExpansion() { return Type2 { Type::Alpha }; }
            static constexpr Type2 SpeedOfSound() { return Type2 { Type::W }; }
            static constexpr Type2 CompressibilityFactor() { return Type2 { Type::Z }; }
            static constexpr Type2 VaporQuality() { return Type2 { Type::X }; }
            static constexpr Type2 DynamicViscosity() { return Type2 { Type::Eta }; }
            static constexpr Type2 KinematicViscosity() { return Type2 { Type::Nu }; }
            static constexpr Type2 ThermalConductivity() { return Type2 { Type::TC }; }
            static constexpr Type2 PrandtlNumber() { return Type2 { Type::PR }; }
            static constexpr Type2 MolecularWeight() { return Type2 { Type::MW }; }
            static constexpr Type2 Phase() { return Type2 { Type::Phase }; }
            static constexpr Type2 Undefined() { return Type2 { Type::Undefined }; }
            static constexpr Type2 Unknown() { return Type2 { Type::Unknown }; }

            static constexpr std::optional<Type2> Create(std::string_view type)
            {
                auto it = std::ranges::find_if(typeList, [type](const auto& pair) {
                    return type.size() == pair.first.size() &&
                           std::equal(type.begin(), type.end(), pair.first.begin(), [](char ch1, char ch2) {
                               return (ch1 >= 'a' && ch1 <= 'z' ? ch1 - 'a' + 'A' : ch1) ==
                                      (ch2 >= 'a' && ch2 <= 'z' ? ch2 - 'a' + 'A' : ch2);
                           });
                });

                switch (it != typeList.end()) {
                    case true:
                        return Type2(it->second);
                    default:
                        return std::nullopt;
                }
            }

            // ===== Friend declarations
            friend constexpr bool operator==(const Property::Type2& lhs, const Property::Type2& rhs);
        };

        Property() { m_property = KProps::Unknown { std::nan("") }; }

        template<typename TProperty>
            requires IsProperty<TProperty>
        Property(TProperty property) : m_property(property)
        {}

        template<typename TProperty>
            requires IsProperty<TProperty>
        Property& operator=(TProperty property)
        {
            m_property = property;
            return *this;
        }

        template<typename TProperty>
            requires IsProperty<TProperty>
        TProperty get() const
        {
            return std::get<TProperty>(m_property);
        }

        template<typename TYPE = Type>
            requires std::same_as<TYPE, Type>
        [[nodiscard]]
        auto type() const
        {
            return static_cast<Type>(m_property.index());
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
            else if constexpr (std::same_as<PROPERTY_T, KProps::Cp>)
                return typeToString(Type::Cp);
            else if constexpr (std::same_as<PROPERTY_T, KProps::Cv>)
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
            else if constexpr (std::same_as<PROPERTY_T, KProps::Phase>)
                return typeToString(Type::Phase);
            else if constexpr (std::same_as<PROPERTY_T, KProps::Undefined>)
                return typeToString(Type::Undefined);
            return typeToString(Type::Unknown);
        }

        template<typename Callable>
        auto visit(Callable&& callable) const
        {
            return std::visit(std::forward<Callable>(callable), m_property);
        }

        static Property Temperature(double value = 0.0) { return Property { T { value } }; }
        static Property Pressure(double value = 0.0) { return Property { P { value } }; }
        static Property Enthalpy(double value = 0.0) { return Property { H { value } }; }
        static Property Entropy(double value = 0.0) { return Property { S { value } }; }
        static Property InternalEnergy(double value = 0.0) { return Property { U { value } }; }
        static Property HelmholtzEnergy(double value = 0.0) { return Property { A { value } }; }
        static Property GibbsEnergy(double value = 0.0) { return Property { G { value } }; }
        static Property Density(double value = 0.0) { return Property { Rho { value } }; }
        static Property Volume(double value = 0.0) { return Property { V { value } }; }
        static Property Cp(double value = 0.0) { return Property { KProps::Cp { value } }; }
        static Property Cv(double value = 0.0) { return Property { KProps::Cv { value } }; }
        static Property IsothermalCompressibility(double value = 0.0) { return Property { Kappa { value } }; }
        static Property ThermalExpansion(double value = 0.0) { return Property { Alpha { value } }; }
        static Property SpeedOfSound(double value = 0.0) { return Property { W { value } }; }
        static Property CompressibilityFactor(double value = 0.0) { return Property { Z { value } }; }
        static Property VaporQuality(double value = 0.0) { return Property { X { value } }; }
        static Property DynamicViscosity(double value = 0.0) { return Property { Eta { value } }; }
        static Property KinematicViscosity(double value = 0.0) { return Property { Nu { value } }; }
        static Property ThermalConductivity(double value = 0.0) { return Property { TC { value } }; }
        static Property PrandtlNumber(double value = 0.0) { return Property { PR { value } }; }
        static Property MolecularWeight(double value = 0.0) { return Property { MW { value } }; }
        static Property Phase() { return Property { Phase::Unknown() }; }
        static Property Undefined(double value = 0.0) { return Property { KProps::Undefined { value } }; }
        static Property Unknown(double value = 0.0) { return Property { KProps::Unknown { value } }; }

        static std::optional<Property> Create(Type type, double value = 0.0)
        {
            switch (type) {
                case Type::T:
                    return Temperature(value);
                case Type::P:
                    return Pressure(value);
                case Type::H:
                    return Enthalpy(value);
                case Type::S:
                    return Entropy(value);
                case Type::U:
                    return InternalEnergy(value);
                case Type::A:
                    return HelmholtzEnergy(value);
                case Type::G:
                    return GibbsEnergy(value);
                case Type::Rho:
                    return Density(value);
                case Type::V:
                    return Volume(value);
                case Type::Cp:
                    return Cp(value);
                case Type::Cv:
                    return Cv(value);
                case Type::Kappa:
                    return IsothermalCompressibility(value);
                case Type::Alpha:
                    return ThermalExpansion(value);
                case Type::W:
                    return SpeedOfSound(value);
                case Type::Z:
                    return CompressibilityFactor(value);
                case Type::X:
                    return VaporQuality(value);
                case Type::Eta:
                    return DynamicViscosity(value);
                case Type::Nu:
                    return KinematicViscosity(value);
                case Type::TC:
                    return ThermalConductivity(value);
                case Type::PR:
                    return PrandtlNumber(value);
                case Type::MW:
                    return MolecularWeight(value);
                case Type::Phase:
                    return Phase();
                case Type::Undefined:
                    return Undefined(value);
                case Type::Unknown:
                    return Unknown(value);
                default:
                    return std::nullopt;
            }
        }

        static std::optional<Property> Create(std::string_view type, double value = 0.0)
        {
            return Create(typeFromString(type.data()), value);
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Property& prop)
    {
        // std::visit([&os](const auto& p) { os << p; }, prop);
        prop.visit([&](const auto& p) { os << p; });
        return os;
    }

    constexpr bool operator==(const Property::Type2& lhs, const Property::Type2& rhs) { return lhs.m_type == rhs.m_type; }
    constexpr bool operator!=(const Property::Type2& lhs, const Property::Type2& rhs) { return !(lhs == rhs); }

}    // namespace KProps