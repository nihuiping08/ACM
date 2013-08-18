#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int X = 105;
const int INF = 100000000;
int map[X][X],dis[X][X],pre[X][X],path[X],n,po,ans;
void get_path(int i,int j){
    if(pre[i][j]){
        get_path(i,pre[i][j]);
        get_path(pre[i][j],j);
    }
    else
        path[po++] = i;
}
void floyd(){
    ans = INF;
    int temp;
    memset(pre,0,sizeof(pre));
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                temp = dis[i][j]+map[j][k]+map[k][i];
                if(i!=j&&i!=k&&j!=k&&temp<ans){
                    ans = temp;
                    po = 0;
                    get_path(i,j);
                    path[po++] = j;
                    path[po++] = k;
                }
            }
        }

        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(i!=j&&i!=k&&j!=k&&dis[i][j]>dis[i][k]+dis[k][j]){
                    dis[i][j] = dis[i][k]+dis[k][j];
                    pre[i][j] = k;
                }
    }
}
void print(){
    if(ans==INF)
        printf("No solution.\n");
    else{
        for(int i=0;i<po-1;i++)
            printf("%d ",path[i]);
        cout<<path[po-1]<<endl;
    }
}
int main(){
    int x,y,z,m;
    while(cin>>n,n!=-1){
        cin>>m;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dis[i][j] = map[i][j] = INF;
        while(m--){
            scanf("%d%d%d",&x,&y,&z);
            if(map[x][y]>z)
                dis[x][y] = dis[y][x] = map[x][y] = map[y][x] = z;
        }
        floyd();
        print();
    }

    return 0;
}