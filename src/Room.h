#ifndef ROOM_H
#define ROOM_H

#include <ostream>
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

	bool operator==(const Point& other) const
	{ 
		return x == other.x
			&& y == other.y;
	}
	bool operator!=(const Point& other) const
	{ return !(*this == other); }
};

class Room
{
public:
    Room();
    ~Room();
    Room(Point position,int width, int height)
    : width {width}, height{height}, position {position}
    {}
    Room(int width,int height,int x , int y);
    int width;
    int height;
    Point position;
    Point GetSteeringNewPosition(std::vector<Room>& neighbours);
    Point middle() const;
    bool intersect(const Room&) const;
    float distance(const Room&) const;
	int distanceX(const Room&) const;
	int distanceY(const Room&) const;

	bool operator==(const Room& other) const
	{ 
		return position == other.position 
			&& height   == other.height
			&& width    == other.width;
	}
	bool operator!=(const Room& other) const
	{ return !(*this == other); }

	friend std::ostream& operator<<(std::ostream& os, const Room& room);
};

#endif
