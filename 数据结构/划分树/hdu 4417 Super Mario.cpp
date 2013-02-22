#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxm = 2e5+10;
const int maxn = 42;
#define debug puts("here");

int toleft[maxn][maxm],data[maxn][maxm],sorted[maxm];
int n,m;

void build(int l,int r,int depth){
    if(l==r)
        return;
    int mid = (r+l)>>1;
    int ls = l;
    int rs = mid+1;
    int lsame = mid-l+1;

    for(int i=l;i<=r;i++)
        if(sorted[mid]>data[depth][i])
            lsame --;
    for(int i=l;i<=r;i++){
        int id = 0;
        if(data[depth][i]<sorted[mid]||(data[depth][i]==sorted[mid]&&lsame>0)){
            data[depth+1][ls++] = data[depth][i];
            id = 1;
            if(data[depth][i]==sorted[mid])
                lsame--;
        }
        else
            data[depth+1][rs++] = data[depth][i];
        toleft[depth][i] = toleft[depth][i-1]+id;
    }
    build(l,mid,depth+1);
    build(mid+1,r,depth+1);
}

int query(int left,int right,int k,int l,int r,int depth){
    if(left==right)
        return data[depth][left];
    int mid = (l+r)>>1;
    int x = toleft[depth][left-1]-toleft[depth][l-1];
    int y = toleft[depth][right]-toleft[depth][l-1];
    int rx = left-l-x;
    int ry = right-l-y;
    int cnt = y-x;

    if(cnt>=k)
        return query(l+x,l+y-1,k,l,mid,depth+1);
    else
        return query(mid+rx+1,mid+ry+1,k-cnt,mid+1,r,depth+1);
}

void bs(int x,int y,int val){
    int l = 0;
    int r = y-x+1;
    int ans = 0;
    while(l<r){
        int mid = (l+r)>>1;
        int temp = query(x,y,mid,1,n,0);
        if(temp<=val){
            l = mid+1;
            ans = mid;
        }
        else
            r = mid;
    }
    if(query(x,y,l,1,n,0)<=val)
        ans++;
    printf("%d\n",ans);
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase,cnt = 0;
    cin>>ncase;
    while(ncase--){
        printf("Case %d:\n",++cnt);
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%d",&sorted[i]);
            data[0][i] = sorted[i];
        }
        sort(sorted+1,sorted+n+1);
        build(1,n,0);
        int x,y,z;
        while(m--){
            scanf("%d%d%d",&x,&y,&z);
            bs(++x,++y,z);
        }
    }
    return 0;
}
