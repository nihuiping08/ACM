/*

題目：
    有n把鑰匙，現在每把鑰匙能夠開ai,bi兩種門，並且所有ai或者bi能夠開的門都
    可以用它來開。但是每把鑰匙只能夠選擇一種開門的方式(即ai,bi只能夠選擇一
    種)。並且每個門可以用ci,di兩種鑰匙來開，並且只需要一種就能夠把門打開。
    現在從0開始開門，問能夠用上面的鑰匙最多能夠開多少所門。

分析：
    2-sat。
    對於每種鑰匙，分成開和不開兩種，所以一共有4*n的點。

    建圖：
    1...2*n表示用鑰匙種類i
    2*n+1...4*n，表示不用該鑰匙種類
    1.對於每把鑰匙每把鑰匙:
        若是選了ai,則ai-(bi+2*n)連邊。
        否則選了bi,把bi-(ai+2*n)連邊。
    2.對於門ci,di:
        連邊：ci-(di+2*n)  ,  di-(ci+2*n)
        表示只用一把鑰匙就可以把該門打開

*/
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
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)
#define Abs(x) max(x,-x)

const int MAXN = 5000;

vector<int> vec[MAXN];
int fa[MAXN],low[MAXN],dfn[MAXN],sta[MAXN],bcnt,depth,top;
bool use[MAXN];
int n,m;

void dfs(int x){
    low[x] = dfn[x] = ++ depth;
    sta[++top] = x;
    use[x] = true;
    int y;
    foreach(i,vec[x]){
        y = vec[x][i];
        if(!dfn[y]){
            dfs(y);
            low[x] = min(low[x],low[y]);
        }else if(use[y])
            low[x] = min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        ++ bcnt;
        do{
            y = sta[top--];
            use[y] = false;
            fa[y] = bcnt;
        }while(x!=y);
    }
}

void tarjan(){
    memset(use,false,sizeof(use));
    memset(dfn,0,sizeof(dfn));
    bcnt = depth = top = 0;
    int tmp = n<<1;
    rep1(i,tmp)
        if(!dfn[i])
            dfs(i);
}

bool sat(){
    tarjan();
    rep1(i,n)
        if(fa[i]==fa[i+n])
            return false;
    return true;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y;
    while(RD2(n,m),n||m){
        n <<= 1;
        rep1(i,n<<1)
            vec[i].clear();

        rep1(i,n>>1){
            RD2(x,y);
            x ++;
            y ++;
            vec[x].pb(y+n);
            vec[y].pb(x+n);
        }
        int ans = 0;
        bool ok = false;
        while(m--){
            RD2(x,y);
            if(ok)
                continue;
            x ++;
            y ++;
            vec[x+n].pb(y);
            vec[y+n].pb(x);
            if(sat())
                ans ++;
            else
                ok = true;
        }
        cout<<ans<<endl;
    }

	return 0;
}
