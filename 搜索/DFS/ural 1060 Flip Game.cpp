/*

题目：
    翻转每个格子的时候，会使得相邻的四个格子全部翻转，然后问最终状态
    为全部统一种颜色的时候的最小翻转次数

分析：
    dfs加剪枝，类似于木棍？

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 5;
const int n = 4;
const int inf = 1e9;

#define debug puts("here");

int a[X][X];
char s[X];
int ans;

int dirx[4] = {-1,1,0,0};
int diry[4] = {0,0,1,-1};

bool ok(){
    int ans = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            ans += a[i][j];
    return ans==0||ans==16;
}

bool out(int x,int y){
    return x<0||y<0||x>=n||y>=n;
}

void flip(int x,int y){
    a[x][y] = a[x][y]^1;
    for(int i=0;i<4;i++){
        int dx = x+dirx[i];
        int dy = y+diry[i];
        if(!out(dx,dy))
            a[dx][dy] = a[dx][dy]^1;
    }
}

void dfs(int pos,int dep){
    if(ok()){
        ans = min(ans,dep);
        return;
    }
    if(pos>=16)
        return;
    if(dep>=ans)
        return;
    int x = pos/4;
    int y = pos%4;
    flip(x,y);
    dfs(pos+1,dep+1);
    flip(x,y);
    dfs(pos+1,dep);
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>s){
        for(int i=0;i<n;i++)
            a[0][i] = s[i]=='w';
        for(int j=1;j<4;j++){
            cin>>s;
            for(int i=0;i<n;i++)
                a[j][i] = s[i]=='w';
        }
        ans = inf;
        dfs(0,0);
        if(ans==inf)
            puts("Impossible");
        else
            cout<<ans<<endl;
    }
    return 0;
}
