#ifndef ENEMY_HH
#define ENEMY_HH
#include <vector>
#include <memory>

#include "iactor.hpp"

namespace StudentSide {

class Enemy : public Interface::IActor

{
public:
    /**
     * @brief Constructor of the OwnActor class
     */
    Enemy(const Interface::Location& loc,
          std::vector<std::shared_ptr<IActor>> buses);
    // ActorIF interface
    Interface::Location giveLocation() const override;
    bool isRemoved() const override;
    void remove() override;
    void move(const Interface::Location& loc) override;

    /**
     * @brief get the vector of buses
     * @return the vector contained shared pointer of current busses
     */
    const std::vector<std::shared_ptr<IActor>>& getBuses() const;

private:
    Interface::Location loc_; 
    std::vector<std::shared_ptr<IActor>> buses_;
    bool removed_;
};

}

#endif // ENEMY_HH
