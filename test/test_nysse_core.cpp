#include <gtest/gtest.h>
#include "enemy.hpp"
#include "location.hpp"
#include "playeractor.hpp"
#include "statistics.hpp"
#include "actor_variant_helpers.hpp"
#include "modern_city.hpp"

// 1. Port of testMorePassenger from your 2019 tst_statisticstest.cpp
TEST(StatisticsTest, MorePassengers)
{
    struct TestCase
    {
        int init_passengers;
        int added_passengers;
        int expected_passengers;
    };

    const TestCase cases[] = {
        {0, 16, 16},   // Normal
        {-2, 10, 10},  // Negative init clamped to 0, then +10
        {10, 0, 10},   // Adding 0 does nothing
        {10, -5, 10},  // Adding negative does nothing
    };

    for (const auto& tc : cases)
    {
        StudentSide::Statistics stats(0, tc.init_passengers);
        stats.morePassengers(tc.added_passengers);
        EXPECT_EQ(stats.getPassengerNumber(), tc.expected_passengers);
    }
}
TEST(StatisticsTest, NysseLeft)
{
    struct TestCase
    {
        int init_nysse;
        int expected_nysse;
    };

    const TestCase cases[] = {
        {50, 49}, // Normal
        {0, 0}, // No bus
        {-10, 0} // Negative bus
    };

    for (const auto& tc : cases)
    {
        StudentSide::Statistics stats(tc.init_nysse, 0);
        stats.nysseLeft();
        EXPECT_EQ(stats.getNysseNumber(), tc.expected_nysse);
    }
}
TEST(StatisticsTest, LessPassengers)
{
    struct TestCase
    {
        int init_passengers;
        int removed_passengers;
        int expected_passengers;
    };

    const TestCase cases[] = {
        {50, 16, 34},   // Normal
        {-2, 10, 0},    // Init negative clamped to 0, then remove 10
        {10, 12, 10},   // Remove more than exist does nothing
    };

    for (const auto& tc : cases)
    {
        StudentSide::Statistics stats(0, tc.init_passengers);
        stats.lessPassengers(tc.removed_passengers);
        EXPECT_EQ(stats.getPassengerNumber(), tc.expected_passengers);
    }
}
TEST(ActorTest, PlayerAndEnemyMovement)
{
    Interface::Location start_location(6700000, 3500000);
    Interface::Location end_location(4500000, 2000000);

    StudentSide::PlayerActor test_player(start_location);
    EXPECT_FALSE(test_player.isRemoved());
    EXPECT_EQ(test_player.giveLocation(), start_location);

    test_player.move(end_location);
    EXPECT_EQ(test_player.giveLocation(), end_location);

    StudentSide::Enemy test_enemy(start_location, {});
    EXPECT_FALSE(test_enemy.isRemoved());
    EXPECT_EQ(test_enemy.giveLocation(), start_location);
}
// Stage 2 test
TEST(ActorVariantTest, TypeAndLocationGet)
{
    StudentSide::ActorVariant empty_actor;
    EXPECT_EQ(StudentSide::getActorType(empty_actor), StudentSide::ActorType::Empty);
    EXPECT_FALSE(StudentSide::getActorLocation(empty_actor).has_value());

    Interface::Location start_location(6700000, 3500000);
    StudentSide::ActorVariant player_actor = StudentSide::PlayerActor(start_location);
    EXPECT_EQ(StudentSide::getActorType(player_actor), StudentSide::ActorType::Player);
    EXPECT_TRUE(StudentSide::getActorLocation(player_actor).has_value());
    EXPECT_EQ(StudentSide::getActorLocation(player_actor), start_location);

    StudentSide::ActorVariant enemy_actor = StudentSide::Enemy(start_location, {});
    EXPECT_EQ(StudentSide::getActorType(enemy_actor), StudentSide::ActorType::Enemy);
}

TEST(ModernCityTest, AddCountFindAndRemove)
{
    StudentSide::ModernCity city;
    Interface::Location first_location(6700000, 3500000);
    Interface::Location second_location(4500000, 2000000);


    StudentSide::PlayerActor player1(first_location);
    StudentSide::PlayerActor player2(second_location);
    StudentSide::Enemy enemy(second_location, {});

    city.addActor(player1);
    city.addActor(player2);
    city.addActor(enemy);

    EXPECT_EQ(city.countActiveActors(StudentSide::ActorType::Player), 2);
    EXPECT_EQ(city.countActiveActors(StudentSide::ActorType::Enemy), 1);

    EXPECT_TRUE(city.findFirstCloseActorLocation(first_location, 100).has_value());
    EXPECT_TRUE(city.findFirstCloseActorLocation(second_location, 100).has_value());

    // Get an actor by index
    auto& actor = city.getActor(0);
    std::get<StudentSide::PlayerActor>(actor).remove();
    city.removeDeadActors();
    EXPECT_EQ(city.countActiveActors(StudentSide::ActorType::Player), 1);
}