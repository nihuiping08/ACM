#include <set>
#include <map>
#include <list>
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
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>
#define PQ priority_queue
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)
#define Clear(x) memset(x,0,sizeof(x))
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 5e5;
const int kind = 26;

char t[2000005];
char s[1005][52];
int use[1005];

struct AC{
    int ch[MAXN][kind],fail[MAXN],last[MAXN];
    int ed[MAXN],tot;

    void init(){
        Clear(ch[0]);
        ed[0] = fail[0] = last[0] = 0;
        tot = 0;
    }

    int newNode(){
        int x = ++ tot;
        Clear(ch[x]);
        ed[x] = last[x] = fail[x] = 0;
        return x;
    }

    int ind(char c){
        return c-'A';
    }

    void insert(char *s,int id){
        int r = 0;
        for(int i=0;s[i];i++){
            int c = ind(s[i]);
            if(ch[r][c]==0)
                ch[r][c] = newNode();
            r = ch[r][c];
        }
        ed[r] = id;
    }

    void build(){
        queue<int> q;
        fail[0] = 0;
        rep(c,kind){
            int x = ch[0][c];
            if(x){
                fail[0] = 0;
                last[x] = 0;
                q.push(x);
            }
        }
        while(!q.empty()){
            int r = q.front();
            q.pop();
            rep(c,kind){
                int x = ch[r][c];
                if(!x){
                    ch[r][c] = ch[ fail[r] ][c];
                    continue;
                }
                q.push(x);
                int y = fail[r];
                while( y && ch[y][c]==0 )
                    y = fail[y];
                fail[x] = ch[y][c];
                last[x] = ed[ fail[x] ]?fail[x]:last[ fail[x] ];
            }
        }
    }

    void run(char *s){
        int r = 0;
        for(int i=0;s[i];i++){

            if(s[i]>'Z'||s[i]<'A'){
                r = 0;
                continue;
            }

            int c = ind(s[i]);
            r = ch[r][c];

            int x = 0;
            if(ed[r])
                x = r;
            else if( last[r] )
                x = last[r];

            while(x){
                use[ ed[x] ] ++;
                x = last[x];
            }
        }
    }
}ac;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(cin>>n){
        ac.init();
        rep1(i,n){
            scanf("%s",s[i]);
            ac.insert(s[i],i);
        }
        ac.build();

        memset(use,0,sizeof(use));
        scanf("%s",t);
        ac.run(t);
        rep1(i,n)
            if(use[i])
                printf("%s: %d\n",s[i],use[i]);
    }

	return 0;
}
