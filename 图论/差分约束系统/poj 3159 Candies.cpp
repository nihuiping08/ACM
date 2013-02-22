/*
#include <iostream>
#include <cstdio>
using namespace std;
#define X 150005
#define INF 0xfffffff
int dis[30005],n,m;
struct node
{
    int x,y,w;
}p[X];
void ballman_ford()
{
    for(int i=1;i<=n;i++)
        dis[i] = INF;
    dis[1] = 0;
    int x,y;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            x = p[j].x;
			y = p[j].y;
            dis[y] = min(dis[y],dis[x]+p[j].w);
			//��x,y�����ɳڲ�����������㾭��x�ٵ�y�벻����x����y
		}
    }
    cout<<dis[n]<<endl;
}
void add(int i,int x,int y,int w)
{
    p[i].x = x;
    p[i].y = y;
    p[i].w = w;
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int x,y,w;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&x,&y,&w);
            add(i,x,y,w);
        }
        ballman_ford();
    }
    return 0;
}
*/
/*
 *
 * ��Դ���·�㷨SPFA,ʱ�临�Ӷ�O(kE),k��һ������²�����2,����ÿ������ʹ�ÿ�����O(VE)��ʱ�������ÿ�Խڵ�֮������·
 * ʹ���˶���,���������ڶ����еĵ����ŵĵ�����ɳ�,ͬʱ�����ڶ����е����ŵĵ����,ֱ���ӿ����㷨����,���·���
 * SPFA��Bellman-Ford���Ż���,���Դ����и�Ȩ�ߵ����
 * ���ڸ���,���ǿ���֤��ÿ������Ӵ������ᳬ��V,�������ǿ��Լ�¼ÿ�������Ӵ���,�������V���ʾ����ָ���,�㷨����
 * ����Ҫ�Ե��ÿһ���߽���ö��,�ʲ����ڽӱ�ʱʱ�临�Ӷ�ΪO(kE),���þ���ʱʱ�临�Ӷ�ΪO(kV^2)
 
#include<cstdio>
#include<vector>
#include<queue>
#define MAXV 10000
#define INF 1000000000 //�˴����鲻Ҫ������С,�����׵�������ʱ���,��С���ܻᱻ�ж�Ϊ�����ľ���
 
using std::vector;
using std::queue;
 
struct Edge{
	int v; //��Ȩ
	int to; //���ӵĵ�
};
 
vector<Edge> e[MAXV]; //����һ�������E<<V*V,���ڴ�ѡ����vector��̬����洢,Ҳ����ʹ������洢
int dist[MAXV]; //�洢��ԭ��0�ľ���,���Կ���ά����洢ÿ�Խڵ�֮��ľ���
int cnt[MAXV]; //��¼��Ӵ���,����V���˳�
queue<int> buff; //����,���ڴ洢��SPFA�㷨�е���Ҫ�ɳڵĽڵ�
bool done[MAXV]; //�����жϸýڵ��Ƿ��Ѿ��ڶ�����
int V; //�ڵ���
int E; //����
 
bool spfa(const int st){ //����ֵ:TRUEΪ�ҵ����·����,FALSE��ʾ���ָ����˳�
	for(int i=0;i<V;i++){ //��ʼ��:������ԭ��st�ľ���������е㵽st�ľ��������һ������ֵ
		if(i==st){
			dist[st]=0; //ԭ�����Ϊ0;
			continue;
		}
		dist[i]=INF; //��ԭ����������
	}
	buff.push(st); //ԭ�����
	done[st]=1; //���ԭ���Ѿ����
	cnt[st]=1; //�޸���Ӵ���Ϊ1
	while(!buff.empty()){ //���зǿ�,��Ҫ�����ɳ�
		int tmp=buff.front(); //ȡ������Ԫ��
		for(int i=0;i<(int)e[tmp].size();i++){ //ö�ٸñ����ӵ�ÿһ����
			Edge *t=&e[tmp][i]; //����vector��Ѱַ�ٶȽ���,���ڴ˽���һ���Ż�
			if(dist[tmp]+(*t).v<dist[(*t).to]){ //���ĺ�������,�����ɳڲ���
				dist[(*t).to]=dist[tmp]+(*t).v; //���ı�Ȩֵ
				if(!done[(*t).to]){ //û�����,�������
					buff.push((*t).to); //���ڵ�ѹ�����
					done[(*t).to]=1; //��ǽڵ��Ѿ����
					cnt[(*t).to]=1; //�ڵ���Ӵ�������
					if(cnt[(*t).to]>V){ //�Ѿ�����V��,���ָ���
						while(!buff.empty())buff.pop(); //��ն���,�ͷ��ڴ�
						return false; //����FALSE
					}
				}
			}
		}
		buff.pop();//�������׽ڵ�
		done[tmp]=0;//�����׽ڵ���Ϊδ���
	}
	return true; //����TRUE
} //�㷨����
 
int main(){ //������
	scanf("%d%d",&V,&E); //��������ͱ���
	for(int i=0,x,y,l;i<E;i++){
		scanf("%d%d%d",&x,&y,&l); //����x,y,l��ʾ��x->y��һ������߳���Ϊl
		Edge tmp; //����һ����ʱ����,�Ա����vector
		tmp.v=l; //���ñ�Ȩ
		tmp.to=y; //�������ӽڵ�
		e[x].push_back(tmp); //��������ѹ��x�ı���
	}
	if(!spfa(0)){ //���ָ���
		printf("���ָ���,���·������\n");
	}else{ //�������·
		printf("�ڵ�0���ڵ�%d����̾���Ϊ%d",V-1,dist[V-1]);
	}
	return 0;
}
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;
#define X 30005
struct node
{
	int x,y,w,next;
}p[X*5];
int dis[X],link[X],n,m;
bool use[X];
void spfa()
{
	stack<int> s;
	memset(use,false,sizeof(use));
	memset(dis,0x7f,sizeof(dis));
	dis[1] = 0;
	s.push(1);
	int k,h;
	while(!s.empty())
	{
		h = s.top();
		s.pop();
		use[h] = false;
		k = link[h];
		while(k)
		{
			if(dis[p[k].y]>dis[h]+p[k].w)
			{
				dis[p[k].y] = dis[h]+p[k].w;
				if(!use[p[k].y])
				{
					use[p[k].y] = true;
					s.push(p[k].y);
				}
			}
			k = p[k].next;
		}
	}
	cout<<dis[n]<<endl;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>n>>m)
	{
		memset(link,0,sizeof(link));
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].w);
			p[i].next = link[p[i].x];
			link[p[i].x] = i;
		}
		spfa();
	}
	return 0;
}