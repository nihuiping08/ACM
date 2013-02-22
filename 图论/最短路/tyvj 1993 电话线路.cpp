/*

题目：
    每台电话都有一个独一无二的号码，用一个十位的十进制数字
    串表示。电话a和b之间能直接通信，当且仅当“a与b之间仅有
    一个数字不同”，或者“交换a的某两位上的数字后，a与b相同”。
    而a、b之间建立通信联系所需要的时间为cost[ lcp(a,b) ]，
    其中cost[]是一个常数数组，lcp(a,b)表示a、b的最长公共前
    缀的长度，lcp(a,b)越大，通信时间越快。
    另外，如果a、b能通信，b、c能通信，那么a、c也能借助b来通
    信。a、c借助b建立通信联系所用时间是cost[ lcp(a,b) ]+
    cost[ lcp(b,c) ]。
    现在Freda想给Rainbow打电话，请你告诉Freda，她最快需要
    多少时间才能与与Rainbow建立通信联系？

分析：
    考察：枚举建图、Hash、最短路
    枚举每个电话号码，O(10*10)枚举每一位变成什么、哪两位交
    换得到的号码，Hash判断是否存在该号码，存在的话就连边，
    边权直接计算LCP。
    然后建好图之后跑个spfa或者heap-dijkstra即可。
    校内测试这题后三个点开O2给了1s，卡掉了用map的Hash。为了
    保证效率建议手写Hash，并使用slf或者heap优化的spfa、或者
    堆优化的dijkstra。

我的心得:
    这道题考察了hash、前向星、spfa、构图的能力。
    在hash函数的建立中，利用的跟前向星的思路，达到hash函数中
    一对一的操作，另外在构造模型的时候，利用枚举的方式实现了
    该两种操作

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 1e6+5;
const int maxm = 2e6+5;
const int mod = 99991;
const int X = 12;

typedef long long ll;
#define debug puts("here");

int c[X],n;
int dig[maxn][X];
ll a[maxn];
int po[maxn],tol;
int dis[maxn];
bool use[maxn];

struct node{
    ll num;
    int next;
    int id;
}p[maxn];

void insert(ll x,int id){
    int z = x%mod;
    p[++tol].num = x;
    p[tol].id = id;
    p[tol].next = po[z];
    po[z] = tol;
}

int ask(ll x){
    int z = x%mod;
    for(int i=po[z];i;i=p[i].next)
        if(p[i].num==x)
            return p[i].id;
    return 0;
}

struct qq{
    int y,next;
    int w;
}edge[maxm];
int head[maxn];

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = head[x];
    head[x] = tol;
    for(int i=0;i<10;i++){
        if(dig[x][i]!=dig[y][i]){
            edge[tol].w = c[i];
            return;
        }
    }
    debug;
}
void spfa(){
    memset(dis,0x3f,sizeof(dis));
    memset(use,false,sizeof(use));
    queue<int> q;
    q.push(1);
    dis[1] = 0;

    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        for(int i=head[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(dis[x]+edge[i].w<dis[y]){
                dis[y] = dis[x]+edge[i].w;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    if(dis[n]==1061109567)
        puts("-1");
    else
        printf("%d\n",dis[n]);
}

void build(){
    int tmp[X];

    ll q[X] = {0};
    q[0] = 1000000000;
    for(int i=1;i<10;i++)
        q[i] = q[i-1]/10;

    tol = 0;
    memset(head,0,sizeof(head));

    for(int k=1;k<=n;k++){
        for(int i=0;i<10;i++)
            tmp[i] = dig[k][i];
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++){
                if(tmp[i]!=tmp[j]){
                    ll w = p[k].num+(tmp[i]-tmp[j])*q[j]-(tmp[i]-tmp[j])*q[i];
                    int id = ask(w);
                    if(id)
                        add(k,id);
                }
                if(tmp[i]!=j){
                    ll w = p[k].num-(tmp[i]-j)*q[i];
                    int id = ask(w);
                    if(id)
                        add(k,id);
                }
            }
    }
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n){
        for(int i=0;i<10;i++)
            scanf("%d",&c[i]);
        int tmp[X];

        ll x;
        tol = 0;
        memset(po,0,sizeof(po));
        for(int i=1;i<=n;i++){
            scanf("%I64d",&x);
            insert(x,i);
            a[i] = x;
            for(int j=0;j<10;j++){
                tmp[j] = x%10;
                x /= 10;
            }
            for(int j=0;j<10;j++)
                dig[i][j] = tmp[10-j-1];
        }

        build();

        spfa();
    }
    return 0;
}
