using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
//#include "swrace.h"

ifstream in("input.txt");
ofstream out("output.txt");

int N, M, B, W;

int main()
{
    in >> N >> M >> B >> W;




    ring leftupmost;
    leftupmost.row = N;
    leftupmost.col = M;
    for (int i = 0; i < B; i++)
    {
        //cout << anelli[i].row << "\t" << anelli[i].col << endl;
        if (anelli[i].row < leftupmost.row || anelli[i].col < leftupmost.col)
        {
            leftupmost.row = anelli[i].row;
            leftupmost.col = anelli[i].col;
        }
    }

    return 0;
}
