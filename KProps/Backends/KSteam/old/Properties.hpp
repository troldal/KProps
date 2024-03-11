//
// Created by Kenneth Balslev on 23/04/2023.
//

#ifndef KSTEAM_PROPERTIES_HPP
#define KSTEAM_PROPERTIES_HPP

#include <concepts>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace KSteam
{

    /**
     * @brief A struct to hold physical and thermodynamic properties of a fluid.
     *
     * This struct is templated on the floating-point type used for the properties, such as
     * pressure, temperature, and density. It provides functions to import and export the properties
     * from/to JSON strings and to output them in a human-readable formatted string.
     *
     * @tparam T The floating-point type used for the properties.
     */
    template<std::floating_point T = double>
    struct PhaseProperties
    {
        using JSONString = std::string;

        T Pressure { 0.0 };                       // [Pa]
        T Temperature { 0.0 };                    // [K]
        T Quality { 0.0 };                        // [-]
        T Compressibility { 0.0 };                // [-]
        T FugacityCoefficient { 0.0 };            // [-]
        T IsothermalCompressibility { 0.0 };      // [1/Pa]
        T ThermalExpansionCoefficient { 0.0 };    // [1/K]
        T SaturationPressure { 0.0 };             // [Pa]
        T SaturationVolume { 0.0 };               // [m3/kg]
        T SaturationTemperature { 0.0 };          // [K]
        T Density { 0.0 };                        // [kg/m3]
        T SpecificVolume { 0.0 };                 // [m3/kg]
        T SpecificEnthalpy { 0.0 };               // [J/kg]
        T SpecificEntropy { 0.0 };                // [J/kg/K]
        T SpecificInternalEnergy { 0.0 };         // [J/kg]
        T SpecificGibbsEnergy { 0.0 };            // [J/kg]
        T SpecificHelmholtzEnergy { 0.0 };        // [J/kg]
        T Cp { 0.0 };                             // [J/kg/K]
        T Cv { 0.0 };                             // [J/kg/K]
        T SpeedOfSound { 0.0 };                   // [m/s]
        T JouleThomsonCoefficient { 0.0 };        // [K/Pa]
        T ThermalConductivity { 0.0 };            // [W/m/K]
        T DynamicViscosity { 0.0 };               // [Pa*s]
        T KinematicViscosity { 0.0 };             // [m2/s]
        T PrandtlNumber { 0.0 };                  // [-]
        T SurfaceTension { 0.0 };                 // [N/m]

    public:
        /**
         * @brief Default constructor that initializes properties with default values.
         *
         * This constructor initializes all properties with default values (usually zero).
         */
        PhaseProperties() = default;

        /**
         * @brief Constructor that initializes the object using a JSON string.
         *
         * This constructor initializes the object by parsing the property values from the given JSON
         * string and assigning them to the corresponding properties.
         *
         * @param json A JSON string containing the property values.
         */
        explicit PhaseProperties(const JSONString& json) { importJSON(json); }

        /**
         * @brief Imports property values from a JSON string.
         *
         * This function parses the property values from the given JSON string and assigns them to the
         * corresponding properties. The JSON string should contain key-value pairs where the keys are
         * the property names and the values are the corresponding property values.
         *
         * @param json A JSON string containing the property values.
         */
        inline void importJSON(const std::string& json)
        {
            rapidjson::Document document;
            document.Parse(json.c_str());

            Pressure                    = document["Pressure"].GetDouble();
            Temperature                 = document["Temperature"].GetDouble();
            Quality                     = document["Quality"].GetDouble();
            Compressibility             = document["Compressibility"].GetDouble();
            FugacityCoefficient         = document["FugacityCoefficient"].GetDouble();
            IsothermalCompressibility   = document["IsothermalCompressibility"].GetDouble();
            ThermalExpansionCoefficient = document["ThermalExpansionCoefficient"].GetDouble();
            SaturationPressure          = document["SaturationPressure"].GetDouble();
            SaturationVolume            = document["SaturationVolume"].GetDouble();
            SaturationTemperature       = document["SaturationTemperature"].GetDouble();
            Density                     = document["Density"].GetDouble();
            SpecificVolume              = document["SpecificVolume"].GetDouble();
            SpecificEnthalpy            = document["SpecificEnthalpy"].GetDouble();
            SpecificEntropy             = document["SpecificEntropy"].GetDouble();
            SpecificInternalEnergy      = document["SpecificInternalEnergy"].GetDouble();
            SpecificGibbsEnergy         = document["SpecificGibbsEnergy"].GetDouble();
            SpecificHelmholtzEnergy     = document["SpecificHelmholtzEnergy"].GetDouble();
            Cp                          = document["Cp"].GetDouble();
            Cv                          = document["Cv"].GetDouble();
            SpeedOfSound                = document["SpeedOfSound"].GetDouble();
            JouleThomsonCoefficient     = document["JouleThomsonCoefficient"].GetDouble();
            ThermalConductivity         = document["ThermalConductivity"].GetDouble();
            DynamicViscosity            = document["DynamicViscosity"].GetDouble();
            KinematicViscosity          = document["KinematicViscosity"].GetDouble();
            PrandtlNumber               = document["PrandtlNumber"].GetDouble();
            SurfaceTension              = document["SurfaceTension"].GetDouble();
        }

        /**
         * @brief Exports property values to a JSON string.
         *
         * This function creates a JSON string containing the property values as key-value pairs, where
         * the keys are the property names and the values are the corresponding property values. The
         * JSON string can be used to save or transfer the property values in a structured format.
         *
         * @return A JSON string containing the property values.
         */
        [[nodiscard]]
        inline std::string exportJSON() const
        {
            rapidjson::Document document;
            document.SetObject();

            document.AddMember("Pressure", Pressure, document.GetAllocator());
            document.AddMember("Temperature", Temperature, document.GetAllocator());
            document.AddMember("Quality", Quality, document.GetAllocator());
            document.AddMember("Compressibility", Compressibility, document.GetAllocator());
            document.AddMember("FugacityCoefficient", FugacityCoefficient, document.GetAllocator());
            document.AddMember("IsothermalCompressibility", IsothermalCompressibility, document.GetAllocator());
            document.AddMember("ThermalExpansionCoefficient", ThermalExpansionCoefficient, document.GetAllocator());
            document.AddMember("SaturationPressure", SaturationPressure, document.GetAllocator());
            document.AddMember("SaturationVolume", SaturationVolume, document.GetAllocator());
            document.AddMember("SaturationTemperature", SaturationTemperature, document.GetAllocator());
            document.AddMember("Density", Density, document.GetAllocator());
            document.AddMember("SpecificVolume", SpecificVolume, document.GetAllocator());
            document.AddMember("SpecificEnthalpy", SpecificEnthalpy, document.GetAllocator());
            document.AddMember("SpecificEntropy", SpecificEntropy, document.GetAllocator());
            document.AddMember("SpecificInternalEnergy", SpecificInternalEnergy, document.GetAllocator());
            document.AddMember("SpecificGibbsEnergy", SpecificGibbsEnergy, document.GetAllocator());
            document.AddMember("SpecificHelmholtzEnergy", SpecificHelmholtzEnergy, document.GetAllocator());
            document.AddMember("Cp", Cp, document.GetAllocator());
            document.AddMember("Cv", Cv, document.GetAllocator());
            document.AddMember("SpeedOfSound", SpeedOfSound, document.GetAllocator());
            document.AddMember("JouleThomsonCoefficient", JouleThomsonCoefficient, document.GetAllocator());
            document.AddMember("ThermalConductivity", ThermalConductivity, document.GetAllocator());
            document.AddMember("DynamicViscosity", DynamicViscosity, document.GetAllocator());
            document.AddMember("KinematicViscosity", KinematicViscosity, document.GetAllocator());
            document.AddMember("PrandtlNumber", PrandtlNumber, document.GetAllocator());
            document.AddMember("SurfaceTension", SurfaceTension, document.GetAllocator());

            rapidjson::StringBuffer                    buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            document.Accept(writer);

            return buffer.GetString();
        }

        /**
         * @brief Creates a formatted string containing the property values.
         *
         * This function creates a formatted string containing the property values, with each property
         * on a separate line and its unit in square brackets. The formatted string can be used to
         * display the property values in a human-readable form.
         *
         * @return A formatted string containing the property values.
         */
        [[nodiscard]]
        inline std::string formattedString() const
        {
            std::stringstream ss;
            ss << "Pressure:                    " << Pressure << " [Pa]" << std::endl;
            ss << "Temperature:                 " << Temperature << " [K]" << std::endl;
            ss << "Quality:                     " << Quality << " [-]" << std::endl;
            ss << "Compressibility:             " << Compressibility << " [-]" << std::endl;
            ss << "FugacityCoefficient:         " << FugacityCoefficient << " [-]" << std::endl;
            ss << "IsothermalCompressibility:   " << IsothermalCompressibility << " [1/Pa]" << std::endl;
            ss << "ThermalExpansionCoefficient: " << ThermalExpansionCoefficient << " [1/K]" << std::endl;
            ss << "SaturationPressure:          " << SaturationPressure << " [Pa]" << std::endl;
            ss << "SaturationVolume:            " << SaturationVolume << " [m3/kg]" << std::endl;
            ss << "SaturationTemperature:       " << SaturationTemperature << " [K]" << std::endl;
            ss << "Density:                     " << Density << " [kg/m3]" << std::endl;
            ss << "SpecificVolume:              " << SpecificVolume << " [m3/kg]" << std::endl;
            ss << "SpecificEnthalpy:            " << SpecificEnthalpy << " [J/kg]" << std::endl;
            ss << "SpecificEntropy:             " << SpecificEntropy << " [J/kg/K]" << std::endl;
            ss << "SpecificInternalEnergy:      " << SpecificInternalEnergy << " [J/kg]" << std::endl;
            ss << "SpecificGibbsEnergy:         " << SpecificGibbsEnergy << " [J/kg]" << std::endl;
            ss << "SpecificHelmholtzEnergy:     " << SpecificHelmholtzEnergy << " [J/kg]" << std::endl;
            ss << "Cp:                          " << Cp << " [J/kg/K]" << std::endl;
            ss << "Cv:                          " << Cv << " [J/kg/K]" << std::endl;
            ss << "SpeedOfSound:                " << SpeedOfSound << " [m/s]" << std::endl;
            ss << "JouleThomsonCoefficient:     " << JouleThomsonCoefficient << " [K/Pa]" << std::endl;
            ss << "ThermalConductivity:         " << ThermalConductivity << " [W/m/K]" << std::endl;
            ss << "DynamicViscosity:            " << DynamicViscosity << " [Pa*s]" << std::endl;
            ss << "KinematicViscosity:          " << KinematicViscosity << " [m2/s]" << std::endl;
            ss << "PrandtlNumber:               " << PrandtlNumber << " [-]" << std::endl;
            ss << "SurfaceTension:              " << SurfaceTension << " [N/m]" << std::endl;
            return ss.str();
        }

        /**
         * @brief Stream insertion operator overload to output a formatted string of the property values.
         *
         * This operator overload allows outputting a PhaseProperties object to an output stream in a
         * human-readable format. The formatted string includes the property values and their units.
         *
         * @param os The output stream to insert into.
         * @param properties The PhaseProperties object to output.
         * @return A reference to the output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const PhaseProperties<T>& properties)
        {
            os << properties.formattedString();
            return os;
        }
    };

    /**
     * @brief A type alias for a collection of PhaseProperties objects.
     *
     * FluidProperties is a type alias for a vector of PhaseProperties objects. It provides a
     * convenient way to represent multiple phases of a fluid and their respective properties.
     * This type alias is templated on the floating-point type used for the properties in
     * the PhaseProperties objects, such as pressure, temperature, and density.
     *
     * @tparam T The floating-point type used for the properties in the PhaseProperties objects.
     */
    template<std::floating_point T = double>
    using FluidProperties = std::vector<PhaseProperties<T>>;


}    // namespace KSteam

#endif    // KSTEAM_PROPERTIES_HPP
