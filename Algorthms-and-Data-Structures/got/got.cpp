using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "got.h"

ifstream in("input.txt");
ofstream out("output.txt");

struct casella
{
    int value = 0;
    bool visited = false;
};
int N;
int M;
vector<vector<casella>> map;
struct coord
{
    int row;
    int col;
};
//queue<coord> Q;

int minEmpty = 9999;

void calcAndPrint(bool);
void solve();
void printSolution(bool);
void visit(int x, int y, int k, int &counter);
void ripristinate(int x, int y, int k);

void solve()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (!map[i][j].visited && map[i][j].value > 0)
            {
                int counter = map[i][j].value - 1;
                map[i][j].visited = true;
                /*
                coord xy;
                xy.row = i;
                xy.col = j;
                Q.push(xy);
                */
                cout << "counter: " << counter << endl;
                cout << "up ";
                if (counter > 0)
                    visit(i - 1, j, map[i][j].value, counter); // up
                cout << "left ";
                if (counter > 0)
                    visit(i, j - 1, map[i][j].value, counter); //left
                cout << "right ";
                if (counter > 0)
                    visit(i, j + 1, map[i][j].value, counter); //right
                cout << "down ";
                if (counter > 0)
                    visit(i + 1, j, map[i][j].value, counter); //down
                if (counter > 0)
                    ripristinate(i, j, map[i][j].value);
                if (counter > 0)
                    calcAndPrint(true);
                else
                    calcAndPrint(false);
            }
        }
        cout << endl;
    }
}
/*
void visit(int row, int col, int k, int &counter)
{
    while (!Q.empty())
    {
        if (counter <= 0)
            break;
        coord punto = Q.pop();
        if (map[row][col].value == 0 && !map[row][col].visited && !(row < N && row >= 0 && col < M && col >= 0))
        {
            coord punto2;
            punto2.row = row;
            punto2.col = col;
            Q.push(punto2);
        }
    }
}
*/
void visit(int row, int col, int k, int &counter)
{
    cout << "visiting " << row << " " << col << " with k= " << k << endl;
    if (counter <= 0)
        return;
    if (!(row < N && row >= 0 && col < M && col >= 0))
        return;
    //cout << row << " " << col << " is visited: " << map[row][col].visited << endl;
    //cout << "condition is: " << (map[row][col].value == 0 && !map[row][col].visited) << endl;
    if (map[row][col].value == 0 && !map[row][col].visited)
    {
        map[row][col].visited = true;
        cout << "assigned " << k << " to " << row << " " << col << endl;
        map[row][col].value = k;
        counter--;
        //cout << "x: " << row << ", y: " << col << " is " << k << endl;
    }
    else //prevents infinite recursion
    {

        return;
    }
    cout << "up ";
    if (counter > 0)
        visit(row - 1, col, map[row][col].value, counter);
    cout << "left ";
    if (counter > 0)
        visit(row, col - 1, map[row][col].value, counter);
    cout << "right ";
    if (counter > 0)
        visit(row, col + 1, map[row][col].value, counter);
    cout << "down ";
    if (counter > 0)
        visit(row + 1, col, map[row][col].value, counter);
}

void ripristinate(int x, int y, int k) //does not take into account the presence of multiple castles with the same number
{
    cout << "call to ripristinate with k = " << k << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (map[i][j].value == k)
            {
                map[i][j].value = 0;
                cout << map[i][j].value << endl;
            }
        }
    }
}

void calcAndPrint(bool force)
{
    int empty = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (map[i][j].value == 0)
                empty++;
        }
    }
    if (empty < minEmpty || force)
    {
        minEmpty = empty;
        cout << endl;
        cout << "empty: " << empty << endl
             << endl;
        printSolution(force);
    }
}

void printSolution(bool force)
{
    //mmissing out def
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            out << map[i][j].value << "\t";
        }
        out << endl;
    }
    out << "***" << endl;
}

int main()
{
    in >> N;
    in >> M;
    map.resize(N);
    for (int i = 0; i < N; i++)
    {
        map[i].resize(M);
    }

    for (int i = 0; i < N; i++)
    {
        int k;
        for (int j = 0; j < M; j++)
        {
            in >> k;
            cout << k << "\t";
            map[i][j].value = k;
        }
        cout << endl;
    }
    cout << endl
         << endl;
    solve();
    /*
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << map[i][j].value << "\t";
        }
        cout << endl;
    }
*/
    return 0;
}