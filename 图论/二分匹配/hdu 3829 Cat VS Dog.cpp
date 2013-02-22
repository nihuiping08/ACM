/*

��Ŀ��
    ����ϲ��è��ϲ����������ϲ������ϲ��è�����ڸ��������˵�ϲ�ã����Ҹ�è����ţ�
    ȥ��һ����è��ʹ������˸���

����:
    ����ÿ���˵�ϲ���п��ܲ�һ�������԰��˷�Ϊ���֣�X��ϲ��è��ϲ������Y��ϲ������ϲ��è��
    ��iϲ���Ķ���ǡ����j��ϲ���Ķ������i��ϲ���Ķ���jϲ����������֮�����ߣ�Ȼ��������
    ƥ��ret��p-ret/2��Ϊ����

*/
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int X = 1005;

int ym[X],n,c,d;
char a[X][5],b[X][5];
bool use[X];
bool map[X][X];

bool dfs(int u)
{
    int t;
    for(int v=1;v<=n;v++)
    {
        if(map[u][v]&&!use[v])
        {
            use[v] = true;
            t = ym[v];
            if(t==-1||dfs(t))
            {
                ym[v] = u;
                return true;
            }
        }
    }
    return false;
}

void hungry()
{
    memset(ym,-1,sizeof(ym));
    int ret = 0;
    for(int u=1;u<=n;u++)
    {
        memset(use,false,sizeof(use));
        if(dfs(u))
            ret++;
    }
    cout<<n-ret/2<<endl;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(cin>>c>>d>>n)
    {
        memset(map,false,sizeof(map));
        for(int i=1;i<=n;i++)
            scanf("%s%s",a[i],b[i]);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(strcmp(a[i],b[j])==0||strcmp(b[i],a[j])==0)
                    map[i][j] = true;
        hungry();
    }


    return 0;
}
