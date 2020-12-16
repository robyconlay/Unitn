using namespace std;
#include <iostream>
#include <fstream>



int vettoreUnimodulare(int start, int end, int arr[]){
  int mid = start + end/2;
  if (arr[mid] > arr[mid - 1]){
    return vettoreUnimodulare(start, mid, arr);
  }else if (arr[mid] > arr[mid + 1]){
    return vettoreUnimodulare(mid, end, arr);
  }else {
    return arr[mid];
  }
}
