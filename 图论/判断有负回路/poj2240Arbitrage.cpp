/*
��Ŀ��
	������һȦ���ܲ��ܻ�Ǯ�õ�����
������
	����ͼ�Ƿ��ڸ������⣬��Ϊ�漰ÿ�����㶼���ܴ��ڸ�����
	ֱ����flord�㷨������
*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#define X 35
string city[X],s1,s2;
double map[X][X];
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int m,n,x,y,cnt = 0;
	double dis;
	while(cin>>n,n)
	{
		memset(map,0,sizeof(map));
		for(int i=0;i<n;i++)
		{
			cin>>city[i];
			map[i][i] = 1;
		}
		cin>>m;
		for(int i=0;i<m;i++)
		{
			cin>>s1>>dis>>s2;
			for(int j=0;j<n;j++)//�ҳ�����յ�
			{
				if(s1==city[j])
					x = j;
				if(s2==city[j])
					y = j;
			}
			map[x][y] = dis;	//����ͼ��·������
		}
		for(int k=0;k<n;k++)	//fload�㷨
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					if(map[i][j]<map[i][k]*map[k][j])		//�ɳڲ���
						map[i][j] = map[i][k]*map[k][j];
		bool flag = true;
		for(int i=0;i<n;i++)
			if(map[i][i]>1)	//������ڸ���
				flag = false;
		if(!flag)
			printf("Case %d: Yes\n",++cnt);
		else
			printf("Case %d: No\n",++cnt);
	}
	return 0;
}