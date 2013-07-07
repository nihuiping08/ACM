/*

题目：把1到n组成一个新的数，如n = 10时，该数为 12345678910，问n时模m的值
分析：
	f(n) = f(n-1)*10^k + n
	由于n比较大，所以需要需要用矩阵快速幂分段求。
	一个辅助矩阵
	f(n) , n , 1
	
	10^k 0  0
	1    1  0
	1    1  1
	
	根据n的长度分段快速幂即可

*/
#include <set>
#include <map>
#include <list>
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
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>
#define PQ priority_queue

/******** program ********************/

const int MAXN = 5;

ll MOD,n;

class Matrix{
    public:
        int n,m;
        ll a[MAXN][MAXN];

        ll cc(ll x,ll y){
            ll sum = 0;
            while(y>0){
                if(y&1)
                    sum = (sum+x)%MOD;
                y >>= 1;
                x = (x<<1)%MOD;
            }
            return sum;
        }

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
                for(int k=0;k<q;k++)
                    if(a[i][k])
                        for(int j=0;j<m;j++)
                            c.a[i][j] = (c.a[i][j]+cc(a[i][k],p.a[k][j]) )%MOD;
            return c;
        }

        void setE(){
            for(int i=0;i<n;i++)
                a[i][i] = 1;
        }

        Matrix bin(ll exp){
            Matrix temp(n,n);
            temp.setE();
            Matrix cur = *this;

            while(exp>0){
                if(exp&1)
                    temp = temp*cur;
                cur = cur*cur;
                exp = exp >> 1;
            }
            return temp;
        }

        void Debug(){
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)
                    cout<<a[i][j]<<" ";
                cout<<endl;
            }
            cout<<endl;
        }
};

int cal(ll n){
    int ans = 0;
    while(n){
        ans ++;
        n /= 10;
    }
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>MOD){
        int len = cal(n);
        Matrix ans = Matrix(1,3);
        ans.a[0][0] = 1;
        ans.a[0][1] = 1;
        ans.a[0][2] = 1;

        ll t = 1;
        for(int i=1;i<=len;i++){
            Matrix now = Matrix(3,3);

            t = t*10;
            now.a[0][0] = t%MOD;
            now.a[0][1] = 0;
            now.a[0][2] = 0;
            now.a[1][0] = 1;
            now.a[1][1] = 1;
            now.a[1][2] = 0;
            now.a[2][0] = 1;
            now.a[2][1] = 1;
            now.a[2][2] = 1;

            ll tmp = t-t/10;
            if(t>n){
                t /= 10;
                tmp = n-t+1;
            }
            if(tmp==9)
                tmp = 8;

            //cout<<tmp<<" ";
            ans = ans*( now.bin(tmp) );
            //ans.Debug();
        }

        //puts("");
        //cout<<"ans = ";
        cout<<ans.a[0][0]<<endl;
    }

	return 0;
}
