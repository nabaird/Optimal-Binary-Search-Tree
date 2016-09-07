#include <iostream>
#include<fstream>
#include <string>

#include "OBST.h"


using namespace std;

int main()
{
    string values[27];
    float probs[] = {8.04,1.54,3.06,3.99,12.51,2.30,1.96,5.49,7.26,0.16,0.67,4.14,2.53,7.09,7.60,2.00,0.11,6.12,6.54,9.25,2.71,0.99,1.92,0.19,1.73,0.09};
    ifstream text ("a-zWords.txt");
    string line;
    int index = 0;
    if(text.is_open())
    {
        while(text.good())
        {
            getline(text, line);
            values[index]=line;
            index++;

        }
        text.close();
    }
    else
    {
        cout<<"file is not open";
    }


    bst p;

    p.OptimizeBst(values, probs, 26);

    p.ReturnRootOrder();
}
