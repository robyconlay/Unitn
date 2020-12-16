using namespace std;
#include <iostream>
#include <fstream>

int main() {
  int N;
  ifstream in("input.txt");
  in >> N;
  int cur = 0, last = 0, mx = 0;
  for (int i = 0; i < N; i++) {
    in >> cur;
    last = max(last, last + cur);
    mx = max(mx, last);
  }

  ofstream out("output.txt");
  out << mx << endl;
  return 0;
}
