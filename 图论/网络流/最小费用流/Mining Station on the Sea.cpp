/*

��Ŀ��
    ��n�����İڷŵص㡢m���ۿڣ�����n�Ҵ���ʼʱͣ�ŵĸۿ�λ�ã�Ȼ
    �����k��ۿ���ۿ�֮���·����ϵ���ٸ���p�鴬��ۿڵĹ�ϵ����
    ������ΰ��Ŵ���ʹ�ô��Ӹۿڻص����İڷŵص�

������
    ֱ�Ӷ�ԭͼ���н�ͼ����һ����С����������
    �����ȶԴ��Լ��ۿ���һ��floyd��ע���ɳڵ�ʱ��ֻ�ܹ��Ըۿ���Ϊ
    �м�ڵ㣨���������ѭ�����ɣ���Ȼ����һ��km(���Ƿ������Ļ���
    ��RE...��

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int X = 1005;
const int maxn = 100005;
const int maxm = 3000005;
const int inf = 1e9;
#define debug puts("here");

int dis[maxn],pre[maxn],arc[maxn];
int po[maxn],tol;
bool use[maxn];
int map[X][X];
int n,m,s,t,k,p,ans;
int d[maxn];

struct node{
    int y,f,c,next;
}edge[maxm];

void add(int x,int y,int c,int f){
    edge[++tol].y = y;
    edge[tol].c = c;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].y = x;
    edge[tol].c = -c;
    edge[tol].f = 0;
    edge[tol].next = po[y];
    po[y] = tol;
}

bool spfa(){
    memset(use,false,sizeof(use));
    for(int i=1;i<=n;i++)
        dis[i] = inf;
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    pre[s] = 0;
    int x,y;
    while(q.size()){
        x = q.front();
        q.pop();
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            y = edge[i].y;
            if(edge[i].f>0&&edge[i].c+dis[x]<dis[y]){
                dis[y] = edge[i].c + dis[x];
                pre[y] = i;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    if(dis[t]==inf)
        return false;
    int aug = inf;
    for(int i=pre[t];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[t];i;i=pre[edge[i^1].y]){
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += dis[t]*aug;
    return true;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m>>k>>p){
        int x,y,z;
        s = n+m+1;
        t = s+1;
        tol = 1;
        memset(po,0,sizeof(po));
        for(int i=1;i<=n;i++){
            scanf("%d",&d[i]);
            add(s,d[i],0,1);
        }
        for(int i=1;i<=k;i++){
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z,inf);
            add(y,x,z,inf);
        }
        for(int i=1;i<=p;i++){
            scanf("%d%d%d",&x,&y,&z);
            add(y,x+m,z,inf);
        }
        for(int i=m+1;i<=n+m;i++)
            add(i,t,0,1);
        ans = 0;
        n = t;
        while(spfa())
            ;

        cout<<ans<<endl;
    }
    return 0;
}
