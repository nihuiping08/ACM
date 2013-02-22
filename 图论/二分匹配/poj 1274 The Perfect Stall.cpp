/*

题目：
    每头奶牛都有自己喜欢产奶的房子，问最多能够满足多少头奶牛

分析：
    裸的二分图最大匹配

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 205;

int xm[X];
bool map[X][X],use[X];
int n,m;

bool dfs(int x){
    for(int y=1;y<=m;y++)
        if(map[x][y]&&!use[y]){
            use[y] = true;
            if(xm[y]==-1||dfs(xm[y])){
                xm[y] = x;
                return true;
            }
        }
    return false;
}

int hungry(){
    memset(xm,-1,sizeof(xm));
    int ret = 0;
    for(int i=1;i<=n;i++){
        memset(use,false,sizeof(use));
        if(dfs(i))
            ret++;
    }
    return ret;
}

int main(){
    freopen("sum.in","r",stdin);
    int x,y;
    while(cin>>n>>m){
        memset(map,0,sizeof(map));
        for(int i=1;i<=n;i++){
            scanf("%d",&y);
            while(y--){
                scanf("%d",&x);
                map[i][x] = true;
            }
        }
        cout<<hungry()<<endl;
    }
    return 0;
}
