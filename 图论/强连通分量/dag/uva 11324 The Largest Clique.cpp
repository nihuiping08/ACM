/*

��Ŀ��
    ��ͼ��ĳ�����������Զ�ܹ�һ���߹����ٸ��ڵ�

������
    ǿ��ͨ������gcc��Ȼ�������ͼ����ͼ��һ��dag������dag����dp����·�����ɡ�
	dpת�Ʒ���Ϊ
		dp[x] = size[x] + max(dp[y]);  
	������б�x��y�ıߣ����仯���������ˣ����忴ʵ�ִ���

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const int maxn = 1005;
const int maxm = 50005;

#define debug puts("here");

int dfn[maxn],low[maxn],stack[maxn],father[maxn],bcnt,top,depth;
bool instack[maxn];
int po[maxn],tol,n,m;
int id[maxn];
int dp[maxn];
int sum[maxn];

vector<int> vec[maxn];

struct node{
    int y,next;
}edge[maxm];

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

void dfs(int x){	//�ݹ�ʵ��tarjan�㷨
    low[x] = dfn[x] = ++depth;
    instack[x] = true;
    stack[++top] = x;
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
        ++bcnt;
        do{
            y = stack[top--];
            instack[y] = false;
            father[y] = bcnt;
        }while(x!=y);
    }
}

void tarjan(){
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    top = bcnt = depth = 0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i);
}

int f(int x){	//���仯������dag�ϵ��·��
    if(dp[x])
        return dp[x];
    int ans = 0;
    for(int i=0;i<(int)vec[x].size();i++){	//��x�����б߳������������·��
        int y = vec[x][i];
        ans = max(ans,f(y));	//ת�Ʒ���
    }
    dp[x] = ans+sum[x];
    return dp[x];
}

void dag(){
    memset(id,0,sizeof(id));
    memset(sum,0,sizeof(sum));
    memset(dp,0,sizeof(dp));

    for(int i=1;i<=n;i++)
        vec[i].clear();

    for(int x=1;x<=n;x++){		//������ͼ
        for(int j=po[x];j;j=edge[j].next){
            int y = edge[j].y;
            if(father[x]!=father[y]){
                vec[father[x]].push_back(father[y]);
                id[father[y]] ++;
            }
        }
        sum[father[x]] ++;	//ͳ��ÿ�������ĸýڵ�������������ԭͼ�Ľڵ���Ŀ
    }

    int ans = 0;
    for(int i=1;i<=bcnt;i++)
        if(!id[i])
            ans = max(f(i),ans);
    cout<<ans<<endl;
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--){
        cin>>n>>m;
        int x,y;
        memset(po,0,sizeof(po));
        tol = 0;
        while(m--){
            scanf("%d%d",&x,&y);
            add(x,y);
        }
        tarjan();
        dag();
    }
    return 0;
}
