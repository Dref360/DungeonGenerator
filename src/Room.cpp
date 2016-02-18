#include "Room.h"

#include <algorithm>
#include <iostream>

Room::Room()
: position {Point()},width {0},height{0}
{}

Room::Room(int w, int h, int x, int y)
: position {Point(x, y)}, width{w}, height{h}
{}


Room::~Room()
{
}

Point Room::GetSteeringNewPosition(std::vector<Room>& neibors)
{
    Point vectorino;
    vectorino.x = 0;
    vectorino.y = 0;
    auto vectorSteering = std::accumulate(begin(neibors),end(neibors), vectorino, [&](const Point& acc,Room& x)
    {
      return intersect(x) ? acc + (x.middle() - middle()) : acc;
    } );
    std::cout << vectorSteering.x << ".." << vectorSteering.y << std::endl;
    return position + vectorSteering * -1;
}

bool Room::intersect(const Room& room) const
{
   if((room.position.x >= position.x + width)      // trop à droite
	|| (room.position.x + room.width <= position.x) // trop à gauche
	|| (room.position.y >= position.y + height) // trop en bas
	|| (room.position.y + room.height <= position.y))  // trop en haut
          return false;
   else
          return true;
}

Point Room::middle() const
{
    Point middle;
    middle.x = position.x + (width/2);
    middle.y = position.y + (height/2);
    return middle;
}

float Room::distance(const Room& room) const
{
    auto midThis = middle();
    auto midRoom = room.middle();
    return sqrt(std::pow(midThis.x + midRoom.x,2)+std::pow(midThis.y + midRoom.y,2) );
}
