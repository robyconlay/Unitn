using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>

int main()
{
  int N;
  int turni = 0;

  ifstream in("input.txt");
  ofstream out("output.txt");

  in >> N;
  int arr[N];
  for (int i = 0; i < N; i++) {
    in >> arr[i];
  }

  if (N <= 1){
    out << arr;
    return 0;
  }
  int swapsum = 0;
  int swapnum = 0;
  int unordered[N];
  int j = 0;
  bool noswap = false;
  for (int i = 0; i < N; i++) {
    //cout << arr[i] << " " << i+1 << endl;
    //cout << "j = " << j << endl;
    if (arr[i] != (i+1)){
      if (arr[arr[i] - 1] == (i+1)){
        swapsum += arr[i];
        swapnum++;
        cout << arr[i] << " " << i + 1 << " " << arr[arr[i] - 1] << endl;
      }else {
        unordered[j] = arr[i];
        j++;
        turni++;
        noswap = true;
      }
      //cout << "entered" << endl;
    }
  }
  j--;
  turni += (swapnum / 2);
  if (noswap) turni--;

  int sum1 = 0;
  int sum2 = 0;
  int sum3 = 0;
  int sum4 = 0;
  int num_min = 1000000;
  for (int i = 0; i <= j; i++) {
    sum1 += unordered[i];
    num_min = min(num_min, unordered[i]);

    sum3 += (1 + unordered[i]);
  }
  if (sum1 != 0 && j >= 0){
    sum2 = sum1;
    sum1 += ((j - 1) + swapsum);
    sum2 += ((num_min * (j-1)) + swapsum);
    sum3 += ((num_min + 1) + swapsum);
  }
  cout << "j = " << j << endl;
  cout << "min = " << num_min << endl;
  cout << "swapsum = " << swapsum << endl;
  cout << "sums = " << sum1 << " " << sum2 << " " << sum3 << endl;
  out << turni << " " << max(swapsum, min(sum2, sum3));

    return 0;
}
