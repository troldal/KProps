//
// Created by Kenneth Balslev on 25/04/2023.
//

#ifndef KSTEAM_KSTEAMERROR_HPP
#define KSTEAM_KSTEAMERROR_HPP

#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

namespace KSteam {

    class KSteamError : public std::runtime_error
    {
    public:
        /**
         * @brief Constructor.
         * @param msg The error message.
         */
        explicit KSteamError(const char* msg) : std::runtime_error(msg) {};

        KSteamError(const char* msg, const char* functionName, const std::map<std::string, double>& parameters)
            : std::runtime_error(msg),
              m_functionName(functionName),
              m_parameters(parameters) {};

        [[nodiscard]] std::string functionName() const { return m_functionName; }

        [[nodiscard]] std::string parameters() const
        {
            std::stringstream ss;
            for (const auto& param : m_parameters) {
                ss << param.first << " = " << param.second << ", ";
            }
            return ss.str();
        }

    private:
        std::string                   m_functionName {};
        std::map<std::string, double> m_parameters {};
    };


}


#endif    // KSTEAM_KSTEAMERROR_HPP
