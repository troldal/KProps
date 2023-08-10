/*
KKKKKKKKK    KKKKKKK   SSSSSSSSSSSSSSS      tttt
K:::::::K    K:::::K SS:::::::::::::::S  ttt:::t
K:::::::K    K:::::KS:::::SSSSSS::::::S  t:::::t
K:::::::K   K::::::KS:::::S     SSSSSSS  t:::::t
KK::::::K  K:::::KKKS:::::S        ttttttt:::::ttttttt        eeeeeeeeeeee    aaaaaaaaaaaaa      mmmmmmm    mmmmmmm
  K:::::K K:::::K   S:::::S        t:::::::::::::::::t      ee::::::::::::ee  a::::::::::::a   mm:::::::m  m:::::::mm
  K::::::K:::::K     S::::SSSS     t:::::::::::::::::t     e::::::eeeee:::::eeaaaaaaaaa:::::a m::::::::::mm::::::::::m
  K:::::::::::K       SS::::::SSSSStttttt:::::::tttttt    e::::::e     e:::::e         a::::a m::::::::::::::::::::::m
  K:::::::::::K         SSS::::::::SS    t:::::t          e:::::::eeeee::::::e  aaaaaaa:::::a m:::::mmm::::::mmm:::::m
  K::::::K:::::K           SSSSSS::::S   t:::::t          e:::::::::::::::::e aa::::::::::::a m::::m   m::::m   m::::m
  K:::::K K:::::K               S:::::S  t:::::t          e::::::eeeeeeeeeee a::::aaaa::::::a m::::m   m::::m   m::::m
KK::::::K  K:::::KKK            S:::::S  t:::::t    tttttte:::::::e         a::::a    a:::::a m::::m   m::::m   m::::m
K:::::::K   K::::::KSSSSSSS     S:::::S  t::::::tttt:::::te::::::::e        a::::a    a:::::a m::::m   m::::m   m::::m
K:::::::K    K:::::KS::::::SSSSSS:::::S  tt::::::::::::::t e::::::::eeeeeeeea:::::aaaa::::::a m::::m   m::::m   m::::m
K:::::::K    K:::::KS:::::::::::::::SS     tt:::::::::::tt  ee:::::::::::::e a::::::::::aa:::am::::m   m::::m   m::::m
KKKKKKKKK    KKKKKKK SSSSSSSSSSSSSSS         ttttttttttt      eeeeeeeeeeeeee  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm

MIT License

Copyright (c) 2023 Kenneth Troldal Balslev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef KSTEAM_ERROR_HPP
#define KSTEAM_ERROR_HPP

#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

namespace KSteam
{

    /**
     * @class KSteamError
     * @brief Represents an error encountered in the KSteam class.
     *
     * This class inherits from std::runtime_error, providing the ability to
     * describe and propagate runtime errors in the KSteam class. It stores
     * information about the error message, the function name where the error
     * occurred, and a map of parameters relevant to the error.
     */
    class KSteamError : public std::runtime_error
    {
    public:

        /**
         * @brief Constructor taking a message string.
         * @param msg The error message.
         */
        explicit KSteamError(const char* msg) : std::runtime_error(msg) {};

        /**
         * @brief Constructor taking a message string and a function name.
         * @param msg The error message.
         * @param functionName The name of the function where the error occurred.
         */
        KSteamError(const char* msg, const char* functionName, const std::map<std::string, double>& parameters)
            : std::runtime_error(msg),
              m_functionName(functionName),
              m_parameters(parameters) {};

        /**
         * @brief This function is the description of the functionName.
         *
         * It is a const member function and does not modify the state of the object.
         * The function does not return any example code.
         *
         * @return The name of the function where the error occurred.
         */
        [[nodiscard]] std::string functionName() const { return m_functionName; }

        /**
         * @brief Get the value of the parameters.
         *
         * This function returns the current value of the parameters.
         *
         * @return The value of the parameters.
         */
        [[nodiscard]] std::string parameters() const
        {
            std::stringstream ss;
            for (const auto& param : m_parameters) {
                ss << param.first << " = " << param.second << ", ";
            }
            return ss.str();
        }

    private:
        std::string                   m_functionName {};   ///< The name of the function where the error occurred.
        std::map<std::string, double> m_parameters {};    ///< A map of parameters relevant to the error.
    };
}    // namespace XLSteam

#endif    // KSTEAM_ERROR_HPP
