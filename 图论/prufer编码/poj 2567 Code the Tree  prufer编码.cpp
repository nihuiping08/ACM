/*

题目：
1. 一棵标号树的Pufer编码规则如下：找到标号最小的叶子节点，输出与它相邻的节点到prufer 序列, 
将该叶子节点删去，反复操作，直至剩余2个节点。

2. 由Pufer编码生成树：任何一个prufer 序列可以唯一对应到一棵有标号的树，首先标记所有节点为未删除
 依次扫描prufer 序列中的数，比如当前扫描到第k个数u，说明有一个叶子节点连到u，并在当前操作中被删除，
 找一个标号最小的未被标记为删除的且在prufer 序列第k个位置后未出现过的节点v，在u,v间连边并将v删除，
 反复操作，最后剩两个节点未被标记为删除，在它们之间连边，这样得到的一个图含有n-1条边则是一棵树

 3. 一棵树N个结点，其Profer序列有N-2个位置，因此可以在这N-2个位置里面任何的填充1～N之间的数形成一
个prufer序列，且一个prufer序列唯一的对应一颗生成树，于是完全图的最小生成树的数目为N^(N-2)

*/
#include <string>
#include <vector>
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

const int MAXN = 55;

string s;
int in[MAXN];
int vec[MAXN][MAXN];
int n,len,pos;

int dfs(){
    int num = -1;
    while(1){
        if(isdigit(s[pos])){
            num = 0;
            while(pos<len && isdigit(s[pos]))
                num = num*10+s[pos++]-'0';
            n = max(num,n);
        }else if(s[pos]==' ')
            pos ++;
        else if(s[pos]=='('){
            pos ++;
            int tmp = dfs();
            in[tmp] ++;
            in[num] ++;
            vec[num][tmp] = 1;
            vec[tmp][num] = 1;
        }else{
            pos ++;
            break;
        }
    }
    return num;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(getline(cin,s)){
        memset(vec,0,sizeof(vec));
        len = s.size();

        n = 0;
        pos = 1;
        memset(in,0,sizeof(in));
        dfs();
        bool ok = false;
        for(int i=1;i<n;i++){
            int x = 1;
            while(in[x]!=1)
                x ++;

            rep1(y,n)
                if(vec[x][y]){
                    ok?putchar(' '):ok = 1;
                    cout<<y;
                    vec[x][y] = vec[y][x] = 0;
                    in[y] --;
                }
            in[x] = 0;
        }
        puts("");
    }
	return 0;
}
