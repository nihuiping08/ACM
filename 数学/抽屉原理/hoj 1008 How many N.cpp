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
	思路：从高位开始计算，比如111111%13==0，从最高位(十万位)1开始算，
		根据(a+r*b)%b==a%b，当111时，111%13=7,71%13=6,61%13=9,91%13=0,得证
		
		至于为什么只算到k<=m，根据抽屉原理(自己百度百科一下)，m个之中还没有整除的话，
		必定会有相同的余数，因为之前相同的余数到现在为止还没被整除完，
		所以，这个数不可能被这k个n整除
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
		while(num%m!=0&&count<=m)	//当还没被整除完
		{
			count++;			//计数
			num=10*(num%m)+n;	//高数位的取余乘以十，加上低数位
		}
		if(count==m+1)			//如果没有整除完
			cout<<0<<endl;
		else
			cout<<count<<endl;
	}
	return 0;
}
