/*
 *	分析：
 *		单调队列。
 *		这个程序优化的地方：可以只存标号，每次Q操作的时候直接二分。
 * */
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 200005;

struct node{
	int id,val;
}q[X];

int main(){
	int n,m;
	while(cin>>n>>m){
		int pre = 0;
		int x;
		char op[2];
		int head = 0,tail = 0;
		int len = 0;
		for(int i=1;i<=n;i++){
			scanf("%s%d",op,&x);
			if(op[0]=='A'){
				x = (x+pre)%m;
				while(tail&&q[tail-1].val<=x)
					tail --;
				q[tail].val = x;
				q[tail++].id = ++len;
			}
			else{
				for(int j=tail-1;j>=0;j--){
					if(q[j].id+x<=len)
						break;
					else
						pre = q[j].val;
				}
				printf("%d\n",pre);
			}
		}
	}
	return 0;
}
