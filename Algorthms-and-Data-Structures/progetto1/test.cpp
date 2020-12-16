#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  vector<vector<int>> matrix;
  vector<int> row;
  row.push_back(1);
  row.push_back(2);
  row.push_back(3);
  row.push_back(4);
  matrix.push_back(row);
  return 0;
}
