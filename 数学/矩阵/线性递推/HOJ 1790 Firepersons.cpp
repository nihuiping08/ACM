/*

题目:
    线性递推关系，an=Σ1<=i<=k*an-i*bi，问ai

分析：
    可以构造矩阵A如下
    0  1    0   ...0
    0  0    1   ...0
    ...
    0  0    0   ...1
    bk bk-1 bk-2...b0

    矩阵B为
    a0
    a1
    a2
    ...
    ak-1
    则ai = ai(i<k)
         = A^(i-k+1)*B最后一行的元素
*/
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

#define debug puts("here")

const int MOD = 10000;
const int X = 102;

class Matrix{
public:
    int n,m;
    int a[X][X];

    Matrix(){
        memset(a,0,sizeof(a));
    }
    Matrix(int _n,int _m):n(_n),m(_m){
        memset(a,0,sizeof(a));
    }

    Matrix operator * (Matrix p){
        int q = p.m;
        Matrix c(n,q);
        for(int i=0;i<n;i++)
            for(int j=0;j<q;j++)
                for(int k=0;k<m;k++)
                    c.a[i][j] = (c.a[i][j]+a[i][k]*p.a[k][j])%MOD;
        return c;
    }

    void getE(){
        memset(a,0,sizeof(a));
        for(int i=0;i<n;i++)
            a[i][i] = 1;
    }

    Matrix bin(int exp){
        Matrix temp(n,n);
        temp.getE();
        Matrix cur = *this;

        while(exp>0){
            if(exp&1)
                temp = temp*cur;
            cur = cur*cur;
            exp = exp >> 1;
        }
        return temp;
    }

    void di(){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }

};

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    int n;
    while(cin>>n,n){
        Matrix a = Matrix(n,n);
        Matrix b = Matrix(n,1);
        for(int i=0;i<n-1;i++)
            a.a[i][i+1] = 1;
        for(int i=0;i<n;i++)
            scanf("%d",&b.a[i][0]);
        for(int i=0;i<n;i++)
            scanf("%d",&a.a[n-1][n-i-1]);
        int exp;
        cin>>exp;
        if(exp<n){
            printf("%d\n",b.a[exp][0]);
            continue;
        }
        exp ++;
        exp -= n;
        a = a.bin(exp);
        a = a*b;
        printf("%d\n",a.a[n-1][0]);
    }
	return 0;
}
