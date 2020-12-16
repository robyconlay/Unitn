using namespace std;
#include <iostream>
#include <fstream>

puntoFisso(int start, int end, int arr[]){
  int i = start + end/2;
  if (arr[i] == i){
    return true;
  }else if (arr[i] > i){
    return puntoFisso(start, i, arr);
  }else if (arr[i] < i){
    return puntoFisso(i, end, arr);
  }
  return false;
}
