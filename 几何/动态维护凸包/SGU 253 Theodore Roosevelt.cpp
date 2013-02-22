/*
 * 253. Theodore Roosevelt
 * ��Ŀ������һ����ʱ���͹����Ȼ���ٸ���m���㣬����m�����Ƿ�������k������͹������
 *     �������ڱ߽��ϣ�
 * ������O(n)��ѯ�ʷ�ʽ�϶�TLE���������ǿ���������̬͹�����ַ�ʽ��set����splay��ά
 *      ��һ�������򣬶���ѯ�ʵ��Ǹ���ļ��ǣ�Ȼ�����ò���жϼ��ɡ�
 *
 * */
#include <cstdio>
#include <cstring>
#include <set>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const double eps = 1e-8;
const int X = 100005;

int dcmp(double x){
	if(fabs(x)<eps)
		return 0;
	return x>0?1:-1;
}

struct Point{
	ll x,y;
	double angle;
	Point(){}
	Point(ll _x,ll _y):x(_x),y(_y){}
	friend bool operator < (Point a,Point b){
		return dcmp(a.angle-b.angle)<0;
	}
	friend Point operator - (Point a,Point b){
		return Point(a.x-b.x,a.y-b.y);
	}
	void input(){
		scanf("%lld%lld",&x,&y);
		angle = atan2(y,x);
	}
};

set<Point> Convex;
int n,m,k;

ll det(Point a,Point b){
	return a.x*b.y-a.y*b.x;
}

ll det(Point a,Point b,Point o){
	return det(a-o , b-o);
}

Point Pre(Point pos){
	set<Point>::iterator it = Convex.lower_bound(pos);
	if(it==Convex.begin())
		return *(--Convex.end());
	return *(--it);
}

Point Next(Point pos){
	set<Point>::iterator it = Convex.upper_bound(pos);
	if(it==Convex.end())
		return *Convex.begin();
	return *it;
}

int cal(Point pos){
	Point pre = Pre(pos);
	Point next = Next(pre);
	return det(pre,next,pos)>=0;
}

int main(){
	freopen("sumd.txt","r",stdin);
	cin>>n>>m>>k;
	Convex.clear();
	Point pos;
	for(int i=0;i<n;i++){
		pos.input();
		Convex.insert(pos);
	}
	int ans = 0;
	while(m--){
		pos.input();
		ans += cal(pos);
		if(ans>=k)
			break;
	}
	ans>=k?puts("YES"):puts("NO");

	return 0;
}
