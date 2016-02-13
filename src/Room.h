#pragma once

#include <vector>

class Point {

  public:
    int x;
    int y;
    Point(int x,int y)
    :x{x},y{y}
    {}
    
    Point()
    :x{0},y{0}
    {}
    
    Point operator+(const Point& other) const
    {
        Point res;
        res.x = x + other.x;
        res.y = y + other.y;
    }
};

class Room
{
public:
    Room();
    ~Room();
    int width;
    int height;
    Point position;
	// TODO Room or Graph job ?
    Point GetSteeringNewPosition(std::vector<Room>& neibors);
    Point middle();

};

