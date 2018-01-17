#ifndef GENERIC_INCLUDE
#define GENERIC_INCLUDE
#include<stack>

struct Point
{
    double x,y;
};

int Orientation(Point p1, Point p2, Point p3);
Point SecondTop(std::stack<Point> &S);

#endif
