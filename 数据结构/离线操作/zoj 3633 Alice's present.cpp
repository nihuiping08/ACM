/*

题目：
    给出a1,a2...an，询问区间[l,r]从右往左第一次出现两次的数，如果没有
    的话，就输出OK。

分析：
    我们可以离线操作。为了更加直观，我首先把数列置反，然后处理一下区间。
    具体过程：
    1.把所有操作先读进来，对于每个操作按照左区间排序，相等的话再按照有区
    间排序。
    2.记录两个指针l,r:l表示当前询问到的最左指针，r表示从l到最右的出现的
    第二次的数val的位置。然后再把l往右移，直到该位置的数为val为止。
    3.开始统计：
        1.当now_x <= l
            1.当now_y<r，OK
            2.当now_y>=r，val
        2.当now_x>l && now_y<=r,OK

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

const int MAXN = 500005;

int a[MAXN],val[MAXN],n,m;
int use[MAXN/10];
map<int,int> ma;
map<int,int> ha;

struct node{
    int x,y,id;
    friend bool operator < (node a,node b){
        return a.x<b.x || (a.x==b.x&&a.y<b.y);
    }
}p[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n){
        ma.clear();
        ha.clear();
        int cnt = 0;
        for(int i=1;i<=n;i++){
            RD(a[i]);
            int tmp = a[i];
            if(ha[a[i]])
                a[i] = ha[a[i]];
            else
                a[i] = ha[a[i]] = ++cnt;
            val[a[i]] = tmp;
        }

        reverse(a+1,a+n+1);

        RD(m);
        rep(i,m){
            RD2(p[i].y,p[i].x);
            p[i].x = n+1-p[i].x;
            p[i].y = n+1-p[i].y;
            p[i].id = i;
        }
        sort(p,p+m);

        memset(use,0,sizeof(use));
        int now = 0;
        int l = 0,r = 1;

        while(r<=n&&now<m){
            ma[a[l]] --;
            l ++;

            while( ma[a[r]]==0 ){
                ma[a[r]] ++;
                r ++;
            }

            //cout<<"r = "<<r<<endl;

            while(a[l]!=a[r]){
                ma[a[l]] --;
                l ++;
            }

            //cout<<l<<" "<<r<<endl;

            while(now<m&&p[now].x<=l){
                int id = p[now].id;
                if(p[now].y>=r)
                    use[id] = val[a[r]];
                else
                    use[id] = 0;
                now ++;
            }

            while(now<m&&p[now].y<=r){
                int id = p[now].id;
                use[id] = 0;
                now ++;
            }
        }

        rep(i,m)
            use[i]==0?puts("OK"):printf("%d\n",use[i]);
        puts("");
    }

	return 0;
}
