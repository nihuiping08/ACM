/*

��Ŀ��
    �ָ�����λѡ�ֵ������Ƚϲ������Լ������ѵĲ������룬�����֯����ʹ���Լ��������ܹ���ʤ

������
    ��ѡ�������ȽϿ��Թ���һ������ͼ������Ҫʹ���Լ�������ҪӮ�ñ����������������ڵ���ͨ��
    �ض������Ϊ0�ģ����轨ͼʱ���������������Ϊ�ߵ���㣩��������Ŀ����ת��Ϊ�Ƚ�ͼ��Ȼ��
    ������ͨ�������㣬Ȼ���жϸ������Ƿ����Ϊ0�����������ڸ���ͨ���У������жϿ�����֯����
    ��һ�����������ж������ڲ��ڸ���ͨ���У������������е����Ϊ0����ͨ����������Ϊtrue��
    Ȼ��ֱ�Ӱ��������ѵ����ڵ���ͨ����Ϊfalse,�����е���ͨ����ֻҪ����true����ͨ�飬�Ϳ��ж�
    ������֯������һ������

*/
#include <cstdio>
#include <cstring>

const int X = 100005;

int dfn[X],low[X],stack[X],deg[X],father[X],depth,top,bcnt;
int f[X],fri,n,m;
bool use[X],instack[X];

struct node
{
    int v;
    node *next;
    void fun()
    {
        v = 0;
        next = NULL;
    }
}edge[X],*head[X],*tmp;

void tarjan(int u)
{
    int v;
    dfn[u] = low[u] = ++depth;
    stack[++top] = u;
    instack[u] = true;

    for(node *p=head[u];p;p=p->next)
    {
        v = p->v;
        if(!low[v])
        {
            tarjan(v);
            if(low[v]<low[u])
                low[u] = low[v];
        }
        else if(instack[v]&&low[u]>dfn[v])
            low[u] = dfn[v];
    }
    if(low[u]==dfn[u])
    {
        bcnt++;
        do
        {
            v = stack[top--];
            instack[v] = false;
            father[v] = bcnt;
        }while(u!=v);
    }
}

void solve()
{
    memset(instack,false,sizeof(instack));
    memset(low,0,sizeof(low));
    memset(deg,0,sizeof(deg));
    depth = bcnt = top = 0;

    for(int i=1;i<=n;i++)
        if(!low[i])
            tarjan(i);

    for(int i=1;i<=n;i++)
        for(node *p=head[i];p;p=p->next)
            if(father[i]!=father[p->v])
                deg[father[p->v]]++;

    memset(use,false,sizeof(use));
    for(int i=1;i<=bcnt;i++)
        if(!deg[i])
            use[i] = true;

    for(int i=0;i<fri;i++)
        use[father[f[i]]] = false;

    bool flag = true;
    for(int i=1;i<=bcnt;i++)
        if(use[i])
        {
            flag = false;
            break;
        }
    flag?printf("yes\n"):printf("no\n");
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(scanf("%d%d%d",&n,&fri,&m),n||m||fri)
    {
        for(int i=0;i<fri;i++)
            scanf("%d",&f[i]);
        memset(head,NULL,sizeof(head));

        for(int i=0;i<m;i++)
            edge[i].fun();
        tmp = edge;
        int u,v;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&u,&v);
            tmp->next = head[u];
            tmp->v = v;
            head[u] = tmp++;
        }
        solve();
    }

    return 0;
}
