#pragma once

#include <cstddef>
#include <optional>
#include <vector>

#include "actor_variant_helpers.hpp"

namespace StudentSide
{
class ModernCity
{
public:
    ModernCity() = default;

    // Take ActorVariant and add it to the city
    void addActor(ActorVariant actor);

    // Delete all actors where isActorRemoved() is true
    void removeDeadActors();

    // Get actor
    [[nodiscard]] ActorVariant& getActor(size_t index);

    // Count non-removed actors of a specific type
    [[nodiscard]] size_t countActiveActors(ActorType type) const;
    
    // find first non-removed actor whose location isClose(target_loc, limit) and returns its location (std::optional<Location>)
    [[nodiscard]] std::optional<Interface::Location> findFirstCloseActorLocation(const Interface::Location& target_loc, int limit) const;

private:
    std::vector<ActorVariant> actors_;

};
} // namespace StudentSide