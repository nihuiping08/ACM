/*

题目大意：
    住房部正在规划一个庞大的建设项目，他们看中了k块土地。这k块土地大小均为m*n，
    每块土最多只能盖一幢别墅，每幢别墅大小均为h*w，土地和别墅均为长方形。
    由于这些土地上还住着一些钉子户（编号A-Z），因而政府需要付钱购买钉子户的房
    子。购买时遵循如下规则：如果要付钱购买房子，则在同一块土地上只购买同一个
    钉子户的，比如A；如果在某一块地上购买了A拥有的房子，则在其他土地上不再购
    买A的房子。
    给出每块土地上钉子户的分布情况，求最多能盖多少幢房子。
    k<=30;m,n<=50;h,w<=50。

算法分析：
    最开始我理解错了题意，以为每块地只要大小允许，可以盖不止一幢别墅。
    实际情况中土贵如金，谁会如此奢侈？但是政府有钱，我们平头百姓有什么办法。
    二分图匹配，以土地为X集合，钉子户为Y集合，二分图用map[ ][ ]表示，
    结果用result表示。对第i块土地，可以分如下两种情况考虑：
    1． 该土地中不存在钉子户。
    2． 该土地中存在钉子户，但不用购买任何钉子户的土地就可以有足购的空间
    盖起一幢别墅。
    3．该土地空间不足以盖起一幢别墅，但当买下该块地中钉子户j的所有土地后，
    就有足购的空间。
    初始时置result=0，map[i][j]=false。对于情况1和2，直接将result++即可；
    对于情况3，则置map[i][j]=true。对map[ ][ ]求最大二分匹配m，最后结果为
    result+m。
    在情况3中判断买下j的土地是否空间足够，由于图最大也就50*50，直接枚举即
    可，四重循环。值得注意的是，土地和别墅的方向只有一种。如下图，也就是说
    在土地上，别墅只能横着盖，不能竖着盖。左边是正确的，右边是错误的。最开
    始我两种情况都考虑了，WA了好几次。其实正常来说，如果竖着盖能行，也应该
    是可以的呀。咱政府就是有钱，没办法。
    土地 m*n
    别墅h*w
    别墅w*h
    土地m*n
    求二分匹配我用的是匈牙利算法，DFS实现。匈牙利算法也可以用BFS或
    Hopcroft Carp实现，另外，求二分匹配也可以用网络流有关算法。DFS的
    优点是实现简洁、容易理解，而且对一般的题，效率也可以忍受。

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 105;

int n,m,k,h,w;

char s[31][51][51];
bool map[X][X];
bool use[X];
int ha[128];
int yy,ym[X];

bool dfs(int x)
{
    for(int i=1;i<=yy;i++)
        if(map[x][i]&&!use[i])
        {
            use[i] = true;
            if(ym[i]==-1||dfs(ym[i]))
            {
                ym[i] = x;
                return true;
            }
        }
    return false;
}

void hungry()
{
    memset(ym,-1,sizeof(ym));
    int ret = 0;
    for(int i=0;i<k;i++)
    {
        memset(use,false,sizeof(use));
        if(dfs(i))
            ret++;
    }
    cout<<ret<<endl;
}

int check(int block,int lx,int ly,int rx,int ry)
{
    bool ok = false;
    char str;
    for(int i=lx;i<=rx;i++)
        for(int j=ly;j<=ry;j++)
            if(s[block][i][j]!='0')
            {
                if(ok&&s[block][i][j]!=str)
                    return -1;
                ok = true;
                str = s[block][i][j];
            }
    if(!ok)
        return ++yy;
    return ha[(int)str];
}

int main()
{
    freopen("sum.in","r",stdin);
    int ncase,x;
    int temp;
    cin>>ncase;
    while(ncase--)
    {
        cin>>k>>n>>m>>h>>w;
        memset(use,false,sizeof(use));
        yy = 0;
        memset(ha,0,sizeof(ha));
        for(int i=0;i<k;i++)
            for(int j=0;j<n;j++)
            {
                scanf("%s",s[i][j]);
                for(int qq=0;s[i][j][qq];qq++)
                {
                    if(s[i][j][qq]!='0')
                    {
                        temp = (int)(s[i][j][qq]);
                        x = ha[temp];
                        if(!x)
                            ha[temp] = ++yy;
                    }
                }
            }
        memset(map,false,sizeof(map));
        for(int qq=0;qq<k;qq++)
            for(int i=h-1;i<n;i++)
                for(int j=w-1;j<m;j++)
                {
                    temp = check(qq,i-h+1,j-w+1,i,j);
                    if(temp==-1)
                        continue;
                    map[qq][temp] = true;
                }
        hungry();
    }
    return 0;
}
