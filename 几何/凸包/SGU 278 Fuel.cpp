/*
 * ��Ŀ��
 *		n����Ʒ������������a,b,c��������n����Ʒ����Լ��
 *		��ai * xi <= A
 *		��bi * xi <= B
 *		��n����Ʒ���������ϡ�������Լ���µ�
 *		x * (��ci * xi) �����ֵ
 *
 *	������
 *		���ǲ�����
 *		di = ai / ci
 *		ei = bi / ci
 *		���е�ʽ
 *		��di * xi = A / x
 *		��ei * xi = B / x
 *		xΪ���н⡣
 *		��Ȼ����di < dj , ei < ej
 *		i�ض���j���š�
 *		
 *		���ǿ��Զ���(di,ei)����͹����Ȼ��������͹���ķ�Χ����n����Ʒ�����һ���di,ei
 *		�����п���ȡֵ��Ȼ����ͨ�����߶�[(0,0),(A,B)]�Ľ������x��
 *		Ȼ����ͨ��x��������
 *
 * */
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 150005;
const double eps = 1e-10;

double sx,sy;

struct Point{
	double x,y;
	Point(){}
	Point(double _x,double _y):x(_x),y(_y){}
	friend bool operator < (Point a,Point b){
		return a.y<b.y||(a.y==b.y&&a.x<b.x);
	}
	friend Point operator - (Point a,Point b){
		return Point(a.x-b.x,a.y-b.y);
	}
	friend Point operator + (Point a,Point b){
		return Point(a.x+b.x,a.y+b.y);
	}
	friend bool operator == (Point a,Point b){
		return fabs(a.x-b.x)<eps && fabs(a.y-b.y)<eps ;
	}
	void input(){
		double c;
		scanf("%lf%lf%lf",&x,&y,&c);
		x /= c;
		y /= c;
	}
}p[X],ret[X];

int top,n;

double det(Point a,Point b){
	return a.x*b.y-a.y*b.x;
}

double det(Point a,Point b,Point o){
	return det(a-o,b-o);
}

double det(Point a,Point b,Point c,Point d){
	return det(b-a,d-c);
}

bool del(int top,int i){
	return det(ret[top],p[i],ret[top-1])>=0;
}

void graham(){
	sort(p,p+n);
	top = 1;
	ret[0] = p[0];
	ret[1] = p[1];
	for(int i=2;i<n;i++){
		if(p[i]==p[i-1])
			continue;
		while(top&&del(top,i))
			top --;
		ret[++top] = p[i];
	}
	int mintop = top;
	for(int i=n-2;i>=0;i--){
		if(p[i]==p[i-1])
			continue;
		while(top>mintop&&del(top,i))
			top --;
		ret[++top] = p[i];
	}
}

double dis(Point a){
	return sqrt(a.x*a.x+a.y*a.y);
}

double dis(Point a,Point b){
	return dis(a-b);
}

Point intersect(Point a,Point b,Point c,Point d){
	double s,s1;
    s = det(c,d,a);
	s1 = det(c,b,a) + det(b,d,a);
    return Point(a.x+s/s1*(b.x-a.x) , a.y+s/s1*(b.y-a.y));
}

bool check(Point a,Point b,Point c,Point d){
    return det(c,b,a) * det(b,d,a)>0;
}

int cross(Point a,Point b,Point c,Point d){
    return det(c,b,a)*det(b,d,a)<0;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("sumd.txt","r",stdin);
#endif
	
	while(cin>>n>>sx>>sy){
		Point pos = Point(sx,sy);
		Point origin = Point(0,0);

		double ans = 0;
		for(int i=0;i<n;i++){
			p[i].input();
			ans = max(ans , min(sx/p[i].x , sy/p[i].y));
		}
		
		graham();
		
		for(int i=0;i<top-1;i++){
			if(cross(origin,pos,ret[i],ret[i+1]))
				continue;
			ans = max(ans,dis(pos)/dis(intersect(origin,pos,ret[i],ret[i+1])));
		}
		
		printf("%.10lf\n",ans);
	}
	return 0;
}

