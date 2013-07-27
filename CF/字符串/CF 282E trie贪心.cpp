/*

给出一个序列，现在选择一个前缀以及一个后缀（不相交），使得前缀以及后缀中的所有数的异或和最大

trie树上贪心。先把所有的数异或起来，作为最初的后缀，而前缀是 0，先插入字典树中，然后，
每次将后缀“减一”，前缀“加一”，先把前缀加入字典树中，再在字典树中查询与当前的后缀异或值最大的数。


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
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)
#define fir first
#define sec second

/******** program ********************/

const int MAXN = 1e5+5;

ll a[MAXN];

struct node{
    node *p[2];
    ll val;
    node(){
        val = 0;
        p[0] = p[1] = NULL;
    }
};

void ins(node *root,ll now){
    ll val = now;

    ll tmp[42] = {0};
    ll top = 40;
    while(now){
        tmp[--top] = now&1;
        now >>= 1;
    }

    for(ll i=0;i<40;i++){
        ll x = tmp[i];
        if( root->p[x]==NULL )
            root->p[x] = new node();
        root = root->p[x];
    }
    root->val = val;
}

ll cc(node *root,ll now){
    ll tmp[42] = {0};
    ll top = 40;
    while(now){
        tmp[--top] = now&1;
        now >>= 1;
    }

    for(ll i=0;i<40;i++){
        ll x = tmp[i];
        if(root->p[x^1])
            root = root->p[x^1];
        else if(root->p[x])
            root = root->p[x];
        else
            return 0;
    }
    return root->val;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(cin>>n){
        node *root = new node();

        ll r = 0;
        ll ans = 0;

        rep1(i,n){
            cin>>a[i];
            r ^= a[i];
            cmax(ans,r);
        }

        ll l = 0;
        ins(root,0);

        rep1(i,n){
            l ^= a[i];
            r ^= a[i];
            ins(root,l);
            cmax( ans,cc(root,r)^r );
        }
        cout<<ans<<endl;
    }

	return 0;
}
