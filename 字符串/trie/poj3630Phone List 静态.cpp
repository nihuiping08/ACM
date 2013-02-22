/*
��Ŀ��
	�ж���û�������绰�����ܹ���ǰ׺��ϵ
������
	��̬������Ȼ��Time limitted��ֻ�����þ�̬��������ֱ�Ӱ��ֵ����������Ƚ����������Ƿ�
	�ܹ���ǰ׺��ϵ�����������˵˵��̬������(Ӧ���ǶԵġ���)
*/
/*
#include <iostream>
#include <cstdio>
using namespace std;
struct trie
{	//�����ֵ���
	bool end;
	bool id;
	trie *p[10];//һ��ʮλ����
	trie()
	{
		end = false;//�жϴ˴���������û�е��ʣ��з���true
		id = false;//�ж��Ƿ����е������ù��Ӵ˴��ص�������Щ����
		for(int i=0;i<10;i++)//��ʼʱû�к��룬��NULL
			p[i] = NULL;
	}
}root;

bool make_tree(struct trie *r,char *s)
{	//��̬��������
	for(int i=0;s[i];i++)
	{
		if(r->p[s[i]-'0']==NULL)//�����ǰû���ù��˴��ĺ��룬��û��ǰ׺��ϵ
			r->p[s[i]-'0'] = new trie();
		else if(r->end)	//������λ�����к����Ҹú����ڴ˴���β������false
			return false;
		r->id = true;//��Ǵ˴��Ѿ����˺����߹�
		r = r->p[s[i]-'0'];
		if(r->end)	//������λ�����к����Ҹú����ڴ˴���β������false
			return false;
	}
	if(r->id==1||r->end)//�˴����к����ڴ˽�β���ߵ�ǰ�����Ǳ��˵�ǰ׺
		return false;
	r->id = true;//��Ǵ˴��Ѿ����˺����߹�
	r->end = true;//��Ǵ˴��Ѿ����˺����ڴ˽�β
	return true;
}

int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t,n;
	char s[12];
	cin>>t;
	while(t--)
	{
		struct trie qq;
		int flag = 0;//�����û���ҵ���ǰ׺��ϵ
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%s",s);
			if(!flag&&!make_tree(&qq,s))
				flag = 1;
		}
		if(flag)
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}
*/
/*
����ֱ���ÿ��ź����������Ƚ�ǰ�������Ƿ񹹳�ǰ׺��ϵ
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;
#define X 10005
string s[X];
int cmp(string s1,string s2)//�����ڲ��ȽϺ���
{
	return s1<s2;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t,n;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)
			cin>>s[i];
		sort(s,s+n,cmp);//ֱ������
		bool flag = 0;
		int i,j;
		for(i=0;i<n-1;i++)
		{
			int len = s[i].size();
			for(j=0;j<len;j++)
				if(s[i][j]!=s[i+1][j])//�����������ʱ�������ܹ���ǰ׺��ϵ
					break;
			if(j==len)//��ʾ���Թ���ǰ׺��ϵ
			{
				flag = true;
				break;
			}
		}
		if(flag)
			printf("NO\n");
		else
			printf("YES\n");
	}
}