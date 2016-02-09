#pragma once
class Point {
    int x;
    int y;
    Point(int x,int y)
    :x{x},y{y}
    {}
};

class Room
{
public:
    Room();
    ~Room();
    int width;
    int height;
    

};

