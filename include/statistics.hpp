#ifndef STATISTICS_H
#define STATISTICS_H

#include "istatistics.hpp"
#include "initerror.hpp"

#include <random>

namespace StudentSide {
class Statistics : public Interface::IStatistics {

public:
    explicit Statistics(int nysses, int passengers);
    Statistics() = default;
    ~Statistics() override = default;
    // StatisticIF interface
    void morePassengers(int num) override;
    void nysseRemoved() override;
    void newNysse() override;
    void nysseLeft() override;

    /**
     * @brief add score to current score
     * @param score added score
     */
    void nysseDestroyed(int score);

    /**
     * @brief Decrease the total number of passengers
     * @param num The number of passengers to remove
     */
    void lessPassengers(int num);

    /**
     * @brief get the number of passengers in real time
     * @return numPassenger_
     */
    int getPassengerNumber() const;

    /**
     * @brief get the number of buses in real time
     * @return numBuses_
     */
    int getNysseNumber() const;

    /**
     * @brief get the score in real time
     * @return score_
     */
    int getScore() const;

private:
   int numNysses_;
   int numPassengers_;
   int score_;
};
}
#endif // STATISTICS_H
