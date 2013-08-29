/*

分析：构造一棵二叉树即可。每个节点只有左或者右节点，最后中序遍历即可输出答案~

*/
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

/******** program ********************/

const int MAXN = 1e6+5;

char s[MAXN];
int n;

struct node{
    node *l,*r;
    int id;
    node(){
        l = r = NULL;
        id = 0;
    }
};

void dfs(node *root , int dep){
    if(dep>n)return;
    root->id = dep;
    if(s[dep]=='l'){
        root->l = new node();
        dfs(root->l,dep+1);
    }else{
        root->r = new node();
        dfs(root->r,dep+1);
    }
}

void out(node *root){
    if(root==NULL)
        return;

    out(root->l);
    if(root->id)
        printf("%d\n",root->id);
    out(root->r);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    bool ok = false;
    while(gets(s+1)){
        ok?puts("----------------------"):ok = true;

        node *root = new node();
        n = strlen(s+1);
        dfs(root,1);
        out(root);
    }

	return 0;
}
