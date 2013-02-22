/*

题目：
    现在有n个0，给出n个区间0的个数为奇数还是偶数，问给出的区间最早出现矛盾的
    前一个位置是哪个位置

分析:
    区间减法，就是sum[i,j] = sum[j]-sum[i-1]，用并查集的方式表示区间[i,j]中
    i-1与j奇偶关系，然后判断合适出现矛盾即可

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>

using namespace std;

const int X = 20000;
#define debug puts("here");

int n,p[X];

int find_set(int x){
    if(x!=p[x])
        p[x] = find_set(p[x]);
    return p[x];
}

void union_set(int x,int y){
    x = find_set(x);
    y = find_set(y);
    if(x!=y)
        p[x] = y;
}

bool solve(int x,int y,int ok){
    if(ok){
        if(find_set(x)==find_set(y))
            return false;
        union_set(x,y+n);
        union_set(x+n,y);
    }
    else{
        if(find_set(x)==find_set(y+n))
            return false;
        union_set(x,y);
        union_set(x+n,y+n);
    }
    return true;
}

int main(){
    freopen("sum.in","r",stdin);
    int len,x,y;
    char s[10];
    while(cin>>len>>n,len!=-1){
        for(int i=0;i<X;i++)
            p[i] = i;
        map<int,int> ma;
        int tol = 0;
        int ok,ans = n;
        bool flag = true;
        int m = n;
        n = n<<1;
        for(int i=1;i<=m;i++){
            scanf("%d%d%s",&x,&y,s);
            if(!flag)
                continue;
            ok = 1;
            if(s[0]=='e')
                ok = 0;
            if(ma[x-1])
                x = ma[x-1];
            else{
                ma[x-1] = ++tol;
                x = tol;
            }
            if(ma[y])
                y = ma[y];
            else{
                ma[y] = ++tol;
                y = tol;
            }
            flag = solve(x,y,ok);
            if(!flag)
                ans = i-1;
        }
        cout<<ans<<endl;
    }

    return 0;
}
