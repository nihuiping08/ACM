/*

�Ժ���������Ϊģ��ɡ�

*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int X = 1005;
const int INF = 100000000;

int map[X][X],dis[X],n,m;
int q[X];
bool use[X];

void spfa(int s){
    int h = 0,t = 1,x;  //hΪͷָ��,tΪβָ��

    memset(q,0,sizeof(q));
    memset(use,false,sizeof(use));

    for(int i=1;i<=n;i++)
        dis[i] = INF;

    dis[s] = 0;
    use[s] = true;
    q[t] = s;

    while(h!=t){    //������h<t,����ѭ������
        h = (h+1)%(n+1);//���ﲻ��%n��������Ͷӿ�״̬һ��
        x = q[h];
        use[x] = false;
        for(int i=1;i<=n;i++)
            if(dis[i]-map[x][i]>dis[x]) {//dist[i]>dist[x]+a[x][i]��Խ���
                dis[i] = dis[x]+map[x][i];
                if(!use[i]){
                    t = (t+1)%(n+1);
                    use[i] = true;
                    q[t] = i;
                }
            }
    }
}
int main(){
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    cin>>m>>n;
    int x,y,z;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            map[i][j] = INF;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        if(map[x][y]>z)
            map[x][y] = map[y][x] = z;
    }
    spfa(1);
    cout<<dis[n]<<endl;
    return 0;
}
