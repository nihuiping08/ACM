/*
 *	题目：
 *		BZOJ 1860: [Zjoi2006]Mahjong麻将
 *		http://www.lydsy.com/JudgeOnline/problem.php?id=1860
 *
 *	分析：
 *		据说有DP解，暂时没想出来。。。直接暴力dfs+hash
 *		dfs(pos,two,state):pos表示当前的位置，two表示是否有对，state表示状态
 *		暴力枚举四种情况，然后每次进行搜索前进行hash判重。
 *		hash判重时使用像池子法一样的方式解决冲突问题。
 *
 * */
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int maxm = 2e5+10;
const int mod = 99997;
const int maxn = 105;
const int n = 100;
const int seed = 103;

typedef unsigned long long ll;

ll p[maxn];
int a[maxn];

int po[mod+3],tol;

struct Hash{
	ll val;
	int next;
}edge[maxm];

void ins(ll x){ //insert x
	int y = int(x%mod);
	edge[++tol].val = x;
	edge[tol].next = po[y];
	po[y] = tol;
}

bool has(ll x){ //has x ?
	int y = int(x%mod);
	for(int i=po[y];i;i=edge[i].next)
		if(edge[i].val==x)
			return true;
	return false;
}

bool dfs(int pos,bool two,ll state){
	if(has(state))
		return false;
	ins(state);
	
	while(pos<=n&&a[pos]==0)
		pos ++;
	if(pos>n)
		return two;
	
	if(pos+2<=n&&a[pos+1]&&a[pos+2]){ //three continous
		a[pos]   --;
		a[pos+1] --;
		a[pos+2] --;
		if(dfs(pos,two,state-p[pos]-p[pos+1]-p[pos+2]))
			return true;
		a[pos]	 ++;
		a[pos+1] ++;
		a[pos+2] ++;
	}

	if(a[pos]>=3){ //three
		a[pos] -= 3;
		if(dfs(pos,two,state-p[pos]*3))
			return true;
		a[pos] += 3;
	}
1
	if(a[pos]>=4){ // four
		a[pos] -= 4;
		if(dfs(pos,two,state-p[pos]*4))
			return true;
		a[pos] += 4;
	}

	if(a[pos]>=2 && !two){ // pair
		a[pos] -= 2;
		//对于一对的特殊判断，比如可能存在5 = 3 + 2 = 4 +1（连续型但之前搜过不行）
		if(dfs(pos,true,state-p[pos]*2-p[n+1]))
			return true;
		a[pos] += 2;
	}

	return false;
}

int main(){
	freopen("sum.in","r",stdin);
	int ncase,x;
	cin>>ncase;
	
	p[1] = 1;
	for(int i=2;i<=n+1;i++)
		p[i] = p[i-1]*seed;

	while(ncase--){
		ll state = 0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			state *= seed;
			state += a[i];
		}
		state *= seed; //对于一对的特殊判断
		state ++;
		memset(po,0,sizeof(po));
		tol = 0;
		dfs(1,false,state)?puts("Yes"):puts("No");
	}
	return 0;
}

