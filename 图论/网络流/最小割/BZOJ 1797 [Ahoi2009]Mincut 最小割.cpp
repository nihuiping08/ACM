/*

��Ŀ��
    A,B�����������ڽ�ս������A������������������N����תվ��
    M�������·�������е�i (1��i��M)����·������vi,ui������תվ��
    ��ô��תվvi����ͨ���õ�·����ui��תվ������ж�������·��
    ��Ҫ����ci������B�����ҳ�һ��·���жϷ�����ʹ��תվs���ܵ�
    ����תվt�������ж�·���Ĵ���֮����С�� С�ɿ�һ�۾Ϳ�����
    ����һ������С������⡣����˼����С�ɿɲ��������ڴˡ�����
    ����ÿ�������·����������⣺ ����һ���Ƿ����һ����С��
    ��·���жϷ��������иõ�·���жϣ� ��������Ƿ���κ�һ��
    ��С����·���жϷ��������иõ�·���жϣ� ��������ش�����
    �����⡣

������
    �������������������磬Ȼ������tarjan������������ǿ��ͨ
    ���������ߵ��������㲻��ͬһ��ǿ��ͨ����������������������
    ��Ϊ0����������һΪ1�����ڴ˻�����һ��������Դ����ͬһ��ǿ
    ��ͨ�����ϣ�����һ������������ͬһ��ǿ��ͨ�����ϣ�������
    ��Ϊ1

    �жϱ��Ƿ���ĳ����С��� �Լ� �жϱ��Ƿ�Ϊ��С��ı���ߡ�
    �ڲ������������ǿ��ͨ���������ڲ���ͬһǿ��ͨ������������
    �ߣ���Ȼ��ĳһ��С���С�

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 4005;
const int maxm = 120005;
const int inf = 1e9;

int po[maxn],tol;
int dis[maxn],pre[maxn],cf[maxn],arc[maxn],gap[maxn];
int n,m,s,t;
int stack[maxn],father[maxn],low[maxn],dfn[maxn];
int bcnt,top,depth;
bool instack[maxn];

struct node{
    int y,f,next;
}edge[maxm];

void dfs(int x){
    dfn[x] = low[x] = ++depth;
    stack[++top] = x;
    instack[x] = true;
    int y;
    for(int i=po[x];i;i=edge[i].next){
        if(edge[i].f<=0)
            continue;
        y = edge[i].y;
        if(!low[y]){
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
    memset(instack,false,sizeof(instack));
    top = depth = bcnt = 0;
    for(int i=1;i<=n;i++)
        if(!low[i])
            dfs(i);
}

void sap(){
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    gap[0] = n;
    for(int i=0;i<=n;i++)
        arc[i] = po[i];
    int i = s;
    int aug = inf;
    bool ok = false;

    while(dis[s]<n){
        cf[i] = aug;
        ok = false;
        for(int j=arc[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]+1==dis[i]){
                ok = true;
                aug = min(aug,edge[j].f);
                i = edge[j].y;
                pre[i] = j;
                if(i==t){
                    while(i!=s){
                        edge[pre[i]].f -= aug;
                        edge[pre[i]^1].f += aug;
                        i = edge[pre[i]^1].y;
                    }
                    aug = inf;
                }
                break;
            }
        if(ok)
            continue;
        int MIN = inf;
        for(int j=po[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]<MIN){
                MIN = dis[edge[j].y];
                arc[i] = j;
            }
        if(--gap[dis[i]]==0)
            break;
        dis[i] = MIN+1;
        ++gap[dis[i]];
        if(i!=s){
            i = edge[pre[i]^1].y;
            aug = cf[i];
        }
    }
}

void add(int x,int y,int f){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;
}

void solve(){
    for(int i=1;i<=m;i++){
        int y = edge[i<<1].y;
        int x = edge[i<<1|1].y;
        int a = 0;
        int b = 0;
        if(father[x]!=father[y]&&!edge[i<<1].f){
            a = 1;
            if(father[x]==father[s]&&father[y]==father[t])
                b = 1;
        }
        printf("%d %d\n",a,b);
    }
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m>>s>>t){
        memset(po,0,sizeof(po));
        tol = 1;
        int x,y,z;
        for(int i=0;i<m;i++){
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
            add(y,x,0);
        }
        sap();
        tarjan();
        solve();
    }
    return 0;
}
