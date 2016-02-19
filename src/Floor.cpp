#include "Floor.h"
#include "Room.h"
#include <numeric>
#include <iostream>

Floor::Floor()
{
}

Floor::Floor(std::vector<Room> rooms)
	:rooms{ rooms }
{
}

Floor::~Floor()
{
}

void Floor::toOutput(std::ostream& os)
{
    auto arr = toArray();
    os << "toOutput" << std::endl;
    int i = MinY(), j = MinX();
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
        for(Room& room : rooms)
        {
            auto p = room.GetSteeringNewPosition(rooms);
            hasChanged |= (p != room.position);
            room.position = p;
        }
        
    }while(hasChanged);
}

std::vector<std::vector<bool>> Floor::toArray()
{
   std::vector<std::vector<bool>> arr(abs(MinX()) + MaxX(),std::vector<bool>(abs(MinY()) + MaxY(),0));
   for(Room room : rooms)
   {
       for(int i = 0; i < room.width; i++){
           for(int j = 0; j < room.height; j++){
               arr[room.position.x + i + abs(MinX())][room.position.y + j + abs(MinY())] = true;
           }
       }
   }
   return arr;
}

int Floor::MinX()
{
    return std::accumulate(begin(rooms),end(rooms),INT32_MAX,[](const int acc,Room& room)
        {
            return std::min(acc,room.position.x);
        });
}

int Floor::MaxX()
{
    return std::accumulate(begin(rooms),end(rooms),INT32_MIN,[](const int acc,Room& room)
        {
            return std::max(acc,room.position.x + room.width);
        });
}

int Floor::MinY()
{
    return std::accumulate(begin(rooms),end(rooms),INT32_MAX,[](const int acc,Room& room)
        {
            return std::min(acc,room.position.y);
        });
}

int Floor::MaxY()
{
    return std::accumulate(begin(rooms),end(rooms),INT32_MIN,[](const int acc,Room& room)
        {
            return std::max(acc,room.position.x + room.height);
        });
}
