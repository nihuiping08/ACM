/*

题目：给出n个数，用m个变量表示，对于这n个数对变量赋值输出。
	1.如果变量已经赋值且为为val，则代价为0
	2.如果变量还没初始化，代价为该值的二进制表示的1的个数
	3.如果变量已经赋值但是非当前的值，代价为新值的二进制表示的1的个数
	
	问如何赋值使得代价最小。
	
分析：
	k路覆盖。
	建立三个集合，A,B,C。
	A集合代表m个变量，连上C集合的所有元素，表示C集合中第一次使用该变量。
	B集合代表n个数已经被变量赋过值，与C集合中的该数后面的数连上。
	对于A,B集合，连上源点。
	对于C集合，连上汇点。
	求一次最小费用流。

7 2
1 2 2 4 2 1 2

11 4
b=1
print(b)
a=2
print(a)
print(a)
b=4
print(b)
print(a)
b=1
print(b)
print(a)

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
#include <utility>
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


const int MAXN = 10005;
const int MAXM = 500005;
const int INF = 1e9;

int pre[MAXN],dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
int n,m,vs,vt,ans;

struct node{
    int y,f,cost,next;
}edge[MAXM];

void Add(int x,int y,int f,int cost){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].cost = cost;
    edge[tol].next = po[x];
    po[x] = tol;
}

void add(int x,int y,int f,int cost){
    Add(x,y,f,cost);
    Add(y,x,0,-cost);
}

bool spfa(){
    memset(use,false,sizeof(use));
    rep1(i,vt)
        dis[i] = INF;
    dis[vs] = 0;
    head = tail = 0;
    q[tail++] = vs;
    pre[vs] = 0;
    while(head<tail){
        int x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(edge[i].f>0&&edge[i].cost+dis[x]<dis[y]){
                dis[y] = dis[x]+edge[i].cost;
                pre[y] = i;
                if(!use[y]){
                    use[y] = true;
                    q[tail++] = y;
                }
            }
        }
    }
    if(dis[vt]==INF)
        return false;

    int aug = INF;
    for(int i=pre[vt];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[vt];i;i=pre[edge[i^1].y]){
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += dis[vt]*aug;
    return true;
}

int a[MAXN];

int cnt(int x){
    int ans = 0;
    while(x){
        ans += x&1;
        x >>= 1;
    }
    return ans;
}

string vec[MAXN];
int fa[MAXN];

string cc(int n){
    string s;
    while(n){
        s.pb( char(n%10+'0') );
        n /= 10;
    }
    reverse(All(s));
    return s;
}

int tmp[MAXN];
int val[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase = 0;
    while(cin>>n>>m){
        ncase?puts("------------------------"):ncase = 1;
        rep1(i,n)
            RD(a[i]);

        Clear(po);
        tol = 1;

        vs = MAXN-5;
        vt = vs+1;

        rep1(i,n){
            add(vs,i,1,0);
            REP(j,i+1,n)
                add(i,j+n,1,a[i]==a[j]?0:cnt(a[j]));
            add(i+n,vt,1,0);
        }

        rep1(i,m){
            rep1(j,n)
                add(i+2*n,j+n,1,cnt(a[j]));
            add(vs,i+2*n,1,0);
        }

        ans = 0;
        while(spfa())
            ;

        Clear(val);

        for(int i=2;i<=tol;i+=2){
            int x = edge[i].y;
            int y = edge[i^1].y;
            if(x==vs||y==vs||x==vt||y==vt)
                continue;
            if(edge[i].f)continue;
            fa[x] = y;
            //cout<<x<<" "<<y<<endl;
        }

        int top = 0;
        rep1(i,n){
            int x = i+n;
            int y = fa[x];

            if(y>2*n){
                string s;
                s.pb( char('a'+y-2*n-1) );
                s += "=" + cc(a[i]);
                vec[top++] = s;

                s.clear();
                s = "print(";
                s.pb( char('a'+y-2*n-1) );
                vec[top++] = s+")";

                val[i] = y-2*n-1;
                tmp[ val[i] ] = a[i];

            }else{

                string s;

                if( tmp[ val[y] ]==a[i]){
                    val[i] = val[y];

                    s = "print(";
                    s.pb( char('a'+val[y]) );
                    vec[top++] = s+")";

                }else{
                    s.pb( char('a'+val[y]) );
                    s += "="+cc(a[i]);
                    vec[top++] = s;

                    s.clear();
                    s = "print(";
                    s.pb( char('a'+val[y]) );
                    vec[top++] = s+")";

                    val[i] = val[y];
                    tmp[val[i]] = a[i];
                }

            }

            //cout<<"val i = "<<i<<" "<<val[i]<<endl;
        }

        cout<<top<<" "<<ans<<endl;
        rep(i,top)
            cout<<vec[i]<<endl;
    }

	return 0;
}
