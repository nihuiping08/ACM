/*

��Ŀ��
	���� Description
    �羰���˵�С��Y �У�ӵ��n �������ľ��㡣����Ľ���������ο�Խ��Խ�࣬Y �����ⰲ����һ���۹⹫������
	Ϊ�ο��ṩ����ݵĽ�ͨ���񡣹۹⹫�����ڵ� 0 ���ӳ����� 1�ž��㣬�������ǰ�� 2��3 ��4 ����n �ž��㡣
	�ӵ� i �ž��㿪���� i+1 �ž�����Ҫ Di ���ӡ�
	����ʱ�̣�������ֻ����ǰ�������ھ��㴦�ȴ��� 
    �蹲��m ���οͣ�ÿλ�ο���Ҫ�˳�1 �δ�һ�����㵽����һ�����㣬��i λ�ο���Ti ������������ Ai ��ϣ����
	��ǰ������Bi ��Ai<Bi ����Ϊ��ʹ���г˿Ͷ���˳������Ŀ�ĵأ���������ÿվ������ȴ���Ҫ�Ӹþ��������
	���г˿Ͷ��ϳ�����ܳ���������һ���㡣����˿����³�����Ҫʱ�䡣  
    һ���˿͵�����ʱ�䣬����������Ŀ�ĵص�ʱ�̼�ȥ�����������ص�ʱ�̡���Ϊֻ��һ���۹⳵����ʱ��Ҫͣ����
	�������˿ͣ��˿��Ƿ׷ױ�Թ����ʱ��̫���ˡ����Ǵ�����˾��ZZ����������װ�� k ��������������ÿʹ��һ����
	����������ʹ����һ�� Di ��1 ������ͬһ��Di �����ظ�ʹ�ü����������Ǳ��뱣֤ʹ�ú�Di ���ڵ���0 �� 
    ��ôZZ����ΰ���ʹ�ü�����������ʹ���г˿͵�����ʱ���ܺ���С�� 
	
�����ʽ Input Format
    ��1 ����3 ������n, m, k ��ÿ��������֮����һ���ո�������ֱ��ʾ���������˿����͵��������������� 
    ��2 ����n-1 ��������ÿ��������֮����һ���ո��������i ������ʾ�ӵ�i �����㿪����i+1 ����������Ҫ��ʱ
	�䣬�� Di �� 
    ��3 ����m+2 ��ÿ��3 ������ Ti , Ai, Bi��ÿ��������֮����һ���ո�������� i+2 �б�ʾ��i λ�˿�������
	�������ʱ�̣������ľ����ź͵���ľ����š� 
	
������
	��С�������Ľ�ģ���⡣

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define debug puts("here");

const int maxn = 2005;
const int maxm = 20005;
const int inf = ~0u>>1;

struct node{
    int y,next;
    int f;
    int c;
}edge[maxm];

int pre[maxn],po[maxn],tol;
int dis[maxn];
int q[maxm];
bool use[maxn];
int la[maxn],num[maxn],d[maxn];
int n,m,k,s,t;
int ans;

void add(int x,int y,int f,int c){
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
    int head = 0,tail = 0;
    for(int i=0;i<=n;i++)
        dis[i] = inf;
    dis[s] = 0;
    q[tail++] = s;
    pre[s] = 0;
    int x,y;
    while(head<tail){
        x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            y = edge[i].y;
            if(edge[i].f>0&&edge[i].c+dis[x]<dis[y]){
                dis[y] = edge[i].c + dis[x];
                pre[y] = i;
                if(!use[y]){
                    use[y] = true;
                    q[tail++] = y;
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

int build(){
    memset(la,0,sizeof(la));
    memset(po,0,sizeof(po));
    memset(num,0,sizeof(num));
    tol = 1;

    int ti,ai,bi;
    int sum = 0;

    for(int i=2;i<=n;i++)
        scanf("%d",&d[i]);

    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&ti,&ai,&bi);
        la[ai] = max(la[ai],ti);
        num[bi]++;
        sum += ti;
    }

    s = 2*n+3;
    int tt = n<<1|1;
    t = tt+1;

    for(int i=1;i<=n;i++){
        if(i!=1){
            add(s,i,la[i-1]+d[i],0);
            add(i+n,t,la[i],0);
            add(i,tt,d[i],0);
        }
        if(i!=n)
            add(i+n,i+1,inf,0);
        add(i,i+n,inf,num[i]);
    }
    add(n<<1,t,inf,0);
    add(tt,t,k,0);
    n = t+1;
    return sum;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m>>k){
        ans = -build();
        while(spfa());
        cout<<ans<<endl;
    }
    return 0;
}
