#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 505;

int n,m;
int order[X],father[X],in[X],out[X],bcnt,scc;
bool use[X];

struct node
{
    int v;
    node *next;
    void fun()
    {
        v = 0;
        next = NULL;
    }
}edge[X*X],redge[X*X],*head[X*X],*rhead[X*X],*tmp,*rtmp;

void dfs(int u)
{
    int v;
    use[u] = true;
    for(node *p=head[u];p;p=p->next)
    {
        v = p->v;
        if(!use[v])
            dfs(v);
    }
    order[++bcnt] = u;
    //cout<<"order["<<bcnt<<"] = "<<u<<endl;
}

void rdfs(int u)
{
    int v;
    use[u] = true;
    father[u] = scc;
    //cout<<"father["<<u<<"] = "<<scc<<endl;
    for(node *p=rhead[u];p;p=p->next)
    {
        v = p->v;
        if(!use[v])
            rdfs(v);
    }
}

void kosaraju()
{
    //cout<<"first"<<endl<<endl;
    scc = bcnt = 0;
    memset(use,false,sizeof(use));
    for(int i=1;i<=n;i++)
        if(!use[i])
        {
            //cout<<"dfs "<<i<<endl;
            dfs(i);
        }
    //cout<<"second"<<endl<<endl;
    memset(use,false,sizeof(use));
    for(int i=n;i;i--)
        if(!use[order[i]])
        {
            //cout<<"dfs "<<i<<endl;
            scc++;
            rdfs(order[i]);
        }
}

void solve()
{
    if(scc==1)
    {
        printf("1\n0\n");
        return;
    }
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
    int v;
    for(int u=1;u<=n;u++)
    {
        for(node *p=head[u];p;p=p->next)
        {
            v = p->v;
            if(father[u]!=father[v])
            {
                in[father[v]]++;
                out[father[u]]++;
            }
        }
    }
    int id = 0;
    int od = 0;
    for(int i=1;i<=scc;i++)
    {
        if(!in[i])
            id++;
        if(!out[i])
            od++;
    }
    printf("%d\n%d\n",id,max(id,od));
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    scanf("%d",&n);

    memset(head,NULL,sizeof(head));
    memset(rhead,NULL,sizeof(rhead));
    for(int i=0;i<=n*n;i++)
    {
        edge[i].fun();
        redge[i].fun();
    }
    tmp = edge;
    rtmp = redge;

    for(int i=1;i<=n;i++)
    {
        while(scanf("%d",&m),m)
        {
            tmp->next = head[i];
            tmp->v = m;
            head[i] = tmp++;

            rtmp->next = rhead[m];
            rtmp->v = i;
            rhead[m] = rtmp++;
        }
    }

    kosaraju();
    solve();
    /*cout<<endl<<endl;
    for(int i=1;i<=n;i++){cout<<i<<"node  ";
        for(node *p=head[i];p;p=p->next)
            cout<<"   "<<p->v;
        cout<<endl;
    }*/
    return 0;
}
