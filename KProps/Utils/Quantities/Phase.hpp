//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <string>

namespace KProps
{
    class Phase
    {
        static constexpr std::string_view strLiquid        = "LIQUID";
        static constexpr std::string_view strGas           = "GAS";
        static constexpr std::string_view strTwoPhase      = "TWOPHASE";
        static constexpr std::string_view strCritical      = "CRITICAL";
        static constexpr std::string_view strSupercritical = "SUPERCRITICAL";

        enum class State { Liquid, Gas, TwoPhase, Critical, Supercritical, Unknown };

        constexpr explicit Phase(State state) : m_state(state) {}

        constexpr explicit Phase(std::string_view state)
        {
            auto isEqualTo = [state](std::string_view str) constexpr {
                return state.size() == str.size() && std::equal(state.begin(), state.end(), str.begin(), [](char ch1, char ch2) {
                           return (ch1 >= 'a' && ch1 <= 'z' ? ch1 - 'a' + 'A' : ch1) == (ch2 >= 'a' && ch2 <= 'z' ? ch2 - 'a' + 'A' : ch2);
                       });
            };

            if (isEqualTo(strLiquid)) {
                m_state = State::Liquid;
            }
            else if (isEqualTo(strGas)) {
                m_state = State::Gas;
            }
            else if (isEqualTo(strTwoPhase)) {
                m_state = State::TwoPhase;
            }
            else if (isEqualTo(strCritical)) {
                m_state = State::Critical;
            }
            else if (isEqualTo(strSupercritical)) {
                m_state = State::Supercritical;
            }
            else {
                m_state = State::Unknown;
            }
        }

        State m_state { State::Unknown };

    public:
        static constexpr Phase Liquid() { return Phase(State::Liquid); }
        static constexpr Phase Gas() { return Phase(State::Gas); }
        static constexpr Phase TwoPhase() { return Phase(State::TwoPhase); }
        static constexpr Phase Critical() { return Phase(State::Critical); }
        static constexpr Phase Supercritical() { return Phase(State::Supercritical); }
        static constexpr Phase Unknown() { return Phase(State::Unknown); }

        static constexpr std::optional<Phase> Create(std::string_view phase)
        {
            auto isEqualTo = [phase](std::string_view str) constexpr {
                return phase.size() == str.size() && std::equal(phase.begin(), phase.end(), str.begin(), [](char ch1, char ch2) {
                           return (ch1 >= 'a' && ch1 <= 'z' ? ch1 - 'a' + 'A' : ch1) == (ch2 >= 'a' && ch2 <= 'z' ? ch2 - 'a' + 'A' : ch2);
                       });
            };

            if (isEqualTo(strLiquid)) {
                return Phase(phase);
            }
            if (isEqualTo(strGas)) {
                return Phase(phase);
            }
            if (isEqualTo(strTwoPhase)) {
                return Phase(phase);
            }
            if (isEqualTo(strCritical)) {
                return Phase(phase);
            }
            if (isEqualTo(strSupercritical)) {
                return Phase(phase);
            }

            return std::nullopt;
        }

        // ===== Friend declarations
        friend constexpr bool operator==(const Phase& lhs, const Phase& rhs);
    };

    constexpr bool operator==(const Phase& lhs, const Phase& rhs) { return lhs.m_state == rhs.m_state; }
    constexpr bool operator!=(const Phase& lhs, const Phase& rhs) { return !(lhs == rhs); }

    inline std::string to_string(const Phase& phase)
    {
        if (phase == Phase::Liquid()) {
            return "LIQUID";
        }
        if (phase == Phase::Gas()) {
            return "GAS";
        }
        if (phase == Phase::TwoPhase()) {
            return "TWOPHASE";
        }
        if (phase == Phase::Critical()) {
            return "CRITICAL";
        }
        if (phase == Phase::Supercritical()) {
            return "SUPERCRITICAL";
        }

        return "UNKNOWN";
    }

    inline std::ostream& operator<<(std::ostream& os, const Phase& phase)
    {
        os << to_string(phase);
        return os;
    }

}    // namespace KProps