/*

��Ŀ��
    ÿ̨�绰����һ����һ�޶��ĺ��룬��һ��ʮλ��ʮ��������
    ����ʾ���绰a��b֮����ֱ��ͨ�ţ����ҽ�����a��b֮�����
    һ�����ֲ�ͬ�������ߡ�����a��ĳ��λ�ϵ����ֺ�a��b��ͬ����
    ��a��b֮�佨��ͨ����ϵ����Ҫ��ʱ��Ϊcost[ lcp(a,b) ]��
    ����cost[]��һ���������飬lcp(a,b)��ʾa��b�������ǰ
    ׺�ĳ��ȣ�lcp(a,b)Խ��ͨ��ʱ��Խ�졣
    ���⣬���a��b��ͨ�ţ�b��c��ͨ�ţ���ôa��cҲ�ܽ���b��ͨ
    �š�a��c����b����ͨ����ϵ����ʱ����cost[ lcp(a,b) ]+
    cost[ lcp(b,c) ]��
    ����Freda���Rainbow��绰���������Freda���������Ҫ
    ����ʱ���������Rainbow����ͨ����ϵ��

������
    ���죺ö�ٽ�ͼ��Hash�����·
    ö��ÿ���绰���룬O(10*10)ö��ÿһλ���ʲô������λ��
    ���õ��ĺ��룬Hash�ж��Ƿ���ڸú��룬���ڵĻ������ߣ�
    ��Ȩֱ�Ӽ���LCP��
    Ȼ�󽨺�ͼ֮���ܸ�spfa����heap-dijkstra���ɡ�
    У�ڲ�������������㿪O2����1s����������map��Hash��Ϊ��
    ��֤Ч�ʽ�����дHash����ʹ��slf����heap�Ż���spfa������
    ���Ż���dijkstra��

�ҵ��ĵ�:
    ����⿼����hash��ǰ���ǡ�spfa����ͼ��������
    ��hash�����Ľ����У����õĸ�ǰ���ǵ�˼·���ﵽhash������
    һ��һ�Ĳ����������ڹ���ģ�͵�ʱ������ö�ٵķ�ʽʵ����
    �����ֲ���

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 1e6+5;
const int maxm = 2e6+5;
const int mod = 99991;
const int X = 12;

typedef long long ll;
#define debug puts("here");

int c[X],n;
int dig[maxn][X];
ll a[maxn];
int po[maxn],tol;
int dis[maxn];
bool use[maxn];

struct node{
    ll num;
    int next;
    int id;
}p[maxn];

void insert(ll x,int id){
    int z = x%mod;
    p[++tol].num = x;
    p[tol].id = id;
    p[tol].next = po[z];
    po[z] = tol;
}

int ask(ll x){
    int z = x%mod;
    for(int i=po[z];i;i=p[i].next)
        if(p[i].num==x)
            return p[i].id;
    return 0;
}

struct qq{
    int y,next;
    int w;
}edge[maxm];
int head[maxn];

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = head[x];
    head[x] = tol;
    for(int i=0;i<10;i++){
        if(dig[x][i]!=dig[y][i]){
            edge[tol].w = c[i];
            return;
        }
    }
    debug;
}
void spfa(){
    memset(dis,0x3f,sizeof(dis));
    memset(use,false,sizeof(use));
    queue<int> q;
    q.push(1);
    dis[1] = 0;

    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        for(int i=head[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(dis[x]+edge[i].w<dis[y]){
                dis[y] = dis[x]+edge[i].w;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    if(dis[n]==1061109567)
        puts("-1");
    else
        printf("%d\n",dis[n]);
}

void build(){
    int tmp[X];

    ll q[X] = {0};
    q[0] = 1000000000;
    for(int i=1;i<10;i++)
        q[i] = q[i-1]/10;

    tol = 0;
    memset(head,0,sizeof(head));

    for(int k=1;k<=n;k++){
        for(int i=0;i<10;i++)
            tmp[i] = dig[k][i];
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++){
                if(tmp[i]!=tmp[j]){
                    ll w = p[k].num+(tmp[i]-tmp[j])*q[j]-(tmp[i]-tmp[j])*q[i];
                    int id = ask(w);
                    if(id)
                        add(k,id);
                }
                if(tmp[i]!=j){
                    ll w = p[k].num-(tmp[i]-j)*q[i];
                    int id = ask(w);
                    if(id)
                        add(k,id);
                }
            }
    }
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n){
        for(int i=0;i<10;i++)
            scanf("%d",&c[i]);
        int tmp[X];

        ll x;
        tol = 0;
        memset(po,0,sizeof(po));
        for(int i=1;i<=n;i++){
            scanf("%I64d",&x);
            insert(x,i);
            a[i] = x;
            for(int j=0;j<10;j++){
                tmp[j] = x%10;
                x /= 10;
            }
            for(int j=0;j<10;j++)
                dig[i][j] = tmp[10-j-1];
        }

        build();

        spfa();
    }
    return 0;
}
