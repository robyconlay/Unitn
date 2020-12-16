using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <array>

int MAX = 1000 + 1;


int lcs(string a, string b, int i, int j){
  cout << "i: " << i << " j: " << j << endl;
  if (i == -1 || j == -1){
    return 0;
  }else if (a.at(i) == b.at(j)){
    return 1 + lcs(a, b, i-1, j-1);
  }else {
    return max(lcs(a, b, i, j-1), lcs(a, b, i-1, j));
  }
}

int lcs2(string a, string b, int i, int j){
  int nA = a.size();
  int nB = b.size();
  vector<vector<int>> DP;
  cout << "jesus1" << endl;
  DP.resize(nA);
  for (size_t i = 0; i < nA - 1; i++) {
    DP[i].resize(nB);
    if (a.at(i) == b.at(0)){
      DP[i][0] = 1;
    }else{
      DP[i][0] = 0;
    }
  }
  cout << "jesus2" << endl;

  for (size_t i = 0; i < nB- 1; i++) {
    if (b.at(i) == a.at(0)){
      DP[0][i] = 1;
    }else{
      DP[0][i] = 0;
    }
  }
  cout << "jesus3" << endl;

   for (size_t i = 1; i < nA; i++) {
     for (size_t j = 1; j < nB; j++) {
       cout << "i and j: " << i << " " << j << "\t";
       if(a.at(i) == b.at(i)){
         DP[i][j] = DP[i-1][j-1];
       }else{
         DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
       }
       cout << "DP[i][j]: " << DP[i][j]  << endl;
     }
     cout << "jesus4" << endl;
   }
   cout << "jesus5" << endl;

   return DP[nA - 1][nB - 1];
}


int main(void){
  ifstream in("input.txt");
  ofstream out("output.txt");


  string a;
  string b;

  getline(in, a);
  getline(in, b);

  cout << a << " and size " << a.size() << endl;
  cout << b << " and size " << b.size() << endl;

  out << lcs2(a, b, a.size()-1, b.size()-1);

  return 0;
}
