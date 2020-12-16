using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <array>


int lcs(string a, string b)
{
    int nA = a.size();
    int nB = b.size();
    int DP[nA + 1][nB + 1];

    for (int i; i < nA + 1; i++)
    {
        DP[i][0] = 0;
    }
    for (int j; j < nB + 1; j++)
    {
        DP[0][j] = 0;
    }

    for (size_t i = 1; i < nA + 1; i++)
    {
        for (size_t j = 1; j < nB + 1; j++)
        {
            if (a.at(i - 1) == b.at(j - 1))
            {
                DP[i][j] = DP[i - 1][j - 1] + 1;
            }
            else
            {
                DP[i][j] = max(DP[i][j - 1], DP[i - 1][j]);
            }
        }
    }
    return DP[nA][nB];
}

int main(void)
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    string a;
    string b;

    getline(in, a);
    getline(in, b);

    cout << a << " and size " << a.size() << endl;
    cout << b << " and size " << b.size() << endl;

    out << lcs(a, b);

    return 0;
}
