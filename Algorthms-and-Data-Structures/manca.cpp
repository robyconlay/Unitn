using namespace std;
#include <iostream>
#include <fstream>

int main(int argc, char const *argv[]) {
  ifstream in("input.txt");
  ofstream out("output.txt");

  if(arr[arr.size()] == arr.size() + 1){
    cout << arr[arr.size()];
  }
  binarySearch(0, arr.size(), arr);
  return 0;


int binarySearch(int start, int end, inr arr[]){
  int mid = start+end/2;
  if (end - start <= 1){
    return mid;
  }else if (arr[mid] = mid){
    return binarySearch(mid, end, arr);
  }else if (arr[mid] > mid){
    return binarySearch(start, mid, arr);
  }
}
