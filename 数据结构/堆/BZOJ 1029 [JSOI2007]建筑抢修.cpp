/*
 *	题目：
 *		每个任务需要ai时间完成，并且需要在时间bi或之前完成，问如何安排任务完成顺序，使得完成
 *		任务的数量最多
 *
 *	分析：
 *		贪心，先对期限排序，然后用最大堆维护需要完成的时间ai
 *		1.当now + ai <= bi时，ans + 1 ，更新now,把ai插入到堆中
 *		2.当now + ai > bi时，若堆的最大元素大于ai时，将该元素（aj,bj）替换为ai，得到的序列答案
 *		不会减少。因为替换之后，时间期限bi必定大于bj，所以可以完成该任务，另外替换之后，所需的
 *		时间减少了，所以替换是正确的。
 *
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 150005;

#define debug puts("here");

struct Heap{
	int a[X];
	int s;

	void insert(int x){
		a[++s] = x;
		for(int i=s;i>1;i>>=1){
			if(a[i] > a[i>>1])
				swap(a[i],a[i>>1]);
			else
				break;
		}
	}

	void down(int x){
		a[1] = x;
		int i = 1;
		int j = 2;
		while(j<=s){
			if(j+1<=s && a[j+1]>a[j])
				j ++;
			if(a[j]>a[i]){
				swap(a[i],a[j]);
				i = j;
				j <<= 1;
			}
			else
				break;
		}
	}

	void init(){
		memset(a,0,sizeof(a));
		s = 0;
	}

	void display(){
		for(int i=1;i<=s;i++)
			cout<<a[i]<<" ";
		cout<<endl;
	}
}heap;

struct node{
	int last,time;
	friend bool operator < (node a,node b){
		return a.time < b.time || (a.time==b.time&&a.last<b.last);
	}
}p[X];

int main(){
	int n;
	while(cin>>n){
		for(int i=0;i<n;i++)
			scanf("%d%d",&p[i].last,&p[i].time);
		
		sort(p,p+n);
		heap.init();
		int now = 0;
		int ans = 0;

		for(int i=0;i<n;i++){
			if(now+p[i].last<=p[i].time){
				ans ++;
				now += p[i].last;
				heap.insert(p[i].last);
			}
			else if(heap.a[1]>p[i].last){
				now -= heap.a[1]-p[i].last;
				heap.down(p[i].last);
			}
			//heap.display();
		}
		cout<<ans<<endl;
	}

	return 0;
}
