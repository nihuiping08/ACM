/*

从A都要到达B和C两地有两种走法：
A - B - C
A - C - B，
现在给出某些顶点和边权（边有重复边），问最小需要走的距离，若某两地没有通路，输出-1

分析：
    直接用两次dijkstra算法求到dis_a_b和dis_a_c和dis_b_c即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 1005
#define INF 1<<29
int map[X][X],dis[X],n,m;
bool use[X];
void dijkstra(int s)//起点为s，dijkstra模板
{
    memset(use,false,sizeof(use));
    for(int i=0;i<n;i++)
        dis[i] = INF;
    dis[s] = 0;
    int MIN,k;
    for(int i=0;i<n;i++)
    {
        MIN = INF;
        for(int j=0;j<n;j++)
            if(!use[j]&&dis[j]<MIN)
                MIN = dis[k=j];
        use[k] = true;
        for(int j=0;j<n;j++)
            if(!use[j])
                dis[j] = min(dis[j],dis[k]+map[k][j]);
    }
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int x,y,z;
    while(cin>>n>>m)
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                map[i][j] = INF;//有重复边
        while(m--)
        {
            scanf("%d%d%d",&x,&y,&z);
            map[x][y] = map[y][x] = min(map[x][y],z);//取最小的边权
        }
        scanf("%d%d%d",&x,&y,&z);
        dijkstra(x);            //第一次
        int ans_x_y = dis[y];
        int ans_x_z = dis[z];
        if(ans_x_y>=INF||ans_x_z>=INF)
        {
            cout<<-1<<endl;
            continue;
        }
        dijkstra(y);            //第二次
        int ans_y_z = dis[z];
        if(ans_y_z>=INF)
        {
            cout<<-1<<endl;
            continue;
        }
        int MAX = min(ans_x_y+ans_y_z,ans_x_z+ans_y_z);//取两种走法的最小值
        cout<<MAX<<endl;
    }

    return 0;
}
