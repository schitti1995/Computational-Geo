#include <iostream>
#include<stack>
#include <fstream>
#include "AndrewAlgo.h"
#include<sstream>

using namespace std;

int main(int argc, char *argv[])
{

    string abc;  //This string helps give names to the output files.

    stack<int> output;  //Output stack that contains the #'s of the points in S that form the vertices of the CH(S)
    int n; //Number of points in the set S

    for(int k=1;k<argc;k++)
    {
        abc = "AndrewAlgo";

        ofstream outputFile;
        // file for printing output

        ostringstream oss;
        oss<<k;
        abc += (oss.str() + ".ch");
        const char *cstr = abc.c_str();
        //naming the output file appropriately

        outputFile.open(cstr);

        ifstream infile(argv[k]);
        //Input file

        infile >> n;

        if (n <= 0)
        {
            cout << "Enter valid Number of points" << endl;
            return 0;
        }

        Point points[n];
        long double a,b;
        int i=0;

        while ((infile >> a >> b) && (i<=n-1))
        {
            points[i].x = a;
            points[i].y = b;
            i++;
        }

        // if input size is 1 or 2, we don't have to do anything.

        if (n==1 || n==2)
        {
            outputFile<<"CH"<<endl;
            outputFile<<n<<" "<<n<<endl;

            for (int i = 0; i < n; ++i)
            {
                outputFile<<points[i].x<<" "<<points[i].y<<" "<<0<<endl;
            }

            for (int i = 0; i<n; i++)
            {
                outputFile << i << " ";
            }

            outputFile << endl;

            return 1; //return 1 since this is one boundary case we don't want
        }

        output = AndrewAlgo(points, n); //Compute the CH(S) as an ordered set of points

        outputFile<<"CH"<<endl;
        outputFile<<n<<" "<<output.size()<<endl;

        //Print the points in any order. Follow that up by the serial numbers(in the printed sequence) of the points that form the vertices of the CH(S).

        for (int i = 0; i < n; ++i)
        {
            outputFile<<points[i].x<<" "<<points[i].y<<" "<<0<<endl;
        }

        int size = output.size();

        //Output files are in .ch format. Open them in a visualizer to see the results

        for (int i = 0; i < size; ++i)
        {
            int top = output.top();
            outputFile<<top<<" ";
            output.pop();
        }
        //delete[] cstr;
        outputFile<<endl;
    }
    return 0;
}
