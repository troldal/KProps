//
// Created by kenne on 02/11/2024.
//

#pragma once

#include <array>
#include <cstdint>
#include <fixed_string.hpp>
#include <iostream>
#include <optional>
#include <string_view>

namespace troldal {
    /**
     * @brief Forward declaration of StringEnum class template.
     *
     * @tparam Derived The derived class type.
     * @tparam Values The fixed string values representing the enum values.
     */
    template<typename Derived, fixstr::fixed_string... Values>
    class StringEnum;

    /**
     * @brief Converts an StringEnum object to a std::string.
     *
     * @tparam Derived The derived class type.
     * @tparam Values The fixed string values representing the enum values.
     * @param enumValue The StringEnum object to convert.
     * @return std::string The string representation of the enum value.
     */
    template<typename Derived, fixstr::fixed_string... Values>
    std::string to_string(const StringEnum<Derived, Values...> &enumValue);

    /**
     * @brief Base class template for creating enum-like classes with string values.
     *
     * @tparam Derived The derived class type.
     * @tparam Values The fixed string values representing the enum values.
     */
    template<typename Derived, fixstr::fixed_string... Values>
    class StringEnum {
    public:

        /**
         * @brief Equality comparison operator.
         *
         * @param rhs The right-hand side StringEnum object to compare.
         * @return true if the values are equal, false otherwise.
         */
        constexpr bool operator==(const StringEnum &rhs) const { return m_value == rhs.m_value; }

        /**
         * @brief Inequality comparison operator.
         *
         * @param rhs The right-hand side StringEnum object to compare.
         * @return true if the values are not equal, false otherwise.
         */
        constexpr bool operator!=(const StringEnum &rhs) const { return !(*this == rhs); }

        /**
         * @brief Friend function to convert StringEnum to std::string.
         *
         * @param enumValue The StringEnum object to convert.
         * @return std::string The string representation of the enum value.
         */
        friend std::string to_string<Derived, Values...>(const StringEnum &enumValue);

        /**
         * @brief Stream output operator for StringEnum.
         *
         * @param os The output stream.
         * @param enum_ The StringEnum object to output.
         * @return std::ostream& The output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const StringEnum &enum_) { return os << enum_.m_value; }

        /**
         * @brief Conversion operator to int64_t.
         *
         * @return int64_t The index of the enum value in the value array.
         */
        constexpr operator int64_t() const {
            auto it = std::ranges::find_if(s_valueArray, [value = m_value](const auto &item) { return value == item; });
            return std::distance(s_valueArray.begin(), it);
        }

        /**
         * @brief Creates an StringEnum object from a string view.
         *
         * @param col The string view representing the enum value.
         * @return std::optional<StringEnum> The created StringEnum object, or std::nullopt if the value is invalid.
         */
        static constexpr std::optional<StringEnum> Create(std::string_view col) {
            auto it = std::ranges::find_if(s_valueArray, [col](const auto &item) {
                return col.size() == item.size() &&
                       std::equal(col.begin(), col.end(), item.begin(), [](char ch1, char ch2) {
                           return (ch1 >= 'a' && ch1 <= 'z' ? ch1 - 'a' + 'A' : ch1) ==
                                  (ch2 >= 'a' && ch2 <= 'z' ? ch2 - 'a' + 'A' : ch2);
                       });
            });
            switch (it == s_valueArray.end()) {
                case false:
                    return StringEnum{*it};
                default:
                    return std::nullopt;
            }
        }

    protected:
        /**
         * @brief Protected constructor to allow instantiation by derived classes only.
         *
         * @param name The string view representing the enum value.
         */
        constexpr explicit StringEnum(std::string_view name) : m_value(name) {}

        std::string_view m_value; ///< Internal string name to identify the enum value.
        static constexpr std::array<std::string_view, sizeof...(Values)> s_valueArray = {
            Values...}; ///< Array of enum values.
    };

    /**
     * @brief Converts an StringEnum object to a std::string.
     *
     * @tparam Derived The derived class type.
     * @tparam Names The fixed string values representing the enum values.
     * @param enumValue The StringEnum object to convert.
     * @return std::string The string representation of the enum value.
     */
    template<typename Derived, fixstr::fixed_string... Names>
    std::string to_string(const StringEnum<Derived, Names...> &enumValue) {
        return std::string{enumValue.m_value};
    }
} // namespace troldal