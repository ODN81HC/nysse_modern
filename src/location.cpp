#include "location.hpp"

#include <cmath>
#include <iostream>


namespace Interface
{
constexpr int kDefaultNorthCoord = 6700000;
constexpr int kDefaultEastCoord = 3500000;
constexpr int kMapOriginEast = 3327034;
constexpr int kMapOriginNorth = 6824642;
constexpr double kMapScale = 0.333333;

Location::Location() : northcoord_(), eastcoord_(), x_(), y_()
{
    giveInitLocation();
}

void Location::giveInitLocation()
{
    northcoord_ = kDefaultNorthCoord;
    eastcoord_ = kDefaultEastCoord;
    x_ = 0;
    y_ = 0;
}

Location::Location(int northcoord, int eastcoord) : Location()
{

    // LATITUDE = Y-AXIS
    // LONGITUDE = X-AXIS
    setNorthEast(northcoord, eastcoord);
}

int Location::giveX() const
{
    return x_;
}

int Location::giveY() const
{
    return y_;
}

void Location::setXY(int x, int y)
{
    x_ = x;
    y_ = y;
    eastcoord_ = EastFromX(x);
    northcoord_ = NorthFromY(y);
}

double Location::giveNorthernCoord() const
{
    return northcoord_;
}

double Location::giveEasternCoord() const
{
    return eastcoord_;
}

void Location::setNorthEast(int northcoord, int eastcoord)
{
    northcoord_ = northcoord;
    eastcoord_ = eastcoord;
    x_ = xFromEast(eastcoord);
    y_ = yFromNorth(northcoord);
}

bool Location::isClose(const Location &loc, int limit) const
{
    const int dx = loc.giveX() - giveX();
    const int dy = loc.giveY() - giveY();

    return dx*dx + dy*dy <= limit*limit;
}

int Location::xFromEast(int eastcoord)
{
    // 3327034 is kkj3-joint coordinate system point
    // at bottom left corner of small map
    // scaling is 500:1500
    return static_cast<int>((eastcoord - kMapOriginEast) * kMapScale);
}

int Location::yFromNorth(int northcoord)
{
    // 6824642 is kkj3-joint coordinate system point
    // at nottom left corner of small map
    // scaling is 500:1500
    return static_cast<int>((northcoord - kMapOriginNorth) * kMapScale);
}


int Location::EastFromX(int x)
{
    return static_cast<int>(x/kMapScale + kMapOriginEast);
}

int Location::NorthFromY(int y)
{
    return static_cast<int>(y/kMapScale + kMapOriginNorth);
}

double Location::calcDistance(const Location& loc_a, const Location& loc_b)
{


    // Approximation because distances are vesy short
    const double distance = sqrt(pow(loc_a.giveEasternCoord() - loc_b.giveEasternCoord(), 2) + pow(loc_a.giveNorthernCoord() - loc_b.giveNorthernCoord(), 2));
    return distance;
}

Location Location::calcBetween(const Location& loc_a, const Location& loc_b, double distance)
{
    // Creating a vector
    const double widthdiff = loc_b.giveNorthernCoord() - loc_a.giveNorthernCoord();
    const double heightdiff = loc_b.giveEasternCoord() - loc_a.giveEasternCoord();

    // New location is found by moving along the vector from point a for the wanted portion.
    return {static_cast<int>(loc_a.giveNorthernCoord() + widthdiff*distance), static_cast<int>(loc_a.giveEasternCoord() + heightdiff*distance)};
}

void Location::printBoth() const {
    std::cout << northcoord_ << " " << eastcoord_;
    std::cout << x_ << " " << y_;
}

bool Location::operator==(const Location &location) const
{
    // comparison operator
    // needed, for determining wether a bus stop and location are equal
    return (this->x_==location.giveX() && this->y_ == location.giveY());
}

}
