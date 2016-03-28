#include "Floor.h"
#include "Room.h"
#include <numeric>
#include <iostream>

Floor::Floor()
{
}

Floor::Floor(std::vector<Room> rooms)
	:rooms{ rooms },
	 minX{ },
	 maxX{ },
	 minY{ },
	 maxY{ }
{}

Floor::~Floor()
{}

void Floor::toOutput(std::ostream& os)
{
	auto arr = toArray();
	os << "toOutput" << std::endl;
    int i = minY, j = minX;
    os << "\t";
    for (auto col1 : arr[0])
        os << j++ << " ";
    os << std::endl;
	for (auto row : arr) {
        os << i++ << "\t";
		for (auto col : row)
    os << col << " ";
		os << std::endl;
	}
}

void Floor::spreadRoom()
{
	bool hasChanged;
	do
	{
		hasChanged = false;
		for (Room& room : rooms)
		{
			hasChanged |= room.GetSteeringNewPosition(rooms);
		}

	} while (hasChanged);
}

int Floor::spreadRoom(bool x)
{
    int count = 0;
	bool hasChanged;
	do
	{
		hasChanged = false;
		for (Room& room : rooms)
		{
			hasChanged |= room.GetSteeringNewPosition(rooms);
		}
        count++;
	} while (hasChanged);

    return count;
}

std::vector<std::vector<bool>> Floor::toArray()
{
	calculateBorders();
	std::vector<std::vector<bool>>
		arr( (maxY-minY), std::vector<bool>( (maxX-minX), false ) );
	for (const auto & room : rooms)
		for (unsigned int j = 0; j < room.height; ++j)
			for (unsigned int i = 0; i < room.width; ++i)
				arr[maxY - room.position.y + j][room.position.x + i - minX]
					= true;
	return arr;
}

int Floor::MinX() const noexcept
{ return minX; }

int Floor::MaxX() const noexcept
{ return maxX; }

int Floor::MinY() const noexcept
{ return minY; }

int Floor::MaxY() const noexcept
{ return maxY; }

void Floor::calculateBorders()
{
	for (const auto & room : rooms)
	{
		if(room.position.x < minX)
			minX = room.position.x;
		if(room.position.x + room.width > maxX)
			maxX = room.position.x + room.width;
		if(room.position.y - room.height < minY)
			minY = room.position.y - room.height;
		if(room.position.y > maxY)
			maxY = room.position.y;
	}
}
