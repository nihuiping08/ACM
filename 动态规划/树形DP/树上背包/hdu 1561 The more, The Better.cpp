/*

��Ŀ��
    ACboy��ϲ����һ��ս����Ϸ����һ����ͼ�ϣ���N���Ǳ���ÿ���Ǳ�����һ���ı��
    ��ÿ����Ϸ��ACboy������M���Ǳ����������ı�������ڵ���λ��ԭ����Щ
    �Ǳ�����ֱ�ӹ��ˣ�Ҫ������Щ�Ǳ������ȹ�������ĳһ���ض��ĳǱ���
    Input
    ÿ������ʵ�����Ȱ���2��������N,M.(1 <= M <= N <= 200);�ڽ�������N���ÿ�а�
    ��2��������a,b. �ڵ� i �У�a ����Ҫ���˵� i ���Ǳ������ȹ��˵� a ���Ǳ������
    a = 0 ��������ֱ�ӹ��˵� i ���Ǳ���b ����� i ���Ǳ��ı�������, b >= 0����
    N = 0, M = 0���������


Output
    ����ÿ������ʵ�������һ������������ACboy����M���Ǳ�����õ���౦���������

������
    ���ϱ��������ڳǱ���Ҫ���ݣ������Ҫ��һ������ֱ�ӹ��˵ĳǱ������Կ����ԳǱ�0
    ��Ϊ���ڵ㣬Ȼ��mֵ��һ�������ϱ�����ת�Ʒ���Ϊ
    dp[x][i] = max(dp[x][i],dp[x][i-j]+dp[y][j]);Ҫ����y�����ȹ���x

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 205;

int adj[X][X];
int top[X];
int n,m,a[X];
int dp[X][X];

void dfs(int x)
{
    int len = top[x];
    int y;
    for(int i=1;i<=m;i++)
        dp[x][i] = a[x];
    dp[x][0] = 0;
    for(int k=0;k<len;k++)
    {
        y = adj[x][k];
        dfs(y);
        for(int i=m;i;i--)
            for(int j=1;j<i;j++)
                dp[x][i] = max(dp[x][i],dp[x][i-j]+dp[y][j]);
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m,n||m)
    {
        int x;
        memset(top,0,sizeof(top));
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&x,&a[i]);
            adj[x][top[x]++] = i;
        }
        m++;
        memset(dp,0,sizeof(dp));
        dfs(0);
        cout<<dp[0][m]<<endl;
    }
    return 0;
}
