#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 350;
const int maxm = 100000;
const int inf = 1000000000;
#define debug puts("here");

int n,m,s,t;
int map[maxn][maxn],kk,mm,cc;
int gap[maxn],arc[maxn],cf[maxn],dis[maxn],pre[maxn];
int po[maxn],tol;

struct node{
	int y,f,next;
}edge[maxm];

int sap(){
	 memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    gap[0] = n;
    for(int i=1;i<=n;i++)
        arc[i] = po[i];
    int MIN;
    int ans = 0;
    bool ok;
    int aug = inf;
    int i = s;

    while(dis[s]<n){
        cf[i] = aug;
        ok = false;
        for(int j=arc[i];j;j=edge[j].next){
            if(edge[j].f>0&&dis[edge[j].y]+1==dis[i]){
                ok = true;
                if(aug>edge[j].f)
                    aug = edge[j].f;
                arc[i] = j;
                i = edge[j].y;
                pre[i] = j;
                if(i==t){
                    ans += aug;
                    for(;i!=s;i=edge[pre[i]^1].y){
                        edge[pre[i]].f -= aug;
                        edge[pre[i]^1].f += aug;
                    }
                    aug = inf;
                }
                break;
            }
        }
        if(ok)
            continue;
        MIN = n-1;
        for(int j=po[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]<MIN){
                MIN = dis[edge[j].y];
                arc[i] = j;
            }
        if(--gap[dis[i]]==0)
            break;
        dis[i] = MIN+1;
        gap[dis[i]]++;
        if(i!=s){
            i = edge[pre[i]^1].y;
            aug = cf[i];
        }
    }

	return ans;
}

void add(int x,int y,int f){
	edge[++tol].y = y;
	edge[tol].f = f;
	edge[tol].next = po[x];
	po[x] = tol;

	edge[++tol].y = x;
	edge[tol].f = 0;
	edge[tol].next = po[y];
	po[y] = tol;
}

void build(int mid){
	memset(po,0,sizeof(po));
	tol = 1;
	for(int i=1;i<=kk;i++)
		for(int j=kk+1;j<=kk+cc;j++)
			if(map[i][j]<=mid)
				add(i,j,map[i][j]);
	for(int i=1;i<=kk;i++)
		add(s,i,mm);
	for(int i=1+kk;i<=cc+kk;i++)
		add(i,t,1);
}

void binary(){
	int l = 0,r = 1000000;
	int mid;
	s = kk+cc+1;
	n = t = s+1;

	while(l<r){
		mid = (r+l)>>1;
		build(mid);
		int temp = sap();
		//cout<<temp<<endl;
		if(temp==cc)
			r = mid;
		else
			l = mid+1;
	}
	cout<<r<<endl;
}

void floyd(){
	for(int k=1;k<=kk+cc;k++)
		for(int i=1;i<=kk+cc;i++)
			if(map[i][k]!=inf)
				for(int j=1;j<=kk+cc;j++)
					map[i][j] = min(map[i][j],map[i][k]+map[k][j]);
}

void init(){
	for(int i=1;i<=kk+cc;i++)
		for(int j=1;j<=kk+cc;j++){
			scanf("%d",&map[i][j]);
			if(!map[i][j])
				map[i][j] = inf;
		}
}

int main(){
	while(cin>>kk>>cc>>mm){
	    //cout<<kk<<" "<<cc<<endl;
		init();
		floyd();
		binary();
	}
	return 0;
}