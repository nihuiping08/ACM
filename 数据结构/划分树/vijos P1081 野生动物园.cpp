/*

题目：
    顺便询问区间的第k大

分析：
    划分树的简单应用

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 32;
const int maxm = 100005;

int sorted[maxm],n,m;
int toleft[maxn][maxm],data[maxn][maxm];

void build(int l,int r,int depth){
    if(l==r)
        return;
    int mid = (l+r)>>1;
    int lp = l;
    int rp = mid+1;
    int ls = mid-l+1;
    for(int i=l;i<=r;i++)
        if(data[depth][i]<sorted[mid])
            ls--;
    int ok;
    for(int i=l;i<=r;i++){
        ok = 0;
        if(data[depth][i]<sorted[mid]||(data[depth][i]==sorted[mid]&&ls)){
            ok = 1;
            data[depth+1][lp++] = data[depth][i];
            if(data[depth][i]==sorted[mid])
                ls--;
        }
        else
            data[depth+1][rp++] = data[depth][i];
        toleft[depth][i] = toleft[depth][i-1]+ok;
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
    return query(mid+rx+1,mid+ry+1,k-cnt,mid+1,r,depth+1);
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        for(int i=1;i<=n;i++){
            scanf("%d",&sorted[i]);
            data[0][i] = sorted[i];
        }
        sort(sorted+1,sorted+n+1);
        build(1,n,0);
        int x,y,k;
        while(m--){
            scanf("%d%d%d",&x,&y,&k);
            printf("%d\n",query(x,y,k,1,n,0));
        }
    }
    return 0;
}
