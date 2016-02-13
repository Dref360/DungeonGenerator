#include "Room.h"

#include <algorithm>

Room::Room()
: position {Point()},width {0},height{0}
{}


Room::~Room()
{
}

Point Room::GetSteeringNewPosition(std::vector<Room>& neibors)
{

    return std::accumulate(begin(neibors),end(neibors), middle(), [](const Point& acc,Room& x)
    {
      return acc + x.middle();  
    } );
}

Point Room::middle()
{
    Point middle;
    middle.x = position.x + width;
    middle.y = position.y + height;
    return middle;
}

