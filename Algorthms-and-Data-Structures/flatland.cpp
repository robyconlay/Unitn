using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main() {

  int num_tri = 0;
  string orientamento;
  ifstream in("input.txt");
  in >> num_tri;
  in >> orientamento;

  char orient_char [num_tri];
  orientamento.copy(orient_char, orientamento+1);

  int i = 1;
    int v1 = rand() % (num_tri-i) + 1;
  while (/* condition */) {
    if (orient_char[v1]=='r'){
      std::move()
    }
    i+=2;
    v1 = rand() % (num_tri - i) + 1;

  }



  ofstream out("output.txt");

  return 0;
}
