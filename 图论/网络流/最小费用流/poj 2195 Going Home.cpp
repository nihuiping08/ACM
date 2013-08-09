/*

��Ŀ:
    ����n�������Լ�n�����ӣ�����Щ�������ѡ��ؼң�ʹ���ܵĹ����پ���
    ��С

������
    ֱ�ӽ�ͼ������ÿ�������Լ�ÿ�����������ߣ�����Ϊ�����پ��룬����Ϊ1,
    ��������Դ���Լ�������㣬�ֱ����϶����Լ�����

*/
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int X = 150;
const int maxn = 305;
const int maxm = 100000;
const int inf = 1e9;
#define debug puts("here");

struct node{
    int y,f,c,next;
}edge[maxm];

struct point{
    int x,y;
    void init(int _x,int _y){
        x = _x;
        y = _y;
    }
}stack[X];

int dis[maxn],pre[maxn],arc[maxn];
int po[maxn],tol;
int n,m,s,t;
bool use[maxn];
int q[maxm],head,tail,ans;
char map[X][X];

void add(int x,int y,int c,int f){
    edge[++tol].y = y;
    edge[tol].c = c;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].y = x;
    edge[tol].c = -c;
    edge[tol].f = 0;
    edge[tol].next = po[y];
    po[y] = tol;
}

bool spfa(){
    memset(use,false,sizeof(use));
    head = tail = 0;
    for(int i=1;i<=n;i++)
        dis[i] = inf;
    dis[s] = 0;
    q[tail++] = s;
    pre[s] = 0;
    int x,y;
    while(head<tail){
        x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            y = edge[i].y;
            if(edge[i].f>0&&edge[i].c+dis[x]<dis[y]){
                dis[y] = edge[i].c + dis[x];
                pre[y] = i;
                if(!use[y]){
                    use[y] = true;
                    q[tail++] = y;
                }
            }
        }
    }
    if(dis[t]==inf)
        return false;
    int aug = inf;
    for(int i=pre[t];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[t];i;i=pre[edge[i^1].y]){
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += dis[t]*aug;
    return true;
}

int abs(int x){
    if(x<0)
        return -x;
    return x;
}

void build(){
    tol = 1;
    memset(po,0,sizeof(po));
    int top = 0;

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(map[i][j]=='H')
                stack[++top].init(i,j);
    int cnt = top;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(map[i][j]=='m'){
                cnt++;
                for(int k=1;k<=top;k++)
                    add(k,cnt,abs(i-stack[k].x)+abs(j-stack[k].y),1);
            }
    s = cnt+1;
    t = s+1;
    for(int i=1;i<=top;i++)
        add(s,i,0,1);
    for(int i=top+1;i<=cnt;i++)
        add(i,t,0,1);
    n = t;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m,n||m){
        for(int i=0;i<n;i++)
            scanf("%s",map[i]);
        build();
        ans = 0;
        while(spfa());
        cout<<ans<<endl;
    }
    return 0;
}
