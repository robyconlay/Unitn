using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>

int main()
{
  int M,N;
  ifstream in("input.txt");
  in >> M >> N;
  ofstream out("output.txt");
  out << M+N << std::endl;

    return 0;
}
