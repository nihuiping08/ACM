/*
 * ��Ŀ��
 *		n����Χ��һ��Ȧ�����ڿ�ʼ����������5���˵�ʱ�򣬱�Ŵ�1��5��ʱ�뿪ʼ����������
 *		�ı������Ϊ1-2,2-3,3-4,4-5,5-1,1-3,2-4,3-5,4-1,5-2�����ڸ���2*n����ϵ�����Ƿ�
 *		�ܹ�ȷ���˵���λ˳��
 *
 * ������
 *		dfs��ö�٣����ǻ���ͼ���Է��֣����������ڵ�����Ϊa,b,cʱ���϶��б�a-b,b-c,a-c
 *		�������ǿ��Դ�1��ʼ���������������ڵ��ĸ��㣬�����ڱ�a-b,b-c,a-c���϶����Դ�a����
 *		����b������b�������������ĵ����Żص�c�����Կ���ֱ��dfs����
 *
 * */
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

#define debug puts("here");

const int X = 200005;

int ans[X],n;
bool use[X];
vector<int> vec[X];

bool dfs(int pre,int now,int len,int start){
	ans[len] = now;
	use[now] = true;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++){
			int x = vec[pre][i];
			int y = vec[now][j];
			if(x!=y)
				continue;
			if(len==n-1 && x==start)
				return start == x;
			if( !use[x] )
				return dfs(now,x,len+1,start);
		}
	return false;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("cf.txt","r",stdin);
#endif

	while(~scanf("%d",&n)){
		int x,y;
		int m = n<<1;
		for(int i=1;i<=n;i++)
			vec[i].clear();
		while(m--){
			scanf("%d%d",&x,&y);
			vec[x].push_back(y);
			vec[y].push_back(x);
		}
		bool ok = true;
		for(int i=1;i<=n;i++){
			if(vec[i].size()!=4){
				puts("-1");
				ok = false;
				break;
			}
		}
		if(!ok)
			continue;
		for(int i=0;i<4&&ok;i++)
			for(int j=i+1;j<4;j++){
				int x = vec[1][i];
				int y = vec[1][j];
				ans[1] = 1;
				ans[n] = y;
				memset(use,false,sizeof(use));
				use[1] = true;
				use[x] = use[y] = true;
				if(dfs(1,x,2,y)){
					for(int k=1;k<n;k++)
						printf("%d ",ans[k]);
					printf("%d\n",ans[n]);
					ok = false;
					break;
				}
			}
		if(ok)
			puts("-1");
	}
	return 0;
}

