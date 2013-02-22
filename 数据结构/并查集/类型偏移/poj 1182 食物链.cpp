/*

建议：做此题之前先做 poj 2524 和 poj 1611。这两道题都是并查集的基础应用。
关键词：并查集 相对关系
思路：（用一个并查集就够了，同时对每个节点保持其到根结点的相对类别偏移量）
     1.p[x]表示x的根结点。r[x]表示p[x]与x的关系。r[x] == 0 表示p[x]与x同类；1表示p[x]吃x；2表示x吃p[x]。

     2.怎样划分一个集合呢？
       注意，这里不是根据x与p[x]是否是同类来划分。而是根据“x与p[x]能否确定两者之间的关系”来划分，
	   若能确定x与p[x]的关系，则它们同属一个集合。

     3.怎样判断一句话是不是假话？
       假设已读入 D , X , Y , 先利用find_set()函数得到X , Y 所在集合的代表元素 rx , ry ,若它们在同
	   一集合（即 rx == ry ）则可以判断这句话的真伪（ 据 2. ）.
        若 D == 1 而 r[X] != r[Y] 则此话为假。（D == 1 表示X与Y为同类，而从r[X] != r[Y]可以推出 X 
		与 Y 不同类。矛盾。）
        若 D == 2 而 r[X] == r[Y] （X 与Y为同类）或者　r[X] == ( r[Y] + 1 ) % 3 （Y吃X ）则此话为假。

     4.上个问题中 r[X] == ( r[Y] + 1 ) % 3这个式子怎样推来？
      假设有Y吃X，那么r[X]和r[Y]的值是怎样的？
　       我们来列举一下: r[X] = 0 && r[Y] = 2 
                                       r[X] = 1 && r[Y] = 0
                                     r[X] = 2 && r[Y] = 1
          稍微观察一下就知道r[X] = ( r[Y] + 1 ) % 3;
      事实上，对于上个问题有更一般的判断方法：
           若 ( r[Y] - r[X] + 3 ) % 3 != D - 1 ，则此话为假。（来自poj 1182中的Discuss ）

     5.其他注意事项:
       在union_set( rx , ry )过程中若将S(ry)合并到S(rx)上，则相应的r[ry]必须更新为ry相对于rx的
	   关系。怎样得到更新关系式？
　   //以下来自poj 1182 中的Discuss
        用向量运算。
         现在已知关系: rx与x, ry与y, x与y，现在求rx与ry的关系。学过向量应该能做出来吧。。。
　   在find_set( x )过程中要更新所有从x到rx路径上的结点与代表元素的相对关系。

*/
/*

我的收获：
	基本了解了并查集的相对类别偏移量的应用，数组r[]用0 1 2分别表示同类，
	食物，天敌三种关系，每次输入时，若两者分别属于两个集合当中时，把他们
	合并，合并时需要注意类别关系，此时应该为r[py] = (r[x]-r[y]+2+d)%3,因为
	当r[x] = 0时，若d为1时表示同类，即r[x] = r[y],且r[py] = 0,同理可得d = 2时
	r[py] = 1

	其实这个操作相当于建树，树根为一个节点，然后子节点分别有着不同的r[x]，代表着
	与父节点的关系，另外

*/
#include <iostream>
#include <cstdio>
using namespace std;
#define X 50001
int r[X],pa[X],n,m,d;
int find_set(int x)
{
	if(x==pa[x])
		return x;
	int t = pa[x];
	pa[x] = find_set(t);
	r[x] = (r[x]+r[t])%3;
	return pa[x];
}
void union_set(int x,int y,int px,int py)
{
	pa[py] = px;
	r[py] = (r[x]-r[y]+d+2)%3;
}
void init()
{
	for(int i=1;i<=n;i++)
	{
		r[i] = 0;
		pa[i] = i;
	}
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	cin>>n>>m;
	int x,y,ans = 0;
	init();
	while(m--)
	{
		scanf("%d%d%d",&d,&x,&y);
		if(x>n||y>n||(d==2&&x==y))
			ans++;
		else
		{
			int px = find_set(x);
			int py = find_set(y);
			if(px==py)
			{
				if(d==1&&r[x]!=r[y])
					ans++;
				else if(d==2&&r[x]!=(r[y]+2)%3)
					ans++;
			}
			else
				union_set(x,y,px,py);
		}
	}
	cout<<ans<<endl;

	return 0;
}