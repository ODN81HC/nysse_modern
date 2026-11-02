#include "statistics.hpp"
#include <iostream>

namespace StudentSide {

Statistics::Statistics(int nysses, int passengers):
    numNysses_(nysses), numPassengers_(passengers), score_(0)
{
    try {
        if (passengers < 0) {
            throw Interface::InitError("Passengers count cannot be negative");
        }
    }  catch (const Interface::InitError& e) {
        numPassengers_ = 0;
    }
    try {
        if (nysses < 0) {
            throw Interface::InitError("Nysses count cannot be negative");
        }
    }  catch (const Interface::InitError& e) {
        numNysses_ = 0;
    }
}

void Statistics::morePassengers(int num)
{
    try {
        if (num <= 0) {
            throw Interface::InitError("Passengers added cannot be smaller or equal to 0");
        }
        else {
           numPassengers_ += num;
        }
    }  catch (const Interface::InitError& e) {
        numPassengers_ += 0;
    }
}

void Statistics::nysseRemoved()
{

}

void Statistics::newNysse()
{
    numNysses_++;
}

void Statistics::nysseLeft()
{
    try {
        numNysses_--;
        if (numNysses_ < 0){
            throw Interface::InitError("Nysses count cannot be negative");
        }
    }  catch (const Interface::InitError &e) {
        numNysses_ = 0;
    }
}

void Statistics::nysseDestroyed(int score)
{
    score_ += score;
    numNysses_--;
}

void Statistics::lessPassengers(int num)
{
    try {
        if (num < 0) {
            throw Interface::InitError("Passengers removed cannot be smaller than 0");
        }
        else if (num > numPassengers_) {
            throw Interface::InitError("Passengers removed cannot be bigger total number of passengers");
        }
        else {
            numPassengers_ -= num;
        }
    }  catch (const Interface::InitError& e) {
        numPassengers_ -= 0;
    }

}

int Statistics::getPassengerNumber() const
{
    return numPassengers_;
}

int Statistics::getNysseNumber() const
{
    return numNysses_;
}

int Statistics::getScore() const
{
    return score_;
}
}
