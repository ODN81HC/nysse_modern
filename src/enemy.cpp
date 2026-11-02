#include "enemy.hpp"

#include <random>

namespace StudentSide {

Enemy::Enemy(const Interface::Location& loc, std::vector<std::shared_ptr<IActor>> buses):
    loc_(loc),
    buses_(std::move(buses)),
    removed_(false)
{
//    qDebug() << "Successfully created";
}

Interface::Location Enemy::giveLocation() const
{
    return loc_;
}

bool Enemy::isRemoved() const
{
    return removed_;
}

void Enemy::remove()
{
    removed_ = true;
}

void Enemy::move(const Interface::Location& location)
{
    loc_ = location;
}

const std::vector<std::shared_ptr<Interface::IActor>>& Enemy::getBuses() const
{
    return buses_;
}

}
