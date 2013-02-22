/*

��A��Ҫ����B��C�����������߷���
A - B - C
A - C - B��
���ڸ���ĳЩ����ͱ�Ȩ�������ظ��ߣ�������С��Ҫ�ߵľ��룬��ĳ����û��ͨ·�����-1

������
    ֱ��������dijkstra�㷨��dis_a_b��dis_a_c��dis_b_c����

*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 1005
#define INF 1<<29
int map[X][X],dis[X],n,m;
bool use[X];
void dijkstra(int s)//���Ϊs��dijkstraģ��
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
                map[i][j] = INF;//���ظ���
        while(m--)
        {
            scanf("%d%d%d",&x,&y,&z);
            map[x][y] = map[y][x] = min(map[x][y],z);//ȡ��С�ı�Ȩ
        }
        scanf("%d%d%d",&x,&y,&z);
        dijkstra(x);            //��һ��
        int ans_x_y = dis[y];
        int ans_x_z = dis[z];
        if(ans_x_y>=INF||ans_x_z>=INF)
        {
            cout<<-1<<endl;
            continue;
        }
        dijkstra(y);            //�ڶ���
        int ans_y_z = dis[z];
        if(ans_y_z>=INF)
        {
            cout<<-1<<endl;
            continue;
        }
        int MAX = min(ans_x_y+ans_y_z,ans_x_z+ans_y_z);//ȡ�����߷�����Сֵ
        cout<<MAX<<endl;
    }

    return 0;
}
