#include <vector>
#include <algorithm>
#include <utility>

#include "modern_city.hpp"

namespace StudentSide
{

void ModernCity::addActor(ActorVariant actor)
{
    actors_.push_back(std::move(actor));
}

void ModernCity::removeDeadActors()
{
    std::erase_if(actors_, [](const ActorVariant& actor) {
        return isActorRemoved(actor);
    });
}

ActorVariant& ModernCity::getActor(size_t index) {
    return actors_.at(index);
}

size_t ModernCity::countActiveActors(ActorType type) const
{
    return static_cast<size_t>(std::ranges::count_if(actors_, [type](const ActorVariant& actor){
        return !isActorRemoved(actor) && getActorType(actor) == type;
    }));
}

std::optional<Interface::Location> ModernCity::findFirstCloseActorLocation(const Interface::Location& target_loc, int limit) const
{
    const auto itr = std::ranges::find_if(actors_, [&target_loc, limit](const ActorVariant& actor){
        if (isActorRemoved(actor)) {
            return false;
        }
        const auto location_opt = getActorLocation(actor);
        return location_opt.has_value() && location_opt->isClose(target_loc, limit);
    });

    if (itr != actors_.end()) {
        return getActorLocation(*itr);
    }
    return std::nullopt;
}

}