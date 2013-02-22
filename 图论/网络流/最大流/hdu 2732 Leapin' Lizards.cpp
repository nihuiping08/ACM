/*

题目：
    给出n*m的地图，然后第一幅地图是含有数字的，每个数字表示只
    能供多少个蜘蛛走，第二幅地图是说明第几个格子有蜘蛛（‘L’）
    表示在这里有一只蜘蛛，现在蜘蛛要从格子里面往外跳，文最多
    能够有多少蜘蛛能够生存

分析：
    对于第二幅地图来说，直接对含有L字符的格子连上源点，流量为
    1，对于第一幅地图来说，对于含有数字非0的格子拆点，然后流量
    为该数字，表示只能够最大走过该数字的蜘蛛数目。然后对于每个
    范围在d之类的格子连上流量为inf的边，另外对于可以走到外面的
    格子连上汇点，表示可以走到外面

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 1000;
const int maxm = 200005;
const int inf = 1e9;
#define debug puts("here");

int n,m,s,t,d;
int po[maxn],tol;
int arc[maxn],pre[maxn],cf[maxn],dis[maxn],gap[maxn];
char a[maxn][maxn];
char b[maxn][maxn];
int ha[maxn][maxn];
int id;

int get(int x,int y){
    if(ha[x][y]==-1)
        ha[x][y] = ++id;
    return ha[x][y];
}

struct node{
    int y,f,next;
}edge[maxm];

void add(int x,int y,int f){
    edge[++tol].f = f;
    edge[tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].f = 0;
    edge[tol].y = x;
    edge[tol].next = po[y];
    po[y] = tol;
}

int sap(){
    memset(gap,false,sizeof(gap));
    memset(dis,0,sizeof(dis));
    gap[0] = t;
    for(int i=1;i<=t;i++)
        arc[i] = po[i];
    int i = s;
    int MIN;
    int aug = inf;
    int ans = 0;
    bool ok;

    while(dis[s]<t){
        ok = false;
        cf[i] = aug;
        for(int j=arc[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]+1==dis[i]){
                ok = true;
                aug = min(aug,edge[j].f);
                arc[i] = j;
                i = edge[j].y;
                pre[i] = j;
                if(i==t){
                    ans += aug;
                    while(i!=s){
                        edge[pre[i]].f -= aug;
                        edge[pre[i]^1].f += aug;
                        i = edge[pre[i]^1].y;
                    }
                    aug = inf;
                }
                break;
            }
        if(ok)
            continue;
        MIN = t-1;
        for(int j=po[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]<MIN){
                MIN = dis[edge[j].y];
                arc[i] = j;
            }
        if(--gap[dis[i]]==0)
            break;
        dis[i] = MIN+1;
        gap[dis[i]]++;
        if(i!=s){
            i = edge[pre[i]^1].y;
            aug = cf[i];
        }
    }
    return ans;
}

int dir[40][2]={
               {1,0},{0,-1},{-1,0},{0,1},//4
               {2,0},{1,-1},{0,-2},{-1,-1},{-2,0},{-1,1},{0,2},{1,1},//8
               {3,0},{2,-1},{1,-2},{0,-3},{-1,-2},{-2,-1},{-3,0},{-2,1},{-1,2},{0,3},{1,2},{2,1},//12
               {4,0},{3,-1},{2,-2},{1,-3},{0,-4},{-1,-3},{-2,-2},{-3,-1},{-4,0},{-3,1},{-2,2},{-1,3},{0,4},{1,3},{2,2},{3,1},//16
};

int size[] = {0,4,12,24,40};

bool out(int x,int y){
    return x<0||y<0||x>=n||y>=m;
}

int build(){
    for(int i=0;i<n;i++)
        scanf("%s",a[i]);
    for(int i=0;i<n;i++)
        scanf("%s",b[i]);

    memset(po,0,sizeof(po));
    memset(ha,-1,sizeof(ha));
    tol = 1;
    id = 0;

    m = strlen(a[0]);
    int qq = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(b[i][j]=='L')
                qq++;

    int sum = n*m;
    s = sum<<1|1;
    t = s+1;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]>'0')
                add(get(i,j),get(i,j)+sum,a[i][j]-'0');
            if(b[i][j]=='L')
                add(s,get(i,j),1);
        }
    }

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            int temp = get(i,j)+sum;
            for(int k=0;k<size[d];k++){
                int x = i+dir[k][0];
                int y = j+dir[k][1];
                if(out(x,y))
                    add(temp,t,inf);
                else
                    add(temp,get(x,y),inf);
            }
        }
    return qq;
}


int main(){
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    for(int i=1;i<=ncase;i++){
        cin>>n>>d;
        int temp = build();
        temp -= sap();
        if(!temp)
            printf("Case #%d: no lizard was left behind.\n",i);
       else if(1!=temp)
            printf("Case #%d: %d lizards were left behind.\n",i,temp);
        else
            printf("Case #%d: 1 lizard was left behind.\n",i);

    }
    return 0;
}
