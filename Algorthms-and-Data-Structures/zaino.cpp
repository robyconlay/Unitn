using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#ifdef EVAL
ifstream in("input.txt");
ofstream out("output.txt");
#else
istream &in(cin);
ostream &out(cout);
#endif

int zaino(int C, int N, int P[], int V[])
{
  int DP[N + 1][C + 1];
  for (size_t i = 0; i < N + 1; i++)
  {
    DP[i][0] = 0;
  }
  for (size_t c = 0; c < C + 1; c++)
  {
    DP[0][c] = 0;
  }

  for (size_t i = 1; i < N + 1; i++)
  {
    for (size_t c = 1; c < C + 1; c++)
    {
      if (P[i] <= c)
      {
        DP[i][c] = max(DP[i - 1][c - P[i]] + V[i], DP[i - 1][c]);
      }
      else
      {
        DP[i][c] = DP[i - 1][c];
      }
      cout << DP[i][c] << endl;
    }
  }
  for (size_t i = 0; i < N + 1; i++)
  {
    for (size_t j = 0; j < C + 1; j++)
    {
      cout << DP[i][j] << "\t";
    }
    cout << endl;
  }

  return DP[N][C];
}
/*
int main()
{
  int C = 0, N = 0;

  in >> C >> N;
  int P[N+1], V[N+1];
  for (size_t i = 1; i <= N; i++) {
    in >> P[i] >> V[i];
  }
  out << zaino(C, N, P, V);
  return 0;
}
*/
int C, N;

vector<int> best;

int main(void)
{

  in >> C >> N;
  best.resize(C + 1, -1);
  best[0] = 0;
  for (int i = 0; i < N; i++)
  {
    int p, v;
    in >> p >> v;
    for (int i = C; (i - p) >= 0; i--)
      if (best[i - p] > -1)
        best[i] = max(best[i], best[i - p] + v);
  }
  int res = -1;
  for (int i = 0; i <= C; i++)
    res = max(res, best[i]);
  out << res << endl;
  return 0;
}
