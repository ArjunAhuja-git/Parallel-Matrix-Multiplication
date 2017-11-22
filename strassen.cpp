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

#define LL long long int

#ifdef FIL
#include <fstream>
std::ifstream cin("inputMatrix.txt");
std::ofstream cout("outputooo.txt");
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

void multiplyMatrics(long long int** a,long long int** b,long long int** c,int size){
    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++)
        {
            c[i][j] = mult(a[i],b[j],size);
        }
    }
}

void sum(LL **A,LL **B,LL **C,LL size){
  for (LL i = 0; i < size; i++) {
      for (LL j = 0; j < size; j++) {
          C[i][j] = A[i][j] + B[i][j];
      }
  }
}

void subtract(LL **A,LL **B,LL **C,LL size){
  for (LL i = 0; i < size; i++) {
      for (LL j = 0; j < size; j++) {
          C[i][j] = A[i][j] - B[i][j];
      }
  }
}

//divide the factor of 2 from number and try to incorportate some of
//strassen and rest our parallel algorithm

void strassenAlgorithm(long long int** a,long long int** b,long long int** c,int size){
    //generate 8 matrics from given matrics
    if(size%2!=0){
        //go for IKJ Basic algorithm discussed till now
        printf("in?\n");
        multiplyMatrics(a,b,c,size);
    } else{
        printf("in?\n");
        int centerCut = size/2;
        //create sub matrices
        long long int** a11 = new long long int*[centerCut];
        long long int** a12 = new long long int*[centerCut];
        long long int** a21 = new long long int*[centerCut];
        long long int** a22 = new long long int*[centerCut];
        long long int** b11 = new long long int*[centerCut];
        long long int** b12 = new long long int*[centerCut];
        long long int** b21 = new long long int*[centerCut];
        long long int** b22 = new long long int*[centerCut];
        long long int** c11 = new long long int*[centerCut];
        long long int** c12 = new long long int*[centerCut];
        long long int** c21 = new long long int*[centerCut];
        long long int** c22 = new long long int*[centerCut];
        long long int** p1 = new long long int*[centerCut];
        long long int** p2 = new long long int*[centerCut];
        long long int** p3 = new long long int*[centerCut];
        long long int** p4 = new long long int*[centerCut];
        long long int** p5 = new long long int*[centerCut];
        long long int** p6 = new long long int*[centerCut];
        long long int** p7 = new long long int*[centerCut];
        long long int** AR = new long long int*[centerCut];
        long long int** BR = new long long int*[centerCut];
        //dividing the matrices in 4 sub-matrices:
        printf("in?\n");
        for (int i = 0; i < centerCut; i++) {
            a11[i] = new long long int[centerCut];
            a12[i] = new long long int[centerCut];
            a21[i] = new long long int[centerCut];
            a22[i] = new long long int[centerCut];
            b11[i] = new long long int[centerCut];
            b12[i] = new long long int[centerCut];
            b21[i] = new long long int[centerCut];
            b22[i] = new long long int[centerCut];
            c11[i] = new long long int[centerCut];
            c12[i] = new long long int[centerCut];
            c21[i] = new long long int[centerCut];
            c22[i] = new long long int[centerCut];
            p1[i]= new long long int[centerCut];
            p2[i]= new long long int[centerCut];
            p3[i]= new long long int[centerCut];
            p4[i]= new long long int[centerCut];
            p5[i]= new long long int[centerCut];
            p6[i]= new long long int[centerCut];
            p7[i]= new long long int[centerCut];
            AR[i]= new long long int[centerCut];
            BR[i]= new long long int[centerCut];
            for (int j = 0; j < centerCut; j++) {
                a11[i][j] = a[i][j];
                a12[i][j] = a[i][j + centerCut];
                a21[i][j] = a[i + centerCut][j];
                a22[i][j] = a[i + centerCut][j + centerCut];

                b11[i][j] = b[i][j];
                b12[i][j] = b[i][j + centerCut];
                b21[i][j] = b[i + centerCut][j];
                b22[i][j] = b[i + centerCut][j + centerCut];
            }
        }

        printf("in?\n");
        //calculate p1 to p7
        sum(a11,a22,AR,centerCut); // a11 + a22
        sum(b11,b22,BR,centerCut); // b11 + b22
        strassenAlgorithm(AR,BR,p1,centerCut); // p1 = (a11+a22) * (b11+b22)

        sum(a21,a22,AR,centerCut); // a21 + a22
        strassenAlgorithm(AR,b11,p2,centerCut); // p2 = (a21+a22) * (b11)

        subtract(b12, b22, BR, centerCut); // b12 - b22
        strassenAlgorithm(a11, BR, p3, centerCut); // p3 = (a11) * (b12 - b22)

        subtract(b21, b11, BR, centerCut); // b21 - b11
        strassenAlgorithm(a22, BR, p4, centerCut); // p4 = (a22) * (b21 - b11)

        sum(a11, a12, AR, centerCut); // a11 + a12
        strassenAlgorithm(AR, b22, p5, centerCut); // p5 = (a11+a12) * (b22)

        subtract(a21, a11, AR, centerCut); // a21 - a11
        sum(b11, b12, BR, centerCut); // b11 + b12
        strassenAlgorithm(AR, BR, p6, centerCut); // p6 = (a21-a11) * (b11+b12)

        subtract(a12, a22, AR, centerCut); // a12 - a22
        sum(b21, b22, BR, centerCut); // b21 + b22
        strassenAlgorithm(AR, BR, p7, centerCut); // p7 = (a12-a22) * (b21+b22)

        // calculating c21, c21, c11 e c22:
        sum(p3, p5, c12, centerCut); // c12 = p3 + p5
        sum(p2, p4, c21, centerCut); // c21 = p2 + p4

        sum(p1, p4, AR, centerCut); // p1 + p4
        sum(AR, p7, BR, centerCut); // p1 + p4 + p7
        subtract(BR, p5, c11, centerCut); // c11 = p1 + p4 - p5 + p7

        sum(p1, p3, AR, centerCut); // p1 + p3
        sum(AR, p6, BR, centerCut); // p1 + p3 + p6
        subtract(BR, p2, c22, centerCut); // c22 = p1 + p3 - p2 + p6

        // Grouping the results obtained in a single matrix:
        for (int i = 0; i < centerCut ; i++) {
            for (int j = 0 ; j < centerCut ; j++) {
                c[i][j] = c11[i][j];
                c[i][j + centerCut] = c12[i][j];
                c[i + centerCut][j] = c21[i][j];
                c[i + centerCut][j + centerCut] = c22[i][j];
            }
        }

    }
}

int main(int argc, char* argv[])
{
    long long int n;
    cin >> n;
    long long int** a = new long long int*[n];
    long long int** b = new long long int*[n];
    long long int** c = new long long int*[n];
    for(int i = 0; i < n; i++){
        a[i] = new long long int[n];
        b[i] = new long long int[n];
        c[i] = new long long int[n];
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> b[j][i];
        }
    }
    strassenAlgorithm(a,b,c,n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << c[i][j] <<" ";
        }
        cout <<endl;
    }
    return 0;
}
