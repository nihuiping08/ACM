/*

题目：
    给从1到n分组，使得每组的和值为素数，并且组数最小

分析：
    令m = n*(n+1)/2
    1.若m为素数，一组
    2.若m为偶数，根据哥德巴赫猜想可知，可以分成两组
    3.若m为奇数，若m-2为素数，两组
    4.若m为奇数，且m-2为合数，则把m-3分成两组（根据2），3单独一组。

    至于如何对于偶数进行分组，可以先找出一个不大于n的素数p，如果
    m-p也是素数，则从高位到低位开始赋值即可（由于1,2这些小数的存在，
    必然使得有解）。

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

/******** program ********************/

const int MAXN = 6005;

int a[MAXN];

bool isprime(int n){
    int len = sqrt(n*1.0);
    for(int i=2;i<=len;i++)
        if(n%i==0)
            return false;
    return true;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(cin>>n){
        rep1(i,n)
            a[i] = 1;
        int m = (n+1)*n/2;
        if(!isprime(m)){
            if(m%2==0){
                int p = -1;
                for(int i=2;i<=n;i++)
                    if(isprime(i)&&isprime(m-i)){
                        p = i;
                        a[i] = 2;
                        break;
                    }
            }else{
                if(isprime(m-2)){
                    a[2] = 2;
                }else{
                    a[3] = 2;
                    m -= 3;
                    for(int i=2;i<=n;i++)
                        if(isprime(i)&&isprime(m-i)){
                            a[i] = 3;
                            break;
                        }
                }
            }
        }
        rep1(i,n)
            printf("%d ",a[i]);
        puts("");
    }

	return 0;
}
