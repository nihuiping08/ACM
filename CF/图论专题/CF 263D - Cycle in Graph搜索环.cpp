/*
 * ��Ŀ��
 *		Ѱ��ͼ�г�������Ϊk+1�Ļ�
 *
 *	������
 *		��ʵ����ֱ�ӱ��ѿɹ�����
 *		���⣬������Ŀ�б�֤��ÿ�����㶼������k�����ڵĶ����������������ǿ��Դ�
 *		ÿ�����������Ѱ��һ������С�����ڶ��㣬Ȼ���ж��Ƿ�û�����������û�еĻ���
 *		����ֱ�Ӵ���������ĵ㿪ʼ�õ���������k+1�Ļ�������
 *	
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

const int X = 100005;

std::vector<int> vec[X];
int s[X];
int dfn[X];

int main(){
#ifndef ONLINE_JUDGE
	freopen("cf.txt","r",stdin);
#endif

	int n,m,k;
	while(~scanf("%d%d%d",&n,&m,&k)){
		int x,y;
		for(int i=1;i<=n;i++)
			vec[i].clear();
		while(m--){
			scanf("%d%d",&x,&y);
			vec[x].push_back(y);
			vec[y].push_back(x);
		}
		int top = 1;
		s[top] = 1;
		memset(dfn,0,sizeof(dfn));
		while(true){
			x = s[top];
			dfn[x] = top;
			int mind = n+1;
			int minp = -1;
			for(unsigned i=0;i<vec[x].size();i++){
				y = vec[x][i];
				if(dfn[y]<mind){
					mind = dfn[y];
					minp = y;
				}
			}
			if(mind==0)
				s[++top] = minp;
			else{
				printf("%d\n",top-mind+1);
				for(int i=mind;i<top;i++)
					printf("%d ",s[i]);
				printf("%d\n",s[top]);
				break;
			}
		}
	}

	return 0;
}
