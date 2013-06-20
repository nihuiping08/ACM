/*

先按年龄分组，然后排序后把多余的删掉，然后合并排序，线性扫描输出。

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

const int MAXN = 1e5+5;

struct node{
    char name[9];
    int age;
    int worth;
    friend bool operator < (node a,node b){
        return (a.worth>b.worth)||
            (a.worth==b.worth&&a.age<b.age)||
            (a.worth==b.worth&&a.age==b.age&&strcmp(a.name,b.name)<0);
    }
}p[MAXN];

vector<node> vec[205];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,k;
    RD2(n,k);

    node now;
    rep(i,n){
        scanf("%s%d%d",now.name,&now.age,&now.worth);
        vec[now.age].pb(now);
    }
    rep(i,201)
        if(vec[i].size())
            sort( All(vec[i]) );

    n = 0;
    rep(i,201){
        int up = min(100,int(vec[i].size()) );
        rep(j,up)
            p[n++] = vec[i][j];
    }

    sort(p,p+n);
    int x,y,m;
    rep1(Ncase,k){
        printf("Case #%d:\n",Ncase);
        RD3(m,x,y);
        int cnt = 0;
        rep(i,n){
            if(p[i].age>=x&&p[i].age<=y){
                printf("%s %d %d\n",p[i].name,p[i].age,p[i].worth);
                cnt ++;
                if(cnt>=m)
                    break;
            }
        }
        if(cnt==0)
            puts("None");
    }

	return 0;
}
