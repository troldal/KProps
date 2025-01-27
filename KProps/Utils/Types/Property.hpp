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
        class Type
        {
            enum class TypeEnum {
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

            // enum class State { Liquid, Gas, TwoPhase, Critical, Supercritical, Unknown };
            TypeEnum m_type { TypeEnum::Unknown };

            using TypeList                     = std::array<std::pair<std::string_view, TypeEnum>, 60>;
            static constexpr TypeList typeList = { { // Basic properties
                                                     { "T", TypeEnum::T },
                                                     { "TEMPERATURE", TypeEnum::T },

                                                     { "PMIN", TypeEnum::P },
                                                     { "MINIMUM PRESSURE", TypeEnum::P },
                                                     { "PMAX", TypeEnum::P },
                                                     { "MAXIMUM PRESSURE", TypeEnum::P },
                                                     { "PCRIT", TypeEnum::P },
                                                     { "CRITICAL PRESSURE", TypeEnum::P },
                                                     { "PTRIP", TypeEnum::P },
                                                     { "TRIPLE POINT PRESSURE", TypeEnum::P },

                                                     { "TMIN", TypeEnum::T },
                                                     { "MINIMUM TEMPERATURE", TypeEnum::T },
                                                     { "TMAX", TypeEnum::T },
                                                     { "MAXIMUM TEMPERATURE", TypeEnum::T },
                                                     { "TCRIT", TypeEnum::T },
                                                     { "CRITICAL TEMPERATURE", TypeEnum::T },
                                                     { "TTRIP", TypeEnum::T },
                                                     { "TRIPLE POINT TEMPERATURE", TypeEnum::T },

                                                     { "P", TypeEnum::P },
                                                     { "PRESSURE", TypeEnum::P },
                                                     { "H", TypeEnum::H },
                                                     { "ENTHALPY", TypeEnum::H },
                                                     { "S", TypeEnum::S },
                                                     { "ENTROPY", TypeEnum::S },
                                                     { "U", TypeEnum::U },
                                                     { "INTERNAL ENERGY", TypeEnum::U },
                                                     { "A", TypeEnum::A },
                                                     { "HELMHOLTZ ENERGY", TypeEnum::A },
                                                     { "G", TypeEnum::G },
                                                     { "GIBBS ENERGY", TypeEnum::G },
                                                     // Density and volume
                                                     { "RHO", TypeEnum::Rho },
                                                     { "DENSITY", TypeEnum::Rho },
                                                     { "V", TypeEnum::V },
                                                     { "VOLUME", TypeEnum::V },
                                                     { "VOL", TypeEnum::V },
                                                     // Specific heats
                                                     { "CP", TypeEnum::Cp },
                                                     { "CV", TypeEnum::Cv },
                                                     // Compressibility and expansion
                                                     { "KAPPA", TypeEnum::Kappa },
                                                     { "ISOTHERMAL COMPRESSIBILITY", TypeEnum::Kappa },
                                                     { "ALPHA", TypeEnum::Alpha },
                                                     { "THERMAL EXPANSION", TypeEnum::Alpha },
                                                     // Speed of sound and compressibility factor
                                                     { "W", TypeEnum::W },
                                                     { "SPEED OF SOUND", TypeEnum::W },
                                                     { "Z", TypeEnum::Z },
                                                     { "COMPRESSIBILITY FACTOR", TypeEnum::Z },
                                                     // Vapor quality
                                                     { "X", TypeEnum::X },
                                                     { "Q", TypeEnum::X },
                                                     { "VAPOR QUALITY", TypeEnum::X },
                                                     // Viscosity, conductivity, and Prandtl number
                                                     { "ETA", TypeEnum::Eta },
                                                     { "DYNAMIC VISCOSITY", TypeEnum::Eta },
                                                     { "NU", TypeEnum::Nu },
                                                     { "KINEMATIC VISCOSITY", TypeEnum::Nu },
                                                     { "TC", TypeEnum::TC },
                                                     { "THERMAL CONDUCTIVITY", TypeEnum::TC },
                                                     { "PR", TypeEnum::PR },
                                                     { "PRANDTL NUMBER", TypeEnum::PR },
                                                     // Molecular weight
                                                     { "MW", TypeEnum::MW },
                                                     { "MOLAR MASS", TypeEnum::MW },
                                                     { "MOLAR WEIGHT", TypeEnum::MW },
                                                     { "PHASE", TypeEnum::Phase } } };

            constexpr explicit Type(TypeEnum type) : m_type(type) {}

        public:
            static constexpr Type Temperature() { return Type { TypeEnum::Temperature }; }
            static constexpr Type Pressure() { return Type { TypeEnum::Pressure }; }
            static constexpr Type Enthalpy() { return Type { TypeEnum::Enthalpy }; }
            static constexpr Type Entropy() { return Type { TypeEnum::Entropy }; }
            static constexpr Type InternalEnergy() { return Type { TypeEnum::InternalEnergy }; }
            static constexpr Type HelmholtzEnergy() { return Type { TypeEnum::HelmholtzEnergy }; }
            static constexpr Type GibbsEnergy() { return Type { TypeEnum::GibbsEnergy }; }
            static constexpr Type Density() { return Type { TypeEnum::Density }; }
            static constexpr Type Volume() { return Type { TypeEnum::Volume }; }
            static constexpr Type Cp() { return Type { TypeEnum::Cp }; }
            static constexpr Type Cv() { return Type { TypeEnum::Cv }; }
            static constexpr Type IsothermalCompressibility() { return Type { TypeEnum::Kappa }; }
            static constexpr Type ThermalExpansion() { return Type { TypeEnum::Alpha }; }
            static constexpr Type SpeedOfSound() { return Type { TypeEnum::W }; }
            static constexpr Type CompressibilityFactor() { return Type { TypeEnum::Z }; }
            static constexpr Type VaporQuality() { return Type { TypeEnum::X }; }
            static constexpr Type DynamicViscosity() { return Type { TypeEnum::Eta }; }
            static constexpr Type KinematicViscosity() { return Type { TypeEnum::Nu }; }
            static constexpr Type ThermalConductivity() { return Type { TypeEnum::TC }; }
            static constexpr Type PrandtlNumber() { return Type { TypeEnum::PR }; }
            static constexpr Type MolecularWeight() { return Type { TypeEnum::MW }; }
            static constexpr Type Phase() { return Type { TypeEnum::Phase }; }
            static constexpr Type Undefined() { return Type { TypeEnum::Undefined }; }
            static constexpr Type Unknown() { return Type { TypeEnum::Unknown }; }

            static constexpr std::optional<Type> Create(std::string_view type)
            {
                auto it = std::ranges::find_if(typeList, [type](const auto& pair) {
                    return type.size() == pair.first.size() &&
                           std::equal(type.begin(), type.end(), pair.first.begin(), [](char ch1, char ch2) {
                               return (ch1 >= 'a' && ch1 <= 'z' ? ch1 - 'a' + 'A' : ch1) ==
                                      (ch2 >= 'a' && ch2 <= 'z' ? ch2 - 'a' + 'A' : ch2);
                           });
                });

                switch (it == typeList.end()) {
                    case false:
                        return Type(it->second);
                    default:
                        return std::nullopt;
                }
            }

            // ===== Friend declarations
            friend constexpr bool operator==(const Property::Type& lhs, const Property::Type& rhs);
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

        //template<typename TYPE = Type2>
        //    requires std::same_as<TYPE, Type2>
        [[nodiscard]]
        Type type() const
        {
            //return static_cast<Type2>(m_property.index());

            switch (m_property.index()) {
                case 0: return Type::Temperature();
                case 1: return Type::Pressure();
                case 2: return Type::Enthalpy();
                case 3: return Type::Entropy();
                case 4: return Type::InternalEnergy();
                case 5: return Type::HelmholtzEnergy();
                case 6: return Type::GibbsEnergy();
                case 7: return Type::Density();
                case 8: return Type::Volume();
                case 9: return Type::Cp();
                case 10: return Type::Cv();
                case 11: return Type::IsothermalCompressibility();
                case 12: return Type::ThermalExpansion();
                case 13: return Type::SpeedOfSound();
                case 14: return Type::CompressibilityFactor();
                case 15: return Type::VaporQuality();
                case 16: return Type::DynamicViscosity();
                case 17: return Type::KinematicViscosity();
                case 18: return Type::ThermalConductivity();
                case 19: return Type::PrandtlNumber();
                case 20: return Type::MolecularWeight();
                case 21: return Type::Phase();
                case 22: return Type::Undefined();
                case 23:
                default: return Type::Unknown();
            }

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
        static Property Phase() { return Property { Phase::Unknown }; }
        static Property Undefined(double value = 0.0) { return Property { KProps::Undefined { value } }; }
        static Property Unknown(double value = 0.0) { return Property { KProps::Unknown { value } }; }

        static std::optional<Property> Create(Type type, double value = 0.0)
        {
            if (type == Type::Temperature()) return Temperature(value);
            if (type == Type::Pressure()) return Pressure(value);
            if (type == Type::Enthalpy()) return Enthalpy(value);
            if (type == Type::Entropy()) return Entropy(value);
            if (type == Type::InternalEnergy()) return InternalEnergy(value);
            if (type == Type::HelmholtzEnergy()) return HelmholtzEnergy(value);
            if (type == Type::GibbsEnergy()) return GibbsEnergy(value);
            if (type == Type::Density()) return Density(value);
            if (type == Type::Volume()) return Volume(value);
            if (type == Type::Cp()) return Cp(value);
            if (type == Type::Cv()) return Cv(value);
            if (type == Type::IsothermalCompressibility()) return IsothermalCompressibility(value);
            if (type == Type::ThermalExpansion()) return ThermalExpansion(value);
            if (type == Type::SpeedOfSound()) return SpeedOfSound(value);
            if (type == Type::CompressibilityFactor()) return CompressibilityFactor(value);
            if (type == Type::VaporQuality()) return VaporQuality(value);
            if (type == Type::DynamicViscosity()) return DynamicViscosity(value);
            if (type == Type::KinematicViscosity()) return KinematicViscosity(value);
            if (type == Type::ThermalConductivity()) return ThermalConductivity(value);
            if (type == Type::PrandtlNumber()) return PrandtlNumber(value);
            if (type == Type::MolecularWeight()) return MolecularWeight(value);
            if (type == Type::Phase()) return Phase();
            if (type == Type::Undefined()) return Undefined(value);
            if (type == Type::Unknown()) return Unknown(value);
            return std::nullopt;
        }

        static std::optional<Property> Create(std::string_view type, double value = 0.0)
        {
            //return Create(typeFromString(type.data()), value);
            auto t = Type::Create(type);
            if (t.has_value())
                return Create(t.value(), value);

            return std::nullopt;
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Property& prop)
    {
        // std::visit([&os](const auto& p) { os << p; }, prop);
        prop.visit([&](const auto& p) { os << p; });
        return os;
    }

    constexpr bool operator==(const Property::Type& lhs, const Property::Type& rhs) { return lhs.m_type == rhs.m_type; }
    constexpr bool operator!=(const Property::Type& lhs, const Property::Type& rhs) { return !(lhs == rhs); }

    inline std::string to_string(const Property::Type& type)
    {

        if (type == Property::Type::Temperature())
            return "TEMPERATURE";
        if (type == Property::Type::Pressure())
            return "PRESSURE";
        if (type == Property::Type::Enthalpy())
            return "ENTHALPY";
        if (type == Property::Type::Entropy())
            return "ENTROPY";
        if (type == Property::Type::InternalEnergy())
            return "INTERNAL ENERGY";
        if (type == Property::Type::HelmholtzEnergy())
            return "HELMHOLTZ ENERGY";
        if (type == Property::Type::GibbsEnergy())
            return "GIBBS ENERGY";
        if (type == Property::Type::Density())
            return "DENSITY";
        if (type == Property::Type::Volume())
            return "VOLUME";
        if (type == Property::Type::Cp())
            return "CP";
        if (type == Property::Type::Cv())
            return "CV";
        if (type == Property::Type::IsothermalCompressibility())
            return "ISOTHERMAL COMPRESSIBILITY";
        if (type == Property::Type::ThermalExpansion())
            return "THERMAL EXPANSION";
        if (type == Property::Type::SpeedOfSound())
            return "SPEED OF SOUND";
        if (type == Property::Type::CompressibilityFactor())
            return "COMPRESSIBILITY FACTOR";
        if (type == Property::Type::VaporQuality())
            return "VAPOR QUALITY";
        if (type == Property::Type::DynamicViscosity())
            return "DYNAMIC VISCOSITY";
        if (type == Property::Type::KinematicViscosity())
            return "KINEMATIC VISCOSITY";
        if (type == Property::Type::ThermalConductivity())
            return "THERMAL CONDUCTIVITY";
        if (type == Property::Type::PrandtlNumber())
            return "PRANDTL NUMBER";
        if (type == Property::Type::MolecularWeight())
            return "MOLECULAR WEIGHT";
        if (type == Property::Type::Phase())
            return "PHASE";
        if (type == Property::Type::Undefined())
            return "UNDEFINED";

        return "UNKNOWN";
    }

    inline std::ostream& operator<<(std::ostream& os, const Property::Type& type)
    {
        os << to_string(type);
        return os;
    }

}    // namespace KProps