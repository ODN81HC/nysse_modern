#include <gtest/gtest.h>
#include "enemy.hpp"
#include "location.hpp"
#include "playeractor.hpp"
#include "statistics.hpp"
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
