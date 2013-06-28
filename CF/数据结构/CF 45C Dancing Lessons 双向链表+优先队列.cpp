/*

分析：
    优先队列寻在总区间最值，用双向链表维护前驱后缀

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
#define PQ priority_queue

/******** program ********************/

const int MAXN = 2e5+5;

char s[MAXN];
int a[MAXN];
int pre[MAXN],next[MAXN];
bool use[MAXN];

struct node{
    int l,r,val;
    node(){}
    node(int x,int y,int z):l(x),r(y),val(z){}
    friend bool operator < (node a,node b){
        return a.val>b.val || (a.val==b.val&&a.l>b.l);
    }
};
PQ<node> q;

bool ok(char x,char y){
    return (x=='B'&&y=='G')||(x=='G'&&y=='B');
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(~RD(n)){
        scanf("%s",s+1);

        s[0] = '*';
        s[n+1] = '*';

        rep1(i,n){
            RD(a[i]);
            pre[i] = i-1;
            next[i] = i+1;
            if( ok(s[i],s[i-1]) )
                q.push( node( i-1,i,abs(a[i]-a[i-1]) ) );
        }

        memset(use,false,sizeof(use));
        vector<PII> vec;
        while(!q.empty()){
            node p = q.top();
            q.pop();
            int y = p.r;
            int x = p.l;
            if(use[x]||use[y])
                continue;
            use[x] = use[y] = true;
            vec.pb( MP(x,y) );
            if( ok(s[pre[x]],s[next[y]]) )
                q.push( node(pre[x],next[y],abs(a[pre[x]]-a[next[y]])) );
            pre[ next[y] ] = pre[x];
            next[ pre[x] ] = next[y];
        }
        cout<<vec.size()<<endl;
        foreach(i,vec)
            printf("%d %d\n",vec[i].first,vec[i].second);
    }

	return 0;
}
