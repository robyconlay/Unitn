using namespace std;
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

const int MAXDIM = 100;

void quicksort1(int v[], int primo, int ultimo) {
   if (primo < ultimo) {
      int p = primo;
      int u = ultimo;
      int pivot = v[ultimo];
      do {
         while ((p < u) && (v[p] <= pivot))
	   p++;
         while ((u > p) && (v[u] >= pivot))
	   u--;
         if (p < u)
	    swap(v[p],v[u]);
      } while (p < u);

      std::swap(v[p],v[ultimo]);
      quicksort1(v, primo, p-1);
      quicksort1(v, p+1, ultimo);
   }
}
void quicksort (int v[],int n)
{
  quicksort1 (v,0,n-1);
}

int main() {
  int N;
  ifstream in("input.txt");
  in >> N;
  int arr[N];
  for (size_t i = 0; i < N; i++) {
    in >> arr[i];
  }
  quicksort(arr, N);
  ofstream out("output.txt");
  for (size_t i = 0; i < N; i++) {
    out << arr[i] << " ";
  }
  return 0;
}
