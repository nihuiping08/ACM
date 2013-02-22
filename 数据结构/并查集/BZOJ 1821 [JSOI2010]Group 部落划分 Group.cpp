/*
 *	题目：
 *		给出n个野人的坐标，n个野人分别属于k个部落，现在问如何划分野人，使得每个部落之间的距离
 *		最小（部落之间的距离是部落中距离最近的两个野人的距离）
 *	分析：
 *		对于所有距离排序，然后利用并查集合并即可。。。
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int X = 1002;

struct node{
	int x,y;
	double dis;
	friend bool operator < (node a,node b){
		return a.dis<b.dis;
	}
}edge[X*X];

struct point{
	double x,y;
}p[X];

double dis (point a,point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int n,m;
int father[X];

int find_set(int x){
	if(x!=father[x])
		father[x] = find_set(father[x]);
	return father[x];
}

int main(){
	while(cin>>n>>m){
		int tot = 0;
		edge[1].dis = 0;
		for(int i=1;i<=n;i++){
			scanf("%lf%lf",&p[i].x,&p[i].y);
			for(int j=1;j<i;j++){
				edge[++tot].x = i;
				edge[tot].y = j;
				edge[tot].dis = dis(p[i],p[j]);
			}
			father[i] = i;
		}
		sort(edge+1,edge+tot+1);
		if(n==m){
			printf("%.2lf\n",edge[1].dis);
			continue;
		}
		for(int i=1;i<=tot;i++){
			int x = edge[i].x;
			int y = edge[i].y;
			x = find_set(x);
			y = find_set(y);
			if(x!=y){
				father[y] = x;
				n --;
				if(n<m){
					printf("%.2lf\n",edge[i].dis);
					break;
				}
			}
		}
	}
	return 0;
}
