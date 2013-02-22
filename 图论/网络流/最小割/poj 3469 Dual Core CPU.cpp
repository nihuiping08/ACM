/*

��Ŀ��
    ���˫��ϵͳ�У�ÿ������n��ģ�飬����ÿ��ģ�����𲽼ۣ�����
    ����������a������b����Ĵ���Ϊc����������ΰ��Ÿ�ģ�������
    �Ӷ�ʹ�ü۸���С

������
    ����ÿ��ģ����˵��ai����Դ�㣬bi���ϻ�㣬Ȼ�����m����ϵ��
    ����һ������ߣ�Ȼ����һ����С��

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 100000;
const int maxm = 2000005;
const int inf = 1e9;
#define debug puts("here");

int n,m,s,t;
int po[maxn],tol;
int arc[maxn],pre[maxn],cf[maxn],dis[maxn],gap[maxn];

struct node{
    int y,f,next;
}edge[maxm];

void add(int x,int y,int f){
    edge[++tol].f = f;
    edge[tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

int sap(){
    memset(gap,false,sizeof(gap));
    memset(dis,0,sizeof(dis));
    gap[0] = t;
    for(int i=1;i<=t;i++)
        arc[i] = po[i];
    int i = s;
    int MIN;
    int aug = inf;
    int ans = 0;
    bool ok;

    while(dis[s]<t){
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
        MIN = t-1;
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
    return ans;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        memset(po,0,sizeof(po));
        tol = 1;
        s = n<<1|1;
        t = s+1;
        int x,y,z;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&x,&y);
            add(s,i,x);
            add(i,s,0);
            add(i,t,y);
            add(t,i,0);
        }
        while(m--){
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
            add(y,x,z);
        }
        cout<<sap()<<endl;
    }
    return 0;
}
