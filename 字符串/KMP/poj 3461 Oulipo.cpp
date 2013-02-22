/*
1.Next数组
 
next[j]={
 
j=1时，0
 
j!=1时，最大子串长度+1，即P1P2….Pk-1==Pj-k+1….Pj-1,1<k<j,(看来j=2时是没有最大子串的,
因此next[2]一定为1)其它情况，1
 
}
 
next[j]=0说明模式串与匹配串都要后移一位
 
next[j]！=0说明匹配串的当前字符与next[j]匹配
 
next数组的下标从1开始，因此我们在模式串（T）的前面添加一个字符‘#’，初始化next[1]=0
 
求每个next[j](j>1)时实际上利用到上next[j-1]的值
 
如求next[5]时，则查看next[4]的值，如果T[4]=T[next[4]]，则next[5]=next[4]+1
 
如果T[4]!=T[next[4]]，T[4]再与next[T[next[4]]]比，如果相等，则next[5]=next[T[next[4]]]+1,
如此继续，如果它的next值为0，则跳到其它情况
 
因此，标准算法如下：
 
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

这段代码优化一下：
 
scanf("%s",t+1);
 
t[0]=’#’;
 
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
其实我还没有熟悉KMP算法了，
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 1000005
char s[X],p[X];
int Next[X],len1,len2;
void shift()	//计算移动的模板
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
int kmp()//kmp的match函数
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
