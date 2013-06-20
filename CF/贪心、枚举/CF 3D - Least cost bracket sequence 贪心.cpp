/*

题目：
    给出字符串，只有三种字符( ? )，把?改为()的代价为a_i,b_i，问把?改为()之后使得字符串括号匹配的
	最小代价是多少。

分析：
	贪心。我们先把所有的?变成)的形式。然后每次判断当前的)数目是否大于(数，如果大于的话，从前面所有
	由?变成的)中选取最小代价差值的?使他变成(。所以题目变成了区间维护最值问题。用set或者priority_queue
	来维护即可

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

/******** program ********************/

const int MAXN = 5e4+5;

set< pair<int,int> > s;
string str,out;
int a[MAXN],b[MAXN];

ll solve(){
    ll ans = 0;
    int le = 0;
    int ri = 0;
    out = str;

    foreach(i,str){
        if(str[i]=='(')
            le ++;
        else if(str[i]==')')
            ri ++;
        else{
            ri ++;
            s.insert( MP(a[i]-b[i],i) );
            ans += b[i];
            out[i] = ')';
        }

        if(le<ri){
            //cout<<i<<" ";
            if(s.size()==0)
                return -1;
            pair<int,int> p = *s.begin();
            ans = ans+p.first;
            //cout<<p.second<<endl;
            out[p.second] = '(';
            le ++;
            ri --;
            s.erase( s.begin() );
        }
    }
    if(le!=ri)  return -1;
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>str){
        foreach(i,str)
            if(str[i]=='?')
                RD2(a[i],b[i]);
        if(str.size() & 1){
            puts("-1");
            continue;
        }
        s.clear();
        ll ans = solve();
        if(ans!=-1)
            cout<<ans<<endl<<out<<endl;
        else
            puts("-1");
    }

	return 0;
}
