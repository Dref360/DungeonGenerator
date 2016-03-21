#include "Floor.h"
#include "Room.h"
#include <numeric>
#include <iostream>

Floor::Floor()
{
}

Floor::Floor(std::vector<Room> rooms)
	:rooms{ rooms },
	 minX{std::numeric_limits<int>::max()},
	 maxX{std::numeric_limits<int>::min()},
	 minY{std::numeric_limits<int>::max()},
	 maxY{std::numeric_limits<int>::min()}
{
}

Floor::~Floor()
{
}

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
			auto p = room.GetSteeringNewPosition(rooms);
			hasChanged |= (p != room.position);
			room.position = p;
		}

	} while (hasChanged);

	calculateBorders();
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
			auto p = room.GetSteeringNewPosition(rooms);
			hasChanged |= (p != room.position);
			room.position = p;
		}
        count++;
	} while (hasChanged);
	
	calculateBorders();

    return count;
}

std::vector<std::vector<bool>> Floor::toArray()
{
	calculateBorders();
	std::vector<std::vector<bool>> arr(maxY-minY, std::vector<bool>(maxX-minX, false));
	for (const Room & room : rooms)
		for (unsigned int j = 0; j < room.height; ++j)
			for (unsigned int i = 0; i < room.width; ++i)
			{
				std::cout << "minY = " << minY << std::endl;
				std::cout << "maxY = " << maxY << std::endl;
				std::cout << "minX = " << minX << std::endl;
				std::cout << "maxX = " << maxX << std::endl;
				std::cout << "height = " << room.height << std::endl;
				std::cout << "width = " << room.width << std::endl;
				std::cout << "max y = " << maxY-minY << " max x = " << maxX-minX << std::endl;
				std::cout << "room position : x = " << room.position.x << " y = " << room.position.y << std::endl;
				std::cout << "i = " << i << " j = " << j << std::endl;
				std::cout << "y[" << maxY - room.position.y + j << "] x[" << room.position.x + i - minX << "]" << std::endl;
				std::cout << arr[maxY - room.position.y + j].size() << std::endl;
				arr[maxY - room.position.y + j][room.position.x + i - minX] = true;
			}
	return arr;
}

int Floor::MinX() const noexcept
{ return minX; }

int Floor::MinY() const noexcept
{ return minY; }

void Floor::calculateBorders()
{
	for (const auto & room : rooms)
	{
		minX = (room.position.x < minX 
					? room.position.x 
					: minX);
		maxX = (room.position.x + room.width > maxX 
					? room.position.x + room.width 
					: maxX);
		minY = (room.position.y - room.height < minY
					? room.position.y - room.height 
					: minY);
		maxY = (room.position.y > maxY 
					? room.position.y 
					: maxY);
	}
}
