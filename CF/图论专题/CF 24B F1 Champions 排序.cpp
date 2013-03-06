/*

题目：
    每场比赛前十名得分。现在有两种排序方式：
    1.先按分数排，相等的话，再按得到第一名的次数排，否则再按第二名的次数
    排。。。。
    2.先按得到第一名的次数排，相等的话，再按分数排，相等的话，按第二名次数
    排。。。
    现在比了t场，问最终两种方式哪个人是第一名

分析：
    结构体简单排序。。。

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 1005;

int mm[MAXN] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};

map<string,int> ma;
map<int,string> name;

struct node{
    int a[52];
    int tot;
    int id;
}a[MAXN];

bool cmp1(node a,node b){
    if(a.tot>b.tot)
        return true;
    else if(a.tot<b.tot)
        return false;
    for(int i=0;i<50;i++){
        if(a.a[i]>b.a[i])
            return true;
        else if(a.a[i]<b.a[i])
            return false;
    }
    return false;
}

bool cmp2(node a,node b){
    if(a.a[0]>b.a[0])
        return true;
    else if(a.a[0]<b.a[0])
        return false;
    if(a.tot>b.tot)
        return true;
    else if(a.tot<b.tot)
        return false;
    for(int i=1;i<50;i++)
        if(a.a[i]>b.a[i])
            return true;
        else if(a.a[i]<b.a[i])
            return false;
    return false;
}

string ans1,ans2;

void solve(int t){
    int n;
    memset(a,0,sizeof(a));
    ma.clear();
    name.clear();

    string s;
    int tot = 0;
    while(t--){
        cin>>n;
        rep(i,n){
            cin>>s;
            int x = ma[s];
            if(x==0){
                x = ma[s] = ++tot;
                name[tot] = s;
                a[x].id = x;
            }
            a[x].a[i] ++;
            a[x].tot += mm[i];
        }
    }

    sort(a+1,a+tot+1,cmp1);
    ans1 = name[a[1].id];

    sort(a+1,a+tot+1,cmp2);
    ans2 = name[a[1].id];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int t;
    while(cin>>t){
        solve(t);
        cout<<ans1<<endl;
        cout<<ans2<<endl;
    }

	return 0;
}
