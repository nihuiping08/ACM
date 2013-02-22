/*
 *	分析：
 *		典型的2-SAT问题，只需要对于不喜欢与喜欢之间建立有向边即可
 *		某人喜欢h1,h2,所以如果做了m1的话，必须做h2才不会被否决，同样，做了m2的话，必须得要做h1，
 *		建立模型之后，直接强连通求缩点，判断两个互斥的hi,mi是否是同一个连通分量即可
 *
 * */
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 10005;

struct node{
	int y,next;
}edge[X];

int po[X],tol;
int father[X],dfn[X],low[X],stack[X],bcnt,depth,top;
bool instack[X];
int n,m;

void add(int x,int y){
	edge[++tol].y = y;
	edge[tol].next = po[x];
	po[x] = tol;
}

void dfs(int x){
	low[x] = dfn[x] = ++depth;
	stack[++top] = x;
	instack[x] = true;
	int y;
	for(int i=po[x];i;i=edge[i].next){
		y = edge[i].y;
		if(!dfn[y]){
			dfs(y);
			low[x] = min(low[x],low[y]);
		}
		else if(instack[y])
			low[x] = min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		++ bcnt;
		do{
			y = stack[top--];
			instack[y] = false;
			father[y] = bcnt;
		}while(x!=y);
	}
}

bool tarjan(){
	memset(instack,false,sizeof(instack));
	memset(dfn,0,sizeof(dfn));
	top = depth = bcnt = 0;
	for(int i=1;i<=n*2;i++)
		if(!dfn[i])
			dfs(i);
	/*
	for(int i=1;i<=n;i++){
		cout<<i<<"  "<<father[i]<<endl;
		cout<<i+n<<"  "<<father[i+n]<<endl;
		cout<<endl;
	}
	cout<<"bcnt = "<<bcnt<<endl;*/
	for(int i=1;i<=n;i++)
		if(father[i]==father[i+n])
			return false;
	return true;
}

int main(){
	int ncase;
	char a,b;
	int x,y;
	cin>>ncase;
	while(ncase--){
		scanf("%d%d ",&n,&m);
		memset(po,0,sizeof(po));
		tol = 0;
		for(int i=0;i<m;i++){
			scanf("%c%d %c%d ",&a,&x,&b,&y);
			if(a=='h'){
				if(b=='h'){
					add(x+n,y);
					add(y+n,x);
				}
				else{
					add(x+n,y+n);
					add(y,x);
				}
			}
			else{
				if(b=='h'){
					add(x,y);
					add(y+n,x+n);
				}
				else{
					add(x,y+n);
					add(y,x+n);
				}
			}
		}
		if(tarjan())
			puts("GOOD");
		else
			puts("BAD");
	}
	return 0;
}
