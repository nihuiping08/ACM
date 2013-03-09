/*

题目：给出prufer编码，给出一棵合法的树
分析：每次选出度为0的点，然后对应当前的编码连边即可

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 155;

int in[MAXN];
int map[MAXN][MAXN];
int a[MAXN],n;

void dfs(int x){
    cout<<'('<<x;
    rep1(y,n)
        if(map[x][y]){
            cout<<' ';
            map[x][y] = map[y][x] = 0;
            dfs(y);
        }
    cout<<')';
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    char s[500];
    while(gets(s)){
        //puts("---------------------");
        memset(in,0,sizeof(in));
        int len = strlen(s);
        if(len==0){
            puts("(1)");
            continue;
        }
        n = 0;
        for(int i=0;i<len;){
            if(isdigit(s[i])){
                int num = 0;
                while(i<len&&isdigit(s[i]))
                    num = num*10+s[i++]-'0';
                a[++n] = num;
                in[num] ++;
            }
            i ++;
        }
        if(n==1){
            cout<<"(2 (1))"<<endl;
            continue;
        }

        n ++;
        memset(map,0,sizeof(map));

        for(int i=1;i<n;i++){
            int x = 1;
            while(in[x]!=0)
                x ++;
            //cout<<"dsa "<<x<<endl;
            in[x] ++;
            map[x][a[i]] = map[a[i]][x] = 1;
            in[a[i]] --;
        }
        /*
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)
                if(map[i][j])
                    cout<<i<<" "<<j<<endl;
        */

        dfs(n);
        puts("");
    }
	return 0;
}
