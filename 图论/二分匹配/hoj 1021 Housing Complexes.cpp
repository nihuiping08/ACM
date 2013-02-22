/*

��Ŀ���⣺
    ס�������ڹ滮һ���Ӵ�Ľ�����Ŀ�����ǿ�����k�����ء���k�����ش�С��Ϊm*n��
    ÿ�������ֻ�ܸ�һ��������ÿ��������С��Ϊh*w�����غͱ�����Ϊ�����Ρ�
    ������Щ�����ϻ�ס��һЩ���ӻ������A-Z�������������Ҫ��Ǯ�����ӻ��ķ�
    �ӡ�����ʱ��ѭ���¹������Ҫ��Ǯ�����ӣ�����ͬһ��������ֻ����ͬһ��
    ���ӻ��ģ�����A�������ĳһ����Ϲ�����Aӵ�еķ��ӣ��������������ϲ��ٹ�
    ��A�ķ��ӡ�
    ����ÿ�������϶��ӻ��ķֲ������������ܸǶ��ٴ����ӡ�
    k<=30;m,n<=50;h,w<=50��

�㷨������
    �ʼ�����������⣬��Ϊÿ���ֻҪ��С�������Ըǲ�ֹһ��������
    ʵ��������������˭������ݳޣ�����������Ǯ������ƽͷ������ʲô�취��
    ����ͼƥ�䣬������ΪX���ϣ����ӻ�ΪY���ϣ�����ͼ��map[ ][ ]��ʾ��
    �����result��ʾ���Ե�i�����أ����Է���������������ǣ�
    1�� �������в����ڶ��ӻ���
    2�� �������д��ڶ��ӻ��������ù����κζ��ӻ������ؾͿ������㹺�Ŀռ�
    ����һ��������
    3�������ؿռ䲻���Ը���һ���������������¸ÿ���ж��ӻ�j���������غ�
    �����㹺�Ŀռ䡣
    ��ʼʱ��result=0��map[i][j]=false���������1��2��ֱ�ӽ�result++���ɣ�
    �������3������map[i][j]=true����map[ ][ ]��������ƥ��m�������Ϊ
    result+m��
    �����3���ж�����j�������Ƿ�ռ��㹻������ͼ���Ҳ��50*50��ֱ��ö�ټ�
    �ɣ�����ѭ����ֵ��ע����ǣ����غͱ����ķ���ֻ��һ�֡�����ͼ��Ҳ����˵
    �������ϣ�����ֻ�ܺ��Ÿǣ��������Ÿǡ��������ȷ�ģ��ұ��Ǵ���ġ��
    ʼ����������������ˣ�WA�˺ü��Ρ���ʵ������˵��������Ÿ����У�ҲӦ��
    �ǿ��Ե�ѽ��������������Ǯ��û�취��
    ���� m*n
    ����h*w
    ����w*h
    ����m*n
    �����ƥ�����õ����������㷨��DFSʵ�֡��������㷨Ҳ������BFS��
    Hopcroft Carpʵ�֣����⣬�����ƥ��Ҳ�������������й��㷨��DFS��
    �ŵ���ʵ�ּ�ࡢ������⣬���Ҷ�һ����⣬Ч��Ҳ�������ܡ�

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
