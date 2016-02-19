#pragma once

#include "Room.h"

#include <vector>
#include <algorithm>

class Floor
{
public:
    Floor();
    Floor(std::vector<Room> rooms);
    ~Floor();
    std::vector<Room> rooms;
    std::vector<std::vector<bool>> toArray();
    void toOutput(std::ostream&);
    void spreadRoom();
private:
    int MinX();
    int MaxX();
    int MinY();
    int MaxY();

};
