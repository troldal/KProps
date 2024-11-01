//
// Created by kenne on 29/10/2024.
//

#pragma once

#include <ranges>
#include <string>

namespace KProps
{
    class Phase
    {
        enum class State { Liquid, Gas, TwoPhase, Critical, Supercritical, Unknown };
        State m_state { State::Unknown };

        using StateList                      = std::array<std::pair<std::string_view, State>, 5>;
        static constexpr StateList stateList = { { { "LIQUID", State::Liquid },
                                                   { "GAS", State::Gas },
                                                   { "TWOPHASE", State::TwoPhase },
                                                   { "CRITICAL", State::Critical },
                                                   { "SUPERCRITICAL", State::Supercritical } } };

        constexpr explicit Phase(State state) : m_state(state) {}

    public:
        static constexpr Phase Liquid() { return Phase(State::Liquid); }
        static constexpr Phase Gas() { return Phase(State::Gas); }
        static constexpr Phase TwoPhase() { return Phase(State::TwoPhase); }
        static constexpr Phase Critical() { return Phase(State::Critical); }
        static constexpr Phase Supercritical() { return Phase(State::Supercritical); }
        static constexpr Phase Unknown() { return Phase(State::Unknown); }

        static constexpr std::optional<Phase> Create(std::string_view phase)
        {
            auto it = std::ranges::find_if(stateList, [phase](const auto& pair) {
                return phase.size() == pair.first.size() &&
                       std::equal(phase.begin(), phase.end(), pair.first.begin(), [](char ch1, char ch2) {
                           return (ch1 >= 'a' && ch1 <= 'z' ? ch1 - 'a' + 'A' : ch1) == (ch2 >= 'a' && ch2 <= 'z' ? ch2 - 'a' + 'A' : ch2);
                       });
            });

            switch (it != stateList.end()) {
                case true:
                    return Phase(it->second);
                default:
                    return std::nullopt;
            }
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