/*

��Ŀ��
    ģ���������ʱ��

������
    �ȰѴ𰸶�ֻΪ�ո�Ȼ��ö��ÿһ�����֣�����Ӧ�Ĵ����������޸ģ������Ļ���ֻ��
    ������������8�������Ķ�����ʵ���ˡ�����ܼ�����ֻ��100����

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 205;

char map[X][X],s[X];
int n;

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(scanf("%d%s",&n,s),n||s[0]!='0')
    {
        int id;
        int y = 0;
        int len = strlen(s);
        for(int i=0;i<2*n+3;i++)
        {
            for(int j=0;j<len*(n+3)-1;j++)
                map[i][j] = ' ';
            map[i][len*(n+3)-1] = '\0';
        }
        for(int q=0;s[q];q++)
        {
            id = s[q]-'0';
            if(id==0)
            {
                for(int i=y+1;i<y+n+1;i++)
                    map[0][i] = map[2*n+2][i] = '-';
                for(int i=1;i<=n;i++)
                    map[i][y] = map[i+n+1][y] = map[i][y+n+1] = map[i+n+1][y+n+1] = '|';
            }
            else if(id==1)
            {
                for(int i=1;i<=n;i++)
                    map[i][y+n+1] = map[i+n+1][y+n+1] = '|';
            }
            else if(id==2)
            {
                for(int i=y+1;i<y+n+1;i++)
                    map[0][i] = map[n+1][i] = map[2*n+2][i] = '-';
                for(int i=1;i<=n;i++)
                    map[i+n+1][y] = map[i][y+n+1] = '|';
            }
            else if(id==3)
            {
                for(int i=y+1;i<y+n+1;i++)
                    map[0][i] = map[n+1][i] = map[2*n+2][i] = '-';
                for(int i=1;i<=n;i++)
                    map[i][y+n+1] = map[i+n+1][y+n+1] = '|';
            }
            else if(id==4)
            {
                for(int i=y+1;i<y+n+1;i++)
                    map[n+1][i]= '-';
                for(int i=1;i<=n;i++)
                    map[i][y] = map[i][y+n+1] = map[i+n+1][y+n+1] = '|';
            }
            else if(id==5)
            {
                for(int i=y+1;i<y+n+1;i++)
                    map[0][i] = map[n+1][i] = map[2*n+2][i] = '-';
                for(int i=1;i<=n;i++)
                    map[i][y] = map[i+n+1][y+n+1] = '|';
            }
            else if(id==6)
            {
                for(int i=y+1;i<y+n+1;i++)
                    map[0][i] = map[n+1][i] = map[2*n+2][i] = '-';
                for(int i=1;i<=n;i++)
                    map[i][y] = map[i+n+1][y] = map[i+n+1][y+n+1] = '|';
            }
            else if(id==7)
            {
                for(int i=y+1;i<y+n+1;i++)
                    map[0][i] = '-';
                for(int i=1;i<=n;i++)
                    map[i][y+n+1] = map[i+n+1][y+n+1] = '|';
            }
            else if(id==8)
            {
                for(int i=y+1;i<y+n+1;i++)
                    map[0][i] = map[n+1][i] = map[2*n+2][i] = '-';
                for(int i=1;i<=n;i++)
                    map[i][y] = map[i+n+1][y] = map[i][y+n+1] = map[i+n+1][y+n+1] = '|';
            }
            else
            {
                for(int i=y+1;i<y+n+1;i++)
                    map[0][i] = map[n+1][i] = map[2*n+2][i] = '-';
                for(int i=1;i<=n;i++)
                    map[i][y] = map[i][y+n+1] = map[i+n+1][y+n+1] = '|';
            }
            y += n+3;
        }
        for(int i=0;i<(2*n+3);i++)
            puts(map[i]);
        puts("");
    }

    return 0;
}
