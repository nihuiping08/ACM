/*

��Ŀ��
    ��n�䷿�ӣ�ѡ��һЩ���ص�������������ΰ���ʹ���ܷ�����С�������С
    ����

������
    ����n���������X��Y������ͼ��һ���걸ƥ���ͼ����ض�����һ��·ʹ��
    X����i��Y����j������������Y����i�ض��ܹ���X���ҵ�һ����ͨ�ıߣ��ɴ�
    �������һ����·��
    �����ͼ��ò����������������һ�������µ���������һ������ͨ�������ͼ
    �����ƥ��֮�У��ѳ�ʼ���Լ���ͼȫȡ�������������ȡ������

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 105;
const int inf = 1e7;

#define debug puts("here");

int mnum,hnum;
int map[X][X],r,c;
int match[X],lx[X],ly[X];
bool visx[X],visy[X];
char s[X];

bool dfs(int x)
{
    visx[x] = true;
    for(int i=1;i<=hnum;i++)
    {
        if(!visy[i]&&lx[x]+ly[i]==map[x][i])
        {
            visy[i] = true;
            if(match[i]==0||dfs(match[i]))
            {
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

void KM()
{
    memset(match,0,sizeof(match));
    for(int i=1;i<=mnum;i++)
    {
        while(true)
        {
            memset(visx,false,sizeof(visx));
            memset(visy,false,sizeof(visy));
            if(dfs(i))
                break;
            int MIN = inf;
            for(int j=1;j<=mnum;j++)
                if(visx[j])
                    for(int qq=1;qq<=hnum;qq++)
                        if(!visy[qq])
                            MIN = min(MIN,map[j][qq]-lx[j]-ly[qq]);
            for(int j=1;j<=mnum;j++)
                if(visx[j])
                    lx[j] += MIN;
            for(int j=1;j<=hnum;j++)
                if(visy[j])
                    ly[j] -= MIN;
        }
    }
    int sum = 0;
    for(int i=1;i<=hnum;i++)
    {
        sum += map[match[i]][i];
        if(map[match[i]][i]==inf)
        {
            puts("-1");
            return;
        }
    }
    printf("%d\n",sum);
}

int main()
{
    freopen("sum.in","r",stdin);
    int x,y;
    while(cin>>r>>c)
    {
        mnum = hnum = r;
        for(int i=1;i<=r;i++)
            for(int j=1;j<=r;j++)
                map[i][j] = inf;
        int z;
        for(int j=1;j<=c;j++)
        {
            scanf("%d%d",&x,&y);
            scanf("%d",&z);
            map[x][y] = min(map[x][y],z);
        }
        for(int i=1;i<=r;i++)
            lx[i] = inf;
        memset(ly,0,sizeof(ly));
        for(int i=1;i<=mnum;i++)
            for(int j=1;j<=hnum;j++)
                lx[i] = min(lx[i],map[i][j]);
        KM();
    }
    return 0;
}
