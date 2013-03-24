/*

分析：
	構造一個矩陣：
	a[][] = 
	B C 0 0 ...
	A B C 0 ...
	...........
	0 0 0 0...B
	
	b[] = s[0,0]....s[n-1,0]
	
 
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

#define debug puts("here")

const int X = 55;
int MOD;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

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

    int N,A,B,C,T;
    while(scanf("%d%d%d%d%d%d",&N,&MOD,&A,&B,&C,&T),N||MOD||A||B||C||T){
        Matrix a(N,N);
        rep(i,N){
            if(i)
                a.a[i][i-1] = A;
            a.a[i][i] = B;
            if(i<N-1)
                a.a[i][i+1] = C;
        }
        Matrix b(N,1);
        rep(i,N)
            RD(b.a[i][0]);
        a = a.bin(T);
        a = a*b;
        N --;
        rep(i,N)
            printf("%d ",a.a[i][0]);
        printf("%d\n",a.a[N][0]);
    }

	return 0;
}
