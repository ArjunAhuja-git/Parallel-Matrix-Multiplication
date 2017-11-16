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

using namespace std;

#ifdef JAM
#include <fstream>
std::ifstream cin("inputMatrix.txt");
std::ofstream cout("output.txt");
#else
#include <iostream>
using std::cin;
using std::cout;
#endif

long long int mult(long long int* a,long long int *b,int n){
    long long int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        sum+=a[i]*b[i];
    }
    return sum;
}

int main(int argc, char* argv[])
{
    long long int n;
    cin >> n;
    long long int* a[n];
    long long int* b[n];
    long long int* c[n];
    printf("%lld\n",n);
    for(int i = 0; i < n; i++){
        a[i] = new long long int[n];
        b[i] = new long long int[n];
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> b[j][i];
        }
    }
    for(int i = 0; i < n; i++){
        c[i] = new long long int[n];
        for (int j = 0; j < n; j++)
        {
            cout << mult(a[i],b[j],n) << " ";
        }
        cout << "\n";
    }
    return 0;
}
