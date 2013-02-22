/*

题目：
	uva 10054 The Necklace
	珠子由两部分组成，每个部分都有颜色，若相同颜色的两个珠子可以串连在一起，现在问能不能把所有的珠子
	串连在一起。若能够，给出串联的方式

分析:
    求欧拉回路，把每种颜色看做图上的一个顶点，然后对于每个珠子构造一条无向边，先判断是否有奇数度的顶点，
	若有的话，欧拉回路不存在，否则DFS一次即可。另外注意图中可能存在多条相同的边（我没测过），所以每次
	DFS的时候把边删掉一条即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 60;
const int n = 50;

int map[X][X];
int id[X];
int m;

void dfs(int x){
    for(int y=1;y<=n;y++){
        if(map[x][y]>0){
            map[x][y] --;
            map[y][x] --;
            dfs(y);
            cout<<y<<" "<<x<<endl;
        }
    }
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase,x,y,cnt = 0;
    cin>>ncase;
    while(ncase--){
        if(cnt)
            puts("");
        printf("Case #%d\n",++cnt);
        memset(map,0,sizeof(map));
        memset(id,0,sizeof(id));
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&x,&y);
            map[x][y] ++;
            map[y][x] ++;

            id[x] ++;
            id[y] ++;
        }
        bool ok = true;
        for(int i=1;i<=n;i++){
            if(id[i]&1){
                ok = false;
                puts("some beads may be lost");
                break;
            }
        }
        if(!ok)
            continue;
        dfs(x);
    }
    return 0;
}
