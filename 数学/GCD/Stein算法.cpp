/*
Stein算法 
欧几里德算法是计算两个数最大公约数的传统算法，他无论从理论还是从效率上都是很好的。
但是他有一个致命的缺陷，这个缺陷只有在大素数时才会显现出来。 

考虑现在的硬件平台，一般整数最多也就是64位，对于这样的整数，计算两个数之间的模是
很简单的。对于字长为32位的平台，计算两个不超过32位的整数的模，只需要一个指令周期，
而计算64位以下的整数模，也不过几个周期而已。但是对于更大的素数，这样的计算过程就不
得不由用户来设计，为了计算两个超过 64位的整数的模，用户也许不得不采用类似于多位数除
法手算过程中的试商法，这个过程不但复杂，而且消耗了很多CPU时间。对于现代密码算法，要
求计算 128位以上的素数的情况比比皆是，设计这样的程序迫切希望能够抛弃除法和取模。 

Stein算法由J. Stein 1961年提出，这个方法也是计算两个数的最大公约数。和欧几里德算法 
算法不同的是，Stein算法只有整数的移位和加减法，这对于程序设计者是一个福音。 

为了说明Stein算法的正确性，首先必须注意到以下结论： 

gcd(a,a) = a，也就是一个数和他自身的公约数是其自身 
gcd(ka,kb) = k gcd(a,b)，也就是最大公约数运算和倍乘运算可以交换，特殊的，当k=2时，说明
两个偶数的最大公约数必然能被2整除 
*/
#include <iostream>
using namespace std;
long long stein(long long a,long long b)
{
	if(a<b)
		swap(a,b);
	if(b==0)
		return a;
	if(a%2==0&&b%2==0)		//当两者都能整除2时
		return 2*stein(a/2,b/2);
	if(a%2==0)
		return stein(a/2,b);
	if(b%2==0)
		return stein(a,b/2);
	return stein((a+b)/2,(a-b)/2);
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	long long a,b;
	while(cin>>a>>b)
		cout<<stein(a,b)<<endl;
	return 0;
}