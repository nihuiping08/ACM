/*

����iostream��using namespace std;֮��Ȼ�ڴ����400��K������C++���˺�ʱ�䣬��
���ڴ档

��Ŀ��
	���⣺�ַ������������������ܿ��ţ��������е��ַ������õ������ӵ���ĸ��β��ӡ�
	���룺���е���ĸ��
	������Ƿ����������ӡ�

˼·��
	��26����ĸ�����ڵ㣬���ʿ����ߣ�����ÿһ�����ʣ�����ĸ�ĳ��ȼ�1��β��ĸ�������1��
	������ͨ��Ȼ���ж����ͼ�Ƿ���ͨ�����ж��Ƿ���ŷ��·����ŷ����·���ɡ�

ŷ����·:
	1.���ж������ȵ��ڳ���(����ͼ)������ֻ����������ĳ��Ȳ�������ȣ��Ҹ���������
		������һ�����ȵ�����ȼ�һ����һ����ȵ��ڳ��ȼ�һ��������ŷ��ͼ��
	2.���⣬��ͼ����ͨ�Ļ���Ҳû��ŷ��ͼ���ж�������ͨ������ͨ��dfsʵ�֣����忴����

*/
#include <cstdio>
#include <cstring>
#define X 27
int in[X],out[X],n,cnt;
bool use[X],map[X][X];
char s[1005];
void init()				//��ʼ��
{
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	memset(use,false,sizeof(use));
	memset(map,false,sizeof(map));
	cnt = 0;
}
void input()		//���뺯��
{
	int start,end;
	for(int i=0;i<n;i++)
	{
		scanf("%s",s);
		start = s[0]-'a';
		end = s[strlen(s)-1]-'a';
		in[end]++;		//���
		out[start]++;	//����
		use[start] = use[end] = true;
		map[start][end] = map[end][start] = true;
	}
}
void dfs(int start)				//�ӿ�ʼ�Ķ��㿪ʼ��Ѱ����һ������
{
	use[start] = false;
	cnt--;
	for(int i=0;i<X;i++)
		if(use[i]&&map[start][i])//û�б������Ҵ���ͨ·
			dfs(i);
}
bool connect()				//�ж�������ͨ
{
	int start;
	for(int i=0;i<X;i++)
		if(use[i])
			cnt++,start = i;//�ҵ�������ĸ����������һ��Ϊ���
	dfs(start);
	if(cnt)
		return false;
	return true;
}
bool is_euler()		//�ж���ȳ��ȹ�ϵ
{
	int start = 0,end = 0;
	for(int i=0;i<X;i++)
	{
		if(use[i])
		{
			if(in[i]==out[i])
				continue;
			else if(in[i]==out[i]+1)
				end++;
			else if(in[i]+1==out[i])
				start++;
			else
				return false;
		}
	}
	if(start==end)
		if(!start||start==1)
			return true;
	return false;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		init();
		input();
		if(is_euler()&&connect())
			printf("Ordering is possible.\n");
		else
			printf("The door cannot be opened.\n");
	}
	return 0;
}