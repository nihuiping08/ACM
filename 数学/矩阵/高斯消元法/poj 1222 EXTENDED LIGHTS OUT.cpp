/*

题目：
    关灯问题，按下开关，该灯和相邻的灯都会变化灯的状态，给出初始状态，问
    如何设置开关，使得灯的最终状态全为关闭的。。

分析：
    我们发现对于i灯，必有
    ai ^ xi ^ (A) = 0
    A为相邻的几个变量xj ^ xk ^ xl & xm(假设有四个)
    所以我们可以列出30个方程组出来。然后解方程组就行了

*/
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

#define rep(i,n) for(int i=0;i<n;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back

const int X = 35;
const int n = 30;

int a[X][X];

int dirx[4] = {-1,0,0,1};
int diry[4] = {0,-1,1,0};

void build(){
    rep(i,5){
        rep(j,6){
            int x = i*6+j;
            a[x][x] = 1;
            rep(k,4){
                int dx = dirx[k]+i;
                int dy = diry[k]+j;
                if(dx>=0&&dx<5 && dy>=0&&dy<6){
                    int y = dx*6+dy;
                    a[x][y] = 1;
                }
            }
        }
    }
}

void debug(){
    rep(i,30){
        rep(j,31)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
}

void gauss(){
    int i = 0,j = 0;
    while(i<n&&j<n){
        int r = i;
        for(int k=i;k<n;k++)
            if(a[k][j]){
                r = k;
                break;
            }
        if(a[r][j]){
            if(r!=i)
                rep(k,n+1)
                    swap(a[r][k],a[i][k]);
            for(int u=i+1;u<n;u++)
                if(a[u][j])
                    for(int k=j;k<n+1;k++)
                        a[u][k] ^= a[i][k];
            i ++;
        }
        j ++;
    }

    for(int i=n-2;i>=0;i--)
        for(int j=n-1;j>i;j--)
            a[i][n] ^= (a[i][j]&&a[j][n]);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    int ncase;
    cin>>ncase;
    rep(cnt,ncase){
        printf("PUZZLE #%d\n",cnt+1);
        memset(a,0,sizeof(a));
        rep(i,n)
            scanf("%d",&a[i][n]);
        build();
        gauss();
        rep(i,5){
            printf("%d",a[i*6][30]);
            for(int j=1;j<6;j++)
                printf(" %d",a[i*6+j][30]);
            puts("");
        }
    }
	return 0;
}
