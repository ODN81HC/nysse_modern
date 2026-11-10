#pragma once

#include "iactor.hpp"

namespace StudentSide {

class PlayerActor : public virtual Interface::IActor
{
public:
    explicit PlayerActor(const Interface::Location&);
    // ActorIF interface
    Interface::Location giveLocation() const override;
    void move(const Interface::Location& loc) override;
    bool isRemoved() const override;
    void remove() override;

private:
    Interface::Location loc_;
    bool removed_;
    int step;
};

}
