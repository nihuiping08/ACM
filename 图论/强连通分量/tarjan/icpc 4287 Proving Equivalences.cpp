/*

������ ��Ŀ��icpc 4287 Proving Equivalences
    a�ܹ��Ƴ�b��b�ܹ��Ƴ�c�����������Ӷ��ٸ���ϵ��ʹ�����еĹ�ϵ�໥�ȼ�

�����������뵽���������ͼ��Ȼ�����ͼ�е�ǿ��ͨ����������֮����max(id,od)��
id��ʾ�������Ϊ0�Ķ��������od��ʾ����Ϊ0�ĸ��������ǵ�Ҫע����ǵ���ͨ��
ֻ��һ����ʱ�򣬴�Ӧ����0�������������Ԫ���໥�ȼۣ�

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn =  50005;
const int maxm =  100005;

int po[maxn],tol;
int stack[maxn],dfn[maxn],low[maxn],father[maxn],bcnt,depth,top;
bool instack[maxn];
int id[maxn],od[maxn];
int n,m;

struct node{
    int y,next;
}edge[maxm];

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
    memset(instack,false,sizeof(instack));
    memset(dfn,0,sizeof(dfn));
    top = bcnt = depth = 0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i);
    if(bcnt==1){
        puts("0");
        return;
    }

    memset(id,0,sizeof(id));
    memset(od,0,sizeof(od));
    for(int x=1;x<=n;x++)
        for(int j=po[x];j;j=edge[j].next){
            int y = edge[j].y;
            if(father[x]!=father[y]){
                od[father[x]] ++;
                id[father[y]] ++;
            }
        }
    int id_cnt = 0,od_cnt = 0;
    for(int i=1;i<=bcnt;i++){
        if(!id[i])
            id_cnt ++;
        if(!od[i])
            od_cnt ++;
    }
    cout<<max(id_cnt,od_cnt)<<endl;
}

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--){
        memset(po,0,sizeof(po));
        tol = 0;
        int x,y;
        cin>>n>>m;
        while(m--){
            scanf("%d%d",&x,&y);
            add(x,y);
        }
        tarjan();
    }
    return 0;
}
