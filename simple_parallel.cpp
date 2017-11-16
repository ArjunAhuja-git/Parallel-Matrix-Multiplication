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

using namespace std;

#ifdef FIL
#include <fstream>
std::ifstream cin("inputMatrix2.txt");
std::ofstream cout("output2.txt");
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

void thread_rcm(long long int* a,long long int *b, long long int **c, int i, int j,long long int n){
  c[i][j] = mult(a,b,n);
}

int main(int argc, char* argv[])
{
    long long int n;
    cin >> n;
    long long int* a[n];
    long long int* b[n];
    long long int **c = new long long int *[n];

    std::thread *compute[n];

    for(int i = 0; i < n; i++){
        a[i] = new long long int[n];
        b[i] = new long long int[n];
        c[i] = new long long int[n];
        compute[i] = new thread[n];
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> b[j][i];
        }
    }

    int count = 0;
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
        {
          compute[i][j] = thread(thread_rcm,a[i],b[j],c,i,j,n);
        }
    }

    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
        {
          compute[i][j].join();
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << c[i][j] <<" ";
        }
        cout <<endl;
    }

    return 0;
}
