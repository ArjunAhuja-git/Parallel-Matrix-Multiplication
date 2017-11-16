#include <algorithm>
#include <assert.h>
#include <bitset>
#include <complex>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <limits.h>
#include <list>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <fstream>
#include <iostream>
#include <time.h>
#include <random>
using namespace std;

#define LL long long int

int main(){
  std::ofstream fobj("inputMatrix2.txt");
  long long int n;
  cin >> n;
  fobj << n;
  srand(time(NULL));


  for(LL i=0;i<2;i++){
  fobj << "\n";
  for(LL i=0;i<n;i++){
    for(LL j=0;j<n;j++){
      fobj << rand()%100000 << " ";
    }
    fobj <<  "\n";
  }
}
  return 0;
}
