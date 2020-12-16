using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

int pillole(int a)
{
  int DP[a][a];
  int mass = 0;

  for (size_t h = 0; h < a; h++)
  {
    DP[0][h] = 1;
  }
  for (size_t f = 1; f < a; f++)
  {
    for (size_t h = 0; h < a; h++)
    {
      if (h == 0)
      {
        DP[f][0] = DP[f - 1][1];
      }
      else
      {
        DP[f][h] = DP[f - 1][h + 1] + DP[f][h - 1];
      }
      mass = max(mass, DP[f][h]);
    }
  }
  for (size_t f = 0; f < a; f++)
  {
    for (size_t h = 0; h < a; h++)
    {
      cout << DP[f][h] << "\t";
    }
    cout << endl;
  }
  return mass;
}
/*
  if (H == 0)
  {
    return pillole(F - 1, 1);
  }
  else if (F == 0)
  {
    return 1;
  }
  else
  {
    return pillole(F - 1, H + 1) + pillole(F, H - 1);
  }
}
*/
int main(void)
{
  ifstream in("input.txt");
  ofstream out("output.txt");

  int a;
in >> a;

  out << pillole(a);

  return 0;
}
