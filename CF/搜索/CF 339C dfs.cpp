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
#define Clear(x) memset(x,0,sizeof(x))
/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

/******** program ********************/

const int MAXN = 1e4+5;

vector<int> vec;
int len;
int pre[MAXN];

bool dfs(int a,int b,int pa,int res){
    if(!res)return true;
    rep(i,len)
        if(vec[i]!=pa&&a+vec[i]>b)
            if(dfs(b,a+vec[i],vec[i],res-1)){
                pre[res] = vec[i];
                return true;
            }
    return false;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    char s[12];
    while(scanf("%s",s+1)!=EOF){
        vec.clear();
        rep1(i,10)
            if(s[i]=='1')
                vec.pb(i);
        len = vec.size();
        int n;
        RD(n);
        if(dfs(0,0,0,n)){
            puts("YES");
            for(int i=n;i;i--)
                printf("%d ",pre[i]);
            puts("");
        }else
            puts("NO");
    }

    return 0;
}
