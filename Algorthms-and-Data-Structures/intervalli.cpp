using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

int main() {
  int N;

  ifstream in("input.txt");
  in >> N;
  int inizi[N];
  int fini[N];

  for (size_t i = 0; i < N; i++) {
    in >> inizi[i];
    in >> fini[i];
  }
  sort(inizi, inizi + N);
  sort(fini, fini + N);

  int diff_max = 0;
  int extrsin, extrdex;
  for (int i = 0; i < N - 1; i++) {
    int diff = inizi[i+1] - fini[i];
    if (diff > diff_max){
      diff_max = diff;
      extrsin = fini[i];
      extrdex = inizi[i+1];
    }
  }

  ofstream out("output.txt");
  if (diff_max == 0){
    out << "0";
  } else {
    out << extrsin << " " << extrdex;
  }

  return 0;
}

/*
new interval
includes whole interval
partially in interval

ends outside    1 end, 2 ends, 0 ends
ends inside



partially in unincluded interval 1 end, 2 ends, 0 ends
only in unincluded interval



*/
