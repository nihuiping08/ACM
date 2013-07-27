/*

一棵树，节点有两种颜色，相邻的节点的颜色必须不一样，且节点的权值为该节点为根时所在子树的所有边权和。
现在给出n个点的信息，需要你还原这棵树。

优先队列+贪心。以颜色划分两个集合，每次从两个集合中取出最小的权值的两个点进行合并，取完之后把一个
点放进优先队列进行下一轮的操作。

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

struct node{
    int x,val;
    friend bool operator < (node a,node b){
        return a.val>b.val;
    }
    node(){}
    node(int a,int b){
        x = a;
        val = b;
    }
};

priority_queue<node> q[2];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    int val,c;
    int ncase = 0;
    while(cin>>n){
        ncase?puts("-------------------------------"):ncase = true;
        while(q[0].size())
            q[0].pop();
        while(q[1].size())
            q[1].pop();

        rep1(x,n){
            RD2(c,val);
            q[c].push( node(x,val) );
        }

        for(int qq=1;qq<n;qq++){
            if(q[0].empty()||q[1].empty()){
                debug;
                exit(0);
            }

            node a = q[0].top();
            node b = q[1].top();
            q[0].pop();
            q[1].pop();
            printf("%d %d %d\n",a.x,b.x,min(a.val,b.val));
            if(a.val>b.val)
                q[0].push( node(a.x,a.val-b.val) );
            else if(a.val<b.val)
                q[1].push( node(b.x,b.val-a.val) );
            else{
                if(q[1].empty())
                    q[1].push( node(b.x,b.val-a.val) );
                else
                    q[0].push( node(a.x,a.val-b.val) );
            }
        }
    }

	return 0;
}
