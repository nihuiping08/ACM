/*

	题目大意是，某条道路由一些公司修建，修建道路的公司可以提供这条路上的连通，询问哪些公司
	可以提供从A到B的路径。类似于Floyed的算法。用二进制数表示一个集合。

	给出一个无向网, 读入一些站点的连接情况以及提供这些连接的公司. 然后接受若干组查询, 输出
	所有为ab站点提供连接的公司, 若无连接则输出 - .
    
	Warshall算法传递闭包的变种. 由于提供连接的只有26个公司, 名字是按小写字母给出的, 所
	以每个公司恰好对应整数中的一个二进制位, 即若为x和y点提供连接的公司有a, b, d, 则对应
	的二进制编码为00000000 00000000 00000000 00001011, 用矩阵m[x][y]存储x和y点间的编码. 
	然后可以推导出松弛公式: m[i][j]|=m[i][k]&m[k][j] 进行类似传递闭包的运算. 查询的时候若
	m[u][v]&(1<<i)成立, 表示状态位(2^i)对应1, 即第i+1个公司可以提供连接, 如此推下去...

*/
/*

我的理解：
	一个整形数使用32位二进制数表示，而小写的字母有26个，所以可以用二进制压缩的方法来做，
	00000000 00000000 00000000 00000000，每个字节中1所在位置代表该字母存在，输入时只需按
	右移操作即可完成该项操作，比如输入的是c的话，c-a = 2，则右移2位置之后，变成的是
	00000000 00000000 00000000 00000100，而算每对顶点之间有没有相同的公司能够提供A到B的
	路径时，只需要对有向图的传递闭包修改一下即可，每次松弛操作时，若A与B之间已经有通路，
	若还有其他的通路存在且可以由相同的公司提供从A到C，再由C到B，也是答案。所以松弛操作
	代码如下：
			map[i][j] |= map[i][k]&map[k][j];
	当问及某两顶点有没有符合要求时，因为之前的floyd算法已经算好每两个顶点存不存在通路，
	所以只需用枚举字母a到z，然后位移操作后再与map[x][y]位与运算即可

*/
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
#define X 202
int map[X][X],n;
string company;
void floyd()
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				map[i][j] |= map[i][k]&map[k][j];
}
void query()
{
	int x,y;
	while(scanf("%d%d",&x,&y),x||y)
	{
		for(char c='a';c<='z';c++)
			if(map[x][y]&(1<<c-'a'))
				cout<<c;
		if(!map[x][y])
			cout<<"-";
		cout<<endl;
	}
	cout<<endl;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int x,y;
	while(cin>>n,n)
	{
		memset(map,0,sizeof(map));
		while(scanf("%d%d",&x,&y),x||y)
		{
			cin>>company;
			for(int i=0;i<company.size();i++)
				map[x][y] |= 1<<(company[i]-'a');
		}
		floyd();
		query();
	}

	return 0;
}