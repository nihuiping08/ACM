/*
1.Next����
 
next[j]={
 
j=1ʱ��0
 
j!=1ʱ������Ӵ�����+1����P1P2��.Pk-1==Pj-k+1��.Pj-1,1<k<j,(����j=2ʱ��û������Ӵ���,
���next[2]һ��Ϊ1)���������1
 
}
 
next[j]=0˵��ģʽ����ƥ�䴮��Ҫ����һλ
 
next[j]��=0˵��ƥ�䴮�ĵ�ǰ�ַ���next[j]ƥ��
 
next������±��1��ʼ�����������ģʽ����T����ǰ�����һ���ַ���#������ʼ��next[1]=0
 
��ÿ��next[j](j>1)ʱʵ�������õ���next[j-1]��ֵ
 
����next[5]ʱ����鿴next[4]��ֵ�����T[4]=T[next[4]]����next[5]=next[4]+1
 
���T[4]!=T[next[4]]��T[4]����next[T[next[4]]]�ȣ������ȣ���next[5]=next[T[next[4]]]+1,
��˼������������nextֵΪ0���������������
 
��ˣ���׼�㷨���£�
 
void get_next()
{
	unsigned int length = strlen(t);
	next[0]=0;
	next[1]=0;
	unsigned int i=1,j=next[1];
	while(i<length-1){
		if(j==0){
			i++;
			j=1;
			next[i]=1;
			continue;
		}
		if(t[i]==t[j]){
				i++;
				j++;
				next[i]=j;
		}else 
			j = next[j];
	}
	
} 

��δ����Ż�һ�£�
 
scanf("%s",t+1);
 
t[0]=��#��;
 
void get_next()
{
	unsigned int length = strlen(t);
	//next[0]=0;
	next[1]=0;
	unsigned int i=1,j=next[1];
	while(i<length-1){
		
		if(j==0||t[i]==t[j]){
				i++;
				j++;
				next[i]=j;
		}else 
			j = next[j];
	}
	
}
*/
/*
��ʵ�һ�û����ϤKMP�㷨�ˣ�
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 1000005
char s[X],p[X];
int Next[X],len1,len2;
void shift()	//�����ƶ���ģ��
{
	int i,j = -1;
	Next[0] = -1;
	for(i=1;i<len2;i++)
	{
		while(j!=-1&&s[j+1]!=s[i])
			j = Next[j];
		if(s[j+1]==s[i])
			j++;
		Next[i] = j;
	}
}
int kmp()//kmp��match����
{
	int j = -1, k = 0;
	shift();
	for(int i=0;i<len2;i++)
	{
		while(j!=-1&&s[j+1]!=p[i])
			j = Next[j];
		if(s[j+1]==p[i])
			j++;
		if(j==len1-1)
		{
			k++;
			j = Next[j];
		}
	}
	return k;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t;
	cin>>t;
	while(t--)
	{
		scanf("%s%s",s,p);
		len1 = strlen(s);
		len2 = strlen(p);
		cout<<kmp()<<endl;
	}
	return 0;
}
