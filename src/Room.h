#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <iostream>

class Point {

 public:
    int x;
    int y;
    Point(int x, int y)
        :x{ x }, y{ y }
    {}
    
    Point()
        :x{ 0 }, y{ 0 }
    {}

    Point operator+(const Point& other) const
    {
        Point res;
        res.x = x + other.x;
        res.y = y + other.y;
        return res;
    }
    Point operator-(const Point& other) const
    {
        Point res;
        res.x = x - other.x;
        res.y = y - other.y;
        return res;
    }
    Point operator*(const int factor) const
    {
        Point res;
        res.x  = x * factor;
        res.y = y * factor;
        return res;
    }
    
    bool operator!=(const Point& other) const
    {
        return x != other.x || y != other.y;
    }
};

class Room
{
public:
    Room();
    ~Room();
    Room(Point position,int width, int height)
    : position {position}, width {width}, height{height}
    {}
    Room(int width,int height,int x , int y);
    int width;
    int height;
    Point position;
	// TODO Room or Graph job ?
    Point GetSteeringNewPosition(std::vector<Room>& neibors);
    Point middle() const;
    bool intersect(const Room&) const;
    float distance(const Room&) const;

};
#endif