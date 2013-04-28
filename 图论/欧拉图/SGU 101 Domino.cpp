#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 205;

struct node{
	int y,id,next;
}edge[X];

int po[X],tol;
int id[X];
bool use[X];

void add(int x,int y,int id){
	edge[++tol].y = y;
	edge[tol].id = id;
	edge[tol].next = po[x];
	po[x] = tol;
}

int Abs(int x){
	return max(x,-x);
}

void is_uler(int x){
	for(int i=po[x];i;i=edge[i].next){
		int y = Abs(edge[i].id);
		if(!use[y]){
			use[y] = true;
			is_uler(edge[i].y);
		}
	}
}

void dfs(int x){
	for(int i=po[x];i;i=edge[i].next){
		int y = Abs(edge[i].id);
		if(!use[y]){
			use[y] = true;
			dfs(edge[i].y);
			printf("%d %c\n",y,edge[i].id>0?'-':'+');
		}
	}
}

int main(){
	freopen("sum.in","r",stdin);
	int m;
	int id[X];
	while(cin>>m){
		memset(id,0,sizeof(id));
		memset(po,0,sizeof(po));
		tol = 0;
		int x,y;
		for(int i=1;i<=m;i++){
			scanf("%d%d",&x,&y);
			id[x] ++;
			id[y] ++;
			add(x,y,i);
			add(y,x,-i);
		}
		int cnt = 0;
		x = -1;
		for(int i=0;i<7;i++)
			if(id[i]&1){
				x = i;
				cnt ++;
			}

		if(cnt&&cnt!=2){
			puts("No solution");
			continue;
		}

		for(int i=0;i<7&&cnt==0;i++)
			if(id[i]){
				x = i;
				break;
			}

		memset(use,false,sizeof(use));
		is_uler(x);
		//cout<<x<<endl;
		bool ok = true;
		for(int i=1;i<=m;i++)
			if(!use[i]){
				ok = false;
				puts("No solution");
				break;
			}
		if(ok){
			memset(use,false,sizeof(use));
			dfs(x);
		}
	}
	return 0;
}
