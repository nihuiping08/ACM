/*

��Ŀ��
    ����n*m�ĵ�ͼ��Ȼ���һ����ͼ�Ǻ������ֵģ�ÿ�����ֱ�ʾֻ
    �ܹ����ٸ�֩���ߣ��ڶ�����ͼ��˵���ڼ���������֩�루��L����
    ��ʾ��������һֻ֩�룬����֩��Ҫ�Ӹ��������������������
    �ܹ��ж���֩���ܹ�����

������
    ���ڵڶ�����ͼ��˵��ֱ�ӶԺ���L�ַ��ĸ�������Դ�㣬����Ϊ
    1�����ڵ�һ����ͼ��˵�����ں������ַ�0�ĸ��Ӳ�㣬Ȼ������
    Ϊ�����֣���ʾֻ�ܹ�����߹������ֵ�֩����Ŀ��Ȼ�����ÿ��
    ��Χ��d֮��ĸ�����������Ϊinf�ıߣ�������ڿ����ߵ������
    �������ϻ�㣬��ʾ�����ߵ�����

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 1000;
const int maxm = 200005;
const int inf = 1e9;
#define debug puts("here");

int n,m,s,t,d;
int po[maxn],tol;
int arc[maxn],pre[maxn],cf[maxn],dis[maxn],gap[maxn];
char a[maxn][maxn];
char b[maxn][maxn];
int ha[maxn][maxn];
int id;

int get(int x,int y){
    if(ha[x][y]==-1)
        ha[x][y] = ++id;
    return ha[x][y];
}

struct node{
    int y,f,next;
}edge[maxm];

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

int dir[40][2]={
               {1,0},{0,-1},{-1,0},{0,1},//4
               {2,0},{1,-1},{0,-2},{-1,-1},{-2,0},{-1,1},{0,2},{1,1},//8
               {3,0},{2,-1},{1,-2},{0,-3},{-1,-2},{-2,-1},{-3,0},{-2,1},{-1,2},{0,3},{1,2},{2,1},//12
               {4,0},{3,-1},{2,-2},{1,-3},{0,-4},{-1,-3},{-2,-2},{-3,-1},{-4,0},{-3,1},{-2,2},{-1,3},{0,4},{1,3},{2,2},{3,1},//16
};

int size[] = {0,4,12,24,40};

bool out(int x,int y){
    return x<0||y<0||x>=n||y>=m;
}

int build(){
    for(int i=0;i<n;i++)
        scanf("%s",a[i]);
    for(int i=0;i<n;i++)
        scanf("%s",b[i]);

    memset(po,0,sizeof(po));
    memset(ha,-1,sizeof(ha));
    tol = 1;
    id = 0;

    m = strlen(a[0]);
    int qq = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(b[i][j]=='L')
                qq++;

    int sum = n*m;
    s = sum<<1|1;
    t = s+1;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]>'0')
                add(get(i,j),get(i,j)+sum,a[i][j]-'0');
            if(b[i][j]=='L')
                add(s,get(i,j),1);
        }
    }

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            int temp = get(i,j)+sum;
            for(int k=0;k<size[d];k++){
                int x = i+dir[k][0];
                int y = j+dir[k][1];
                if(out(x,y))
                    add(temp,t,inf);
                else
                    add(temp,get(x,y),inf);
            }
        }
    return qq;
}


int main(){
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    for(int i=1;i<=ncase;i++){
        cin>>n>>d;
        int temp = build();
        temp -= sap();
        if(!temp)
            printf("Case #%d: no lizard was left behind.\n",i);
       else if(1!=temp)
            printf("Case #%d: %d lizards were left behind.\n",i,temp);
        else
            printf("Case #%d: 1 lizard was left behind.\n",i);

    }
    return 0;
}
