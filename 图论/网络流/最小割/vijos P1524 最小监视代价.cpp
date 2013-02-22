/*

��Ŀ��
    ����yxyС��������һЩ���������£�����jzp�ؽ���һ���Թ��
    ����jzp����Ƚ�æ�����������һЩ��yxy�������Թ��������߶���
    �����Թ����Ա�������һ������ͼ���Թ�����һЩ����д��͵㣬
    ����������������Թ���jzp������һ�ֻ����ˣ����Լ����Թ��е�
    ��·�������ӵĵ�·yxy����ͨ�������Ǽ򵥵���Ϊ����һ����·��
    ���ۼ�Ϊ������·�ĳ��ȡ�����jzp����æ�������һ���������ʹ
    yxy�޷������Թ�����С����ܴ��ۡ�(yxyһ��ʼ��1�Ž��)

������
    ����С��

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 1000;
const int maxm = 100000;
const int inf = 1e9;
#define debug puts("here");

struct node{
    int y,f,next;
}edge[maxm];

int po[maxn],tol;
int arc[maxn],pre[maxn],dis[maxn],gap[maxn],cf[maxn];
int n,m,e,s,t;

void add(int x,int y,int f){
    edge[++tol].f = f;
    edge[tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].f = 0;
    edge[tol].y = x;
    edge[tol].next = po[y];
    po[y] = tol;
}

void sap(){
    n = t;
    memset(gap,false,sizeof(gap));
    memset(dis,0,sizeof(dis));
    gap[0] = n;
    for(int i=1;i<=n;i++)
        arc[i] = po[i];
    int i = s;
    int MIN;
    int aug = inf;
    int ans = 0;
    bool ok;

    while(dis[s]<n){
        ok = false;
        cf[i] = aug;
        for(int j=arc[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]+1==dis[i]){
                ok = true;
                aug = min(aug,edge[j].f);
                arc[i] = j;
                i = edge[j].y;
                pre[i] = j;
                if(i==t){
                    ans += aug;
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
        MIN = n-1;
        for(int j=po[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]<MIN){
                MIN = dis[edge[j].y];
                arc[i] = j;
            }
        if(--gap[dis[i]]==0)
            break;
        dis[i] = MIN+1;
        gap[dis[i]]++;
        if(i!=s){
            i = edge[pre[i]^1].y;
            aug = cf[i];
        }
    }
    cout<<ans<<endl;
}

void init(){
    memset(po,0,sizeof(po));
    tol = 1;
    s = 1;
    t = n+1;
    int x,y,f;
    while(e--){
        scanf("%d%d%d",&x,&y,&f);
        add(x,y,f);
        add(y,x,f);
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d",&x);
        add(x,t,inf);
    }
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>e){
        init();
        sap();
    }
    return 0;
}
