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
#include <thread>
#include <mutex>

#define LL long long int

using namespace std;

std::queue < pair <LL,LL> > Q;

std::mutex flock;

#ifdef FIL
#include <fstream>
std::ifstream cin("inputMatrix3.txt");
std::ofstream cout("output4.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif

long long int mult(long long int* a,long long int *b,long long int n){
    long long int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        sum+=a[i]*b[i];
    }
    return sum;
}

void thread_rcm(long long int** a,long long int **b, long long int **c,long long int n){

  std::pair <LL,LL> p;
  while(1){
    flock.lock();
    if(Q.empty()){
      flock.unlock();
      return;
    }
    p = Q.front();
    Q.pop();
    //printf("%lld %lld %d\n",p.first,p.second,Q.size());
    flock.unlock();

    c[p.first][p.second] = mult(a[p.first],b[p.second],n);
  }
}



int main(int argc, char* argv[])
{
    long long int n;
    cin >> n;
    long long int **a = new long long int *[n];
    long long int **b = new long long int *[n];
    long long int **c = new long long int *[n];

    LL th;
    cin >> th;
    std::thread *compute = new thread[th];

    // queue



    for(int i = 0; i < n; i++){
        a[i] = new long long int[n];
        b[i] = new long long int[n];
        c[i] = new long long int[n];
      //  compute[i] = new thread[n];
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
            Q.push({i,j});
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> b[j][i];
        }
    }


    int count = 0;
    for(int i = 0; i < th; i++){
       compute[i] = thread(thread_rcm,a,b,c,n);
    }

    for(int i = 0; i < th; i++){
          compute[i].join();
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << c[i][j] <<" ";
        }
        cout <<endl;
    }

    return 0;
}
