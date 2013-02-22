/*

题目：
    有n个站，有m条路，每条路连接着两个站，每个站有两种颜色，只有两个
    路口的颜色相同才能够通过该路口到达另一个路口。给出起始点和终止点，
    问最少的时间，可到达的话输出路径

分析：
    单源最短路的变形。
    两个路口x,y，先从x到达y，有四种颜色组合，我们可以算出在t时刻每个路口
    该时刻的颜色，然后来推算出到达y路口所需的时间进行松弛。计算时间的话，
    可以使用递归的形式来计算出所需要等待的时间

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 305;
int INF;

struct junction{
    int tc;
    int c;
    int t[2];
    int tot;

    void read(){
        char op[2];
        scanf("%s%d%d%d",op,&tc,&t[0],&t[1]);
        tot = t[0]+t[1];
        c = (op[0]=='P');
    }
}p[X];

int src,dest;
int pre[X];
int dis[X];
int map[X][X];
int q[X*X];
bool use[X];
int n,m;

void out(int x){
    if(pre[x]){
        out(pre[x]);
        printf("%d ",pre[x]);
    }
}

bool get_color(int x,int t,int &res){
    bool c = p[x].c;
    if(t<p[x].tc){
        res = p[x].tc-t;
        return c;
    }
    res = (t-p[x].tc)%(p[x].t[0]+p[x].t[1]);

    if(res<p[x].t[!c]){
        res = p[x].t[!c]-res;
        return !c;
    }
    else{
        res = p[x].t[0]+p[x].t[1]-res;
        return c;
    }
}

int dfs(int x,int y,int t,int dep){
    if(dep>3)
        return INF;
    int res_x,res_y;
    bool cx = get_color(x,t,res_x);
    bool cy = get_color(y,t,res_y);
    if(cx==cy)
        return 0;
    if(res_x==res_y)
        return res_x + dfs(x,y,t+res_x,dep+1);
    return min(res_x,res_y);
}

void spfa(){
    memset(dis,0x3f,sizeof(dis));
    memset(use,false,sizeof(use));
    INF = dis[0];
    int head,tail;
    head = tail = pre[src] = dis[src] = 0;
    q[tail++] = src;
    while(head<tail){
        int x = q[head++];
        use[x] = false;
        for(int y=1;y<=n;y++){
            if(map[x][y]==0)
                continue;
            int tmp = dfs(x,y,dis[x],0)+dis[x]+map[x][y];
            if(tmp<dis[y]){
                pre[y] = x;
                dis[y] = tmp;
                if(!use[y]){
                    use[y] = true;
                    q[tail++] = y;
                }
            }
        }
    }
    if(dis[dest]>=INF){
        puts("0");
        return;
    }
    printf("%d\n",dis[dest]);
    out(dest);
    printf("%d\n",dest);
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
#endif

    while(~scanf("%d%d",&src,&dest)){
        memset(map,0,sizeof(map));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            p[i].read();
        int x,y,t;
        while(m--){
            scanf("%d%d%d",&x,&y,&t);
            map[x][y] = map[y][x] = t;
        }
        spfa();
    }
    return 0;
}

