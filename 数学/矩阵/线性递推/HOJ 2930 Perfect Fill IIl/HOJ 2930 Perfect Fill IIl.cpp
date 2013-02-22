/*

¼ûÌâ½â

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
#define rep(i,n) for(int i=0;i<n;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back

const int MOD = 2010;
const int X = 5;

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
    Matrix p = Matrix(3,1);
    p.a[0][0] = 1;
    p.a[1][0] = 2;
    p.a[2][0] = 5;
    while(~scanf("%d",&n)){
        if(n<=3){
            printf("%d\n",p.a[n-1][0]);
            continue;
        }
        Matrix ans = Matrix(3,3);
        ans.a[0][1] = ans.a[1][2] = 1;
        ans.a[2][0] = 1;
        ans.a[2][1] = 0;
        ans.a[2][2] = 2;
        ans = ans.bin(n-3);
        ans = ans*p;
        printf("%d\n",ans.a[2][0]);
    }
	return 0;
}
