/*
 *	分析：
 *		平面图最小割转化为最短路问题。
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int X = 1000002*2;
const int inf = 1e9;

#define debug puts("here");

int id[2][1001][1001];

struct node{
	int y,dis,next;
}edge[X*6];

int ds,dt,tot;
int n,m;
int dis[X];
int po[X],tol;

void add(int x,int y,int w){
	edge[++tol].y = y;
	edge[tol].dis = w;
	edge[tol].next = po[x];
	po[x] = tol;

	edge[++tol].y = x;
	edge[tol].dis = w;
	edge[tol].next = po[y];
	po[y] = tol;
}

void build(){
	tot = 0;
	for(int j=1;j<n;j++)
		for(int k=1;k<m;k++)
			for(int i=0;i<2;i++)
				id[i][j][k] = ++tot;
	ds = ++ tot;
	dt = ++ tot;
	
	memset(po,0,sizeof(po));
	tol = 0;
	int w;
	
	int ok = 0;
	int check = n*(m-1)+(n-1)*m+(n-1)*(m-1);
	/***********  1  ******************/
	for(int i=1;i<m;i++){
		scanf("%d",&w);
		ok ++;
		add(id[1][1][i],dt,w);
	}

	for(int i=2;i<n;i++){
		for(int j=1;j<m;j++){
			scanf("%d",&w);
			ok ++;
			add(id[0][i-1][j],id[1][i][j],w);
		}
	}

	for(int i=1;i<m;i++){
		scanf("%d",&w);
		add(ds,id[0][n-1][i],w);
		ok ++;
	}
	/***********  1  ******************/

	/***********  2  ******************/	
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&w);
			ok ++;
			if(j==1)
				add(ds,id[0][i][1],w);
			else if(j==m)
				add(id[1][i][m-1],dt,w);
			else
				add(id[0][i][j],id[1][i][j-1],w);
		}
	}
	/***********  2  ******************/
	
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			if(ok>=check)
				debug;
			scanf("%d",&w);
			add(id[1][i][j],id[0][i][j],w);
			ok ++;
		}
	}
}

struct state{
	int x,w;
	state(){}
	state(int _x,int _w):x(_x),w(_w){}
	friend bool operator < (state a,state b){
		return a.w > b.w;
	}
};

priority_queue<state> q;

int dijkstra(){
	while(q.size())
		q.pop();
	for(int i=1;i<=tot;i++)
		dis[i] = inf;
	dis[ds] = 0;
	q.push(state(ds,0));
	while(q.size()){
		state tmp = q.top();;
		q.pop();
		int x = tmp.x;
		if(tmp.w>dis[x])
			continue;
		if(x==dt)
			return tmp.w;
		for(int i=po[x];i;i=edge[i].next){
			int y = edge[i].y;
			int cur = dis[x]+edge[i].dis;
			if(cur < dis[y]){
				dis[y] = cur;
				q.push(state(y,cur));
			}
		}
	}
	return -1;
}

int main(){
	while(cin>>n>>m){
		if(n==1||m==1){
			int ans = inf;
			int x;
			for(int i=1;i<max(n,m);i++){
				scanf("%d",&x);
				ans = min(ans,x);
			}
			cout<<ans<<endl;
			continue;
		}
		build();
		cout<<dijkstra()<<endl;
	}
	return 0;
}
