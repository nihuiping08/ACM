/*

题目：给出n,a0,b0，找出满足所有x,y的数，使得n|(a0*x+b0*y)和n|(a*x+b*y)
的(a,b)的个数
分析：n| (a0*x+b0*y) , 有n| (a0*x*i+b0*y*i)。。。然后一直找直到
a0*x*i%n = a0%n && b0*y*i%n = b0%n

*/
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    vector< pair<int,int> > ans;

    int n;
    int a0,b0;
    RD3(n,a0,b0);

    a0 %= n;
    b0 %= n;
    int a = a0,b = b0;
    do{
        a = (a+a0)%n;
        b = (b+b0)%n;
        ans.pb( make_pair(a,b) );
    }while(a!=a0 || b!=b0);

    sort(ans.begin(),ans.end());
    cout<<ans.size()<<endl;
    foreach(i,ans)
        cout<<ans[i].first<<" "<<ans[i].second<<endl;

	return 0;
}
