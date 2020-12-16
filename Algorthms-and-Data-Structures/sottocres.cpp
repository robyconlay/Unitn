using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

int N;
vector<int> best;
vector<int> value;

int main(void)
{
  ifstream in("input.txt");
  ofstream out("output.txt");

  in >> N;
  for (size_t i = 0; i < N; i++)
  {
    int el;
    in >> el;
    value.push_back(el);
  }
  best.resize(N);

  int m = 0;
  for (size_t i = 0; i < N; i++)
  {
    best[i] = value[i];
    for (size_t j = 0; j < i; j++)
    {
      if (value[j] <= value[i])
      {
        best[i] = max(best[i], best[j] + value[i]);
      }
    }
    m = max(m, best[i]);
  }
  out << m;

  return 0;
}
