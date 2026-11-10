#pragma once

#include <cstdint>
#include <variant>
#include <optional>
#include "enemy.hpp"
#include "playeractor.hpp"

namespace StudentSide {

enum class ActorType : uint8_t
{
    Empty = 0,
    Player,
    Enemy,
};

using ActorVariant = std::variant<std::monostate, PlayerActor, Enemy>;

inline ActorType getActorType(const ActorVariant& actor)
{
    return std::visit([](auto&& arg) -> ActorType
    {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, PlayerActor>)
        {
            return ActorType::Player;
        }
        else if constexpr (std::is_same_v<T, Enemy>)
        {
            return ActorType::Enemy;
        }
        else
        {
            return ActorType::Empty;
        }
    }, 
    actor);
}

inline std::optional<Interface::Location> getActorLocation(const ActorVariant& actor)
{
    return std::visit(
        [](const auto& arg) -> std::optional<Interface::Location>
        {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::monostate>)
            {
                return std::nullopt;
            }
            else
            {
                return arg.giveLocation();
            }
        },
        actor);
}

inline bool isActorRemoved(const ActorVariant& actor)
{
    return std::visit(
        [](const auto& arg) -> bool
        {
            using T = std::decay_t<decltype(arg)>;
            // If Actor is empty, consider it removed
            if constexpr (std::is_same_v<T, std::monostate>)
            {
                return true;
            }
            else
            {
                return arg.isRemoved();
            }
        },
        actor);
}

}
