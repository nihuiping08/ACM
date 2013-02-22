/*
Find a minimal interger K which is merely comprised of N and can be divided by M.
 
For example,11 is the minimal number that and be divided by 11, and it is 
comprised of two '1's, and 111111 can be divided by 13 which is comprised of six '1's.
 Input 
On each line of input , there will be two positive integer, N and M. N is 
a digit number, M is no more than 10000.
 Output 
On each single line, output the number of N, if no such K, output zero.
Sample Input
1 5
1 11
1 13

 Sample Output 
0
2
6

*/
/*
	˼·���Ӹ�λ��ʼ���㣬����111111%13==0�������λ(ʮ��λ)1��ʼ�㣬
		����(a+r*b)%b==a%b����111ʱ��111%13=7,71%13=6,61%13=9,91%13=0,��֤
		
		����Ϊʲôֻ�㵽k<=m�����ݳ���ԭ��(�Լ��ٶȰٿ�һ��)��m��֮�л�û�������Ļ���
		�ض�������ͬ����������Ϊ֮ǰ��ͬ������������Ϊֹ��û�������꣬
		���ԣ�����������ܱ���k��n����
*/
#include <iostream>
using namespace std;
int main()
{
	int n,m,i;
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>n>>m)
	{
		int count = 1;
		int num = n;
		while(num%m!=0&&count<=m)	//����û��������
		{
			count++;			//����
			num=10*(num%m)+n;	//����λ��ȡ�����ʮ�����ϵ���λ
		}
		if(count==m+1)			//���û��������
			cout<<0<<endl;
		else
			cout<<count<<endl;
	}
	return 0;
}
