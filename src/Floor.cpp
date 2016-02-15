#include "Floor.h"
#include "Room.h"
#include <numeric>

Floor::Floor()
{
}

Floor::Floor(std::vector<Room> rooms)
	:rooms{rooms}
{
}

Floor::~Floor()
{
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
