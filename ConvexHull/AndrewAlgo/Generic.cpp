#include <stdlib.h>
#include<stack>
#include "Generic.h"

using namespace std;


/**
	Returns the orientation of the 3 points
	@param 	3 points for which orientation need to be checked
	@result returns an integer value

*/

int Orientation(Point p1, Point p2, Point p3)
{
    long double res = (p2.x * p3.y) - (p3.x * p2.y) - (p1.x * p3.y) + (p3.x * p1.y) + (p1.x * p2.y) - (p1.y * p2.x);

    if(res == 0)					//Points are collinear
        return 0;
    return (res>0)?1:2; 			//counterclockwise - return 1. clockwise - return 2
}



/**
    Returns the Second Point from top on the stack

    @param stack<Point> The stack
    @return The 2nd top element of the stack
*/

Point SecondTop(std::stack<Point> &S)	//Returns the next to top element of the stack
{
    Point p1 = S.top();  			//Pop the top most element
    S.pop();
    Point p2 = S.top();  			//Get the top() element which is the element we need
    S.push(p1);
    return p2;
}
