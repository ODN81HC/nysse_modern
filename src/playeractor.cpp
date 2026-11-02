#include "playeractor.hpp"

namespace StudentSide {

constexpr int kDefaultStep = 10;

PlayerActor::PlayerActor(const Interface::Location& loc): loc_(loc), removed_(false), step(kDefaultStep)
{
}

Interface::Location PlayerActor::giveLocation() const
{
    return loc_;
}

bool PlayerActor::isRemoved() const
{
    return removed_;
}

void PlayerActor::remove()
{
    removed_ = true;
}

void PlayerActor::move(const Interface::Location& loc)
{
    loc_ = loc;
}



}
