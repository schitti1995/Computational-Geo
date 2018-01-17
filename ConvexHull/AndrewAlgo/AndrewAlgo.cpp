#include <iostream>
#include <stack>
#include "AndrewAlgo.h"

using namespace std;


int compare1(const void* a, const void* b)
{
	//return -1 if a comes before b in the sorted order, 1 if a comes after b
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;

    double c1 = (*p1).x - (*p2).x;
    double c2 = (*p1).y - (*p2).y;

    if(c1<0)        //Sort on increasing x coordinate.
        return -1;

    else if(c1==0)  //If there is a tie, sort on increasing y coordinate
        return (c2<0)?-1:1;

    else
        return 1;
}


stack<int> AndrewAlgo(Point points[], int n)
{ 
    qsort(&points[0], n, sizeof(Point), compare1);	//Sort points based on the criteria given in compare1()
    int oo;

    stack<Point> S; //We don't need the actual points for the visualizer.
    stack<int> S1;  

    //Find all points with lowest and highest x coordinates from the set P
    //We need points with the lowest and the highest y coordinates amongst these.

    double xmin = points[0].x;
    double xmax = points[n-1].x;

    //m1 -> Point# with lowest x and lowest y amongst all such x.
    //m2 -> Point# with lowest x and highest y amongst all such x.
    //m3 -> Point# with highest x and lowest y amongst all such x.
    //m4 -> Point# with highest x and highest y amongst all such x.

    int m1,m2,m3,m4;

    Point Pminmin = points[0];  
    m1 = 0;
    Point Pminmax;
    Point Pmaxmin;
    Point Pmaxmax;

    bool flag1 = true;  
    bool flag2 = false; 

    for(int i=1;i<n;i++)
    {
        if(flag1)
        {
            while(points[i].x==xmin)
			{
				i++;
				if(i==n)
					break;
			}

            i--;
            Pminmax = points[i];
            m2 = i;
        }

        flag1 = false;

        //Assign: Pmaxmin <-- points[i-1]
        if(points[i].x==xmax)
        {
            Pmaxmin = points[i];
            m3 = i;
            flag2 = true;
        }

        while(points[i].x==xmax)
		{
			i++;
			if(i==n)
				break;
		}

        //Assign: Pmaxmax <-- points[i-1] 
        if(flag2)
        {
            i--;
            Pmaxmax = points[i];
            m4 = i;
        }
    }


    //Generating the lower hull
    //Assume an imaginary line segment 'Lmin' joining Pminmin to Pmaxmin

    S.push(Pminmin);
    S1.push(m1);

    int sizeOfS = 1;

    for(int i=1;i<n;i++)
    {
        if(Orientation(Pminmin, points[i], Pmaxmin)!=1) //Process points that are strictly below the line Lmin
            continue;

        while(sizeOfS>=2)
        {
            oo = Orientation(SecondTop(S),S.top(),points[i]);
            if(oo==1)  //Points are in counterclockwise order.
            {
                break;
            }

            if(oo!=1)
			/*Points are either collinear or are in the clockwise order.
			In both cases, remove the top() of the stack (which is the middle element of the 3 elements under consideration)*/
            {
                S.pop();
                S1.pop();
                sizeOfS--;
            }
        }
        S.push(points[i]);
        S1.push(i);
        sizeOfS++;
    }

	//All points of lower hull would have been processed by now

	if(sizeOfS>=2)
	{
		oo = Orientation(SecondTop(S),S.top(),Pmaxmin);
		while(oo!=1 && sizeOfS>=2)
		{
			S.pop();
			S1.pop();
			sizeOfS--;
			oo = Orientation(SecondTop(S),S.top(),Pmaxmin);
		}
	}

    S.push(Pmaxmin);
    S1.push(m3);
    sizeOfS++;

    int t = sizeOfS;    //Count of the number of points in the lower hull.

    //Generating the Upper hull.
    //Process the points in reverse order now.
    //Assume an imaginary line 'Lmax' joining points Pminmax to Pmaxmax

    if(Pmaxmax.y != Pmaxmin.y)  //Add Pmaxmax to the stack only if it is different from Pmaxmin
    {
        S.push(Pmaxmax);
        S1.push(m4);
        sizeOfS++;
    }

    else
    {
        t = sizeOfS - 1;    //When the comparison {sizeOfS - t} is made, note that Pmaxmin is Pmaxmax.
    }

    for(int i=n-2;i>=0;i--)
    {
        if(Orientation(Pmaxmax, points[i], Pminmax)!=1)    //Process points that are strictly above the line Lmax
            continue;

        while(sizeOfS - t >= 2)
        {
            oo = Orientation(SecondTop(S),S.top(),points[i]);

            if(oo==1)  //Points are in counterclockwise order.
            {
                break;
            }

            else        
            //Points are either collinear or are in the clockwise order. In both cases, remove the top() of the stack (which is the middle element of the 3 elements under consideration)
            {
                S.pop();
                S1.pop();
                sizeOfS--;
            }
        }
        S.push(points[i]);
        S1.push(i);

        sizeOfS++;
    }

	//All points would have been processed by now.
	//Put Pminmin on stack and check if the points of the upper hull are indeed counterclockwise with Pminmin

	if(sizeOfS>=2)
	{
		oo = Orientation(SecondTop(S),S.top(),Pminmin);
		while(oo!=1 && sizeOfS >=t+2)
		{
			S.pop();
			S1.pop();
			sizeOfS--;
			oo = Orientation(SecondTop(S),S.top(),Pminmin);
		}
	}

    if(Pminmin.y != Pminmax.y)
    {
        S.push(Pminmax);
        S1.push(m2);
        sizeOfS++;
    }

    return S1;

}

