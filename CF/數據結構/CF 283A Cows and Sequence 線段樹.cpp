/*

題目：
    支持三種操作：
    1.a b，對於前a個數都加上b
    2.a，在數列末尾加上一個數a
    3.表示把數列最後一個數刪除

分析：
    線段樹區間操作

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
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

const int MAXN = 2e5+5;
const int INF = 1e9;

struct node{
    int l,r;
    ll sum,add;
    int mid(){
        return (l+r)>>1;
    }
    int dis(){
        return r-l+1;
    }
}tree[MAXN<<2];

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].add = tree[rt].sum = 0;
    if(l==r)
        return;
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
}

void push_down(int rt){
    tree[rt<<1].add += tree[rt].add;
    tree[rt<<1|1].add += tree[rt].add;
    tree[rt].add = 0;
}

void push_up(int rt){
    ll tmp = tree[rt<<1].sum+tree[rt<<1].dis() * tree[rt<<1].add;
    ll ret = tree[rt<<1|1].sum+tree[rt<<1|1].dis() * tree[rt<<1|1].add;
    tree[rt].sum = tmp+ret;
}

void update(int l,int r,int val,int rt){
    if(tree[rt].l==l&&tree[rt].r==r){
        if(val==INF){
            tree[rt].add = tree[rt].sum = 0;
            return;
        }
        tree[rt].add += val;
        return;
    }
    push_down(rt);
    int mid = tree[rt].mid();
    if(r<=mid)
        update(l,r,val,rt<<1);
    else if(l>mid)
        update(l,r,val,rt<<1|1);
    else{
        update(l,mid,val,rt<<1);
        update(mid+1,r,val,rt<<1|1);
    }
    push_up(rt);
}

ll ask(int l,int r,int rt){
    if(l==tree[rt].l&&tree[rt].r==r)
        return tree[rt].sum + tree[rt].dis()*tree[rt].add;
    push_down(rt);
    int mid = tree[rt].mid();
    if(r<=mid)
        return ask(l,r,rt<<1);
    else if(l>mid)
        return ask(l,r,rt<<1|1);
    else
        return ask(l,mid,rt<<1)+ask(mid+1,r,rt<<1|1);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,op,x,y;
    bool ok = false;
    while(~RD(n)){
        ok?puts(""):ok = true;
        build(1,n+1,1);
        int tot = 1;
        update(1,1,0,1);
        while(n--){
            RD(op);
            //cout<<n<<" "<<op<<" ";
            if(op==1){
                RD2(x,y);
                update(1,x,y,1);
            }else if(op==2){
                RD(x);
                tot ++;
                update(tot,tot,x,1);
            }else{
                update(tot,tot,INF,1);
                tot --;
            }
            printf("%.6lf\n",ask(1,tot,1)*1.0/tot);
        }
    }

	return 0;
}
