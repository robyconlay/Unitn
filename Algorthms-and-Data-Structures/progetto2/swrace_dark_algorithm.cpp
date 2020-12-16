using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
//#include "swrace.h"

ifstream in("input.txt");
ofstream out("output.txt");

struct ring
{
    int row;
    int col;
    bool white; //false = black, true = white
};
//vector<ring> anelli;
int N, M, B, W;

int main()
{
    in >> N >> M >> B >> W;
    //anelli.resize(B + W);
    ring anelli[B + W];
    for (int i = 0; i < B; i++)
    {
        ring anello;
        in >> anello.row >> anello.col;
        //cout << anello.row << "\t" <<  anello.col<< endl;
        anello.white = false; //it's black
        //anelli.push_back(anello);
        anelli[i] = anello;
    }
    for (int i = 0; i < W; i++)
    {
        ring anello;
        in >> anello.row >> anello.col;
        anello.white = true; //it's black
        anelli[i + B] = anello;
        //anelli.push_back(anello);
    }
    /*
    for (int i = 0; i < B + W; i++)
    {
        cout << "anello" << i << " " << anelli[i].row << "\t" << anelli[i].col << endl;
    }
*/
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
    cout << leftupmost.row << endl
         << leftupmost.col << endl;

    cout << "here";
    //go right
    int row = leftupmost.row;
    int col = leftupmost.col;
    char path[1025];
    int index = 0;
    int pathLenght = 0;
    char direction = 'R';
    while (direction == 'R')
    {
        path[index++] = direction;
        col++;
        pathLenght++;

        for (int i = 0; i < B; i++)
        {
            if (anelli[i].col == col && anelli[i].row == row)
            {
                direction = 'D';
            }
        }
    }
    while (direction == 'D')
    {
        path[index++] = direction;
        row++;
        pathLenght++;

        for (int i = 0; i < B; i++)
        {
            if (anelli[i].col == col && anelli[i].row == row)
            {
                direction = 'L';
            }
        }
    }
    while (direction == 'L')
    {
        path[index++] = direction;
        col--;
        pathLenght++;

        for (int i = 0; i < B; i++)
        {
            if (anelli[i].col == col && anelli[i].row == row)
            {
                direction = 'U';
            }
        }
    }
    while (direction == 'U')
    {
        cout << index << " " << direction << " " << row << " " << col << " " << pathLenght << endl;
        path[index++] = direction;
        row--;
        pathLenght++;

        for (int i = 0; i < B; i++)
        {
            if (anelli[i].col == col && anelli[i].row == row)
            {
                direction = 'D';
            }
        }
    }

    out << B + W << " ";
    out << pathLenght << " ";
    out << leftupmost.row << " " << leftupmost.col << " ";
    out << path;
    out << "#";

    return 0;
}
