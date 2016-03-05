#include "Room.h"

#include <algorithm>
#include <iostream>
#include <numeric>

std::ostream& operator<<(std::ostream& os, const Point& pt)
{
	return os << "(" << pt.x << "," << pt.y << ")";
}

Room::Room()
	: width{ 0 }, height{ 0 }, position{ Point() } 
{}

Room::Room(int w, int h, int x, int y)
	: width{ w }, height{ h }, position{ Point(x, y) } 
{}


Room::~Room()
{
}

Point move(const Room& room1, const Room& room2)
{
	Point newPos = room1.middle() - room2.middle();
	if (newPos.x == 0 && newPos.y == 0)
	{
		//Room perfectly overlap
		newPos.x = 1;
		newPos.y = 1;
	}
	return newPos;

}

Point Room::GetSteeringNewPosition(std::vector<Room>& neighbours)
{
	Point vectorino;
	vectorino.x = 0;
	vectorino.y = 0;
	auto vectorSteering = std::accumulate(begin(neighbours), end(neighbours), vectorino, [&](const Point& acc, Room& x)
	{
		//std::cout<<position << " avec " << x.position << " Intersect : " << (intersect(x) ? "True" : "False") << " Same : " << (&x != this) << std::endl;
		return intersect(x) && (&x != this) ? acc + move(x, *this) : acc;
	});
	//std::cout << vectorSteering.x << ".." << vectorSteering.y << std::endl;
	return position + vectorSteering * -1;
}


bool Room::intersect(const Room& room) const
{
	if ((room.position.x >= position.x + width)      // trop à droite
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
	middle.x = position.x + (width / 2);
	middle.y = position.y + (height / 2);
	return middle;
}

float Room::distance(const Room& room) const
{
	auto midThis = middle();
	auto midRoom = room.middle();
	return sqrt(std::pow(midThis.x + midRoom.x, 2) + std::pow(midThis.y + midRoom.y, 2));
}

std::ostream& operator<<(std::ostream& os, const Room& room)
{
	os << '(' << room.position.x << ',' << room.position.y << ')' << '[' << room.width << ',' << room.height << ']';
	return os;
}

