/*

题目：
    判断矩阵a * b == c

分析：
    方法一：
        O(n^3)算法提示会TLE,但是原矩阵是一个稀疏矩阵，所以可
    以在相乘的时候判断是否为0，这样同样不会TLE~~

    方法二：
        压缩矩阵，左乘1*n的矩阵，使得左边以及右边都变成1*n的
    矩阵，然后两边判断是否相等就行了~~但是如果这样压缩的话，
    不保证每个元素的特性，所以这个1*n的矩阵得要体现特性，构
    造的时候可以取随机数，或者令(1,2...n)

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 505;
#define debug puts("here");

typedef __int64 ll;

int n;

void mul(ll a[X][X],ll *b){
    ll temp[X] = {0};
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            temp[i] += b[j]*a[j][i];
    for(int i=0;i<n;i++)
        b[i] = temp[i];
}

bool eq(ll a[],ll b[]){
    for(int i=0;i<n;i++)
        if(a[i]!=b[i])
            return false;
    return true;
}

ll a[X][X],b[X][X],c[X][X];
ll q[X],p[X];

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n){
        for(int i=0;i<n;i++)
            q[i] = p[i] = i+1;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%I64d",&a[i][j]);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%I64d",&b[i][j]);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%I64d",&c[i][j]);

        mul(a,p);
        mul(b,p);
        mul(c,q);

        if(eq(p,q))
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
