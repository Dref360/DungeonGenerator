#include "Room.h"
#include <numeric>
#include <algorithm>

Room::Room()
: position {Point()},width {0},height{0}
{}

Room::Room(int w, int h, int x, int y)
: position {Point(x, y)}, width{w}, height{h}
{}

Room::~Room()
{
}

Point Room::GetSteeringNewPosition(std::vector<Room>& neighbors)
{

    return std::accumulate(begin(neighbors),end(neighbors), middle(), [](const Point& acc,Room& x)
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

