/*

��Ŀ��
	ǽ�ڵĵ�֮����е����ţ�������������һ�����أ�����δ�Խ���ٵ��ŵ���ô�

������
	�����γɵ���һ��͹�������Ա��غ��߶ε�����������ֱ���ཻ�ĵ�������Ϊ��Ҫ��Խ�Ĵ�����
	���ж��߶��ཻ�ÿ���ʵ��Ϳ����ų�ʵ�鼴�ɡ�ö�����е��е��뱦�ص�������ɵ��߶�������
	��ֱ���Ƿ��ཻ���ɡ�
	����֪���ǲ�����Ū�������⣬�о�ö���е�ʱ�������Ǵ�ġ���������ǰ�ҵ�����Ӧ���ǶԵģ�
	���ǿ�WA���������ں��Ե�1ʱͬ��Ҫ���Number of doors = ���㵽�ҿ�WA����������

*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
#define esp 1e-8
bool use[35];

struct point{	//�������
	double x,y;
}s[110];

struct line{	//ֱ�ߵ�����
	point a,b;
}p[35];

int dcmp(double x){	//�ж��Ƿ�Ϊ0
	if(abs(x)<esp)
		return 0;
	return x>0?1:-1;
}

double det(point a,point b,point o){	//������Ĳ��
	return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}

bool dot(point a,point b,point o){		//�жϵ��Ƿ����߶���
	if(dcmp(min(a.x,b.x)-o.x)<=0&&dcmp(max(a.x,b.x)-o.x)>=0)
		return true;
	return false;
}

bool intersect(point a,point b,point c,point d){
	int d1 = dcmp(det(a,b,c));
	int d2 = dcmp(det(a,b,d));
	int d3 = dcmp(det(c,d,a));
	int d4 = dcmp(det(c,d,b));
	if((d1^d2)==-2&&(d3^d4)==-2)//����ʵ��
		return true;
	else if(d1==0&&dot(a,b,c))	//�����ų�����
		return true;
	else if(d2==0&&dot(a,b,d))
		return true;
	else if(d3==0&&dot(c,d,a))
		return true;
	else if(d4==0&&dot(c,d,b))
		return true;
	else
		return false;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,ret;
	cin>>n;
	ret = 0;
	for(int i=1;i<=n;i++){
		cin>>p[i].a.x>>p[i].a.y>>p[i].b.x>>p[i].b.y;
		s[++ret] = p[i].a;
		s[++ret] = p[i].b;
	}

	int ans = 10000000,cnt = 0;
	point q;

	cin>>q.x>>q.y;
	if(n==0){
		printf("Number of doors = %d\n",1);
		return 0;
	}
	
	for(int i=1;i<=ret;i++){	//ö�����е��е�
		cnt = 1;
		for(int j=1;j<=n;j++){
			if((s[i].x==p[j].a.x&&s[i].y==p[j].a.y)||(s[i].x==p[j].b.x&&s[i].y==p[j].b.y))
				continue;
			if(intersect(q,s[i],p[j].a,p[j].b))
				cnt++;
		}
		ans = min(cnt,ans);	//����
	}
	printf("Number of doors = %d\n",ans);
	return 0;
}