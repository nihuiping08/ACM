/*

模板题。
LCA(u)
{
     Make-Set(u)
     ancestor[Find-Set(u)]=u
     对于u的每一个孩子v
     {
         LCA(v)
         Union(u)
         ancestor[Find-Set(u)]=u
     }
     checked[u]=true
     对于每个(u,v)属于P
     {
         if checked[v]=true
        then {
             回答u和v的最近公共祖先为 ancestor[Find-Set(v)]
         }
     }
}

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 10005;

int n,s,e,ans[X],p[X];
int po[X];
bool use[X];

struct node{
    int y,next;
}edge[X];

int find_set(int x){
    if(x!=p[x])
        p[x] = find_set(p[x]);
    return p[x];
}

void union_set(int x,int y){
    x = find_set(x);
    y = find_set(y);
    if(x!=y)
        p[y] = x;
}

void lca(int x){
    ans[x] = p[x] = x;
    for(int i=po[x];i;i=edge[i].next){
        lca(edge[i].y);
        union_set(x,edge[i].y);
        ans[find_set(x)] = x;
    }
    use[x] = true;
    if(x==s&&use[e])
        cout<<ans[find_set(e)]<<endl;
    if(x==e&&use[s])
        cout<<ans[find_set(s)]<<endl;
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase,x,y;
    cin>>ncase;
    while(ncase--){
        cin>>n;
        memset(po,0,sizeof(po));
        memset(use,false,sizeof(use));
        for(int i=1;i<n;i++){
            cin>>x>>y;
            use[y] = true;
            edge[i].y = y;
            edge[i].next = po[x];
            po[x] = i;
        }
        for(int i=1;i<=n;i++)
            if(!use[i]){
                x = i;
                break;
            }
        cin>>s>>e;
        memset(use,false,sizeof(use));
        lca(x);
    }
    return 0;
}
