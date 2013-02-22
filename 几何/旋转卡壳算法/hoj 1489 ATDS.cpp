/*

��Ŀ��
    �ҳ�n�����о�����Զ��������ˮ��

����:
    ������Ŀ�����ݱȽ�С��ֱ��ö�ټ��ɣ���Ȼ������ֱ����͹��������ת�����㷨��

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 6005;

int n;

struct node
{
    double x,y;
}p[X];

double dis(double x,double y)
{
    return sqrt(x*x+y*y);
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n)
    {
        for(int i=0;i<n;i++)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        double ans = 0,temp;
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
            {
                temp = dis(p[i].x-p[j].x,p[i].y-p[j].y);
                if(temp>ans)
                    ans = temp;
            }
        printf("%.2lf\n",ans);
    }
    return 0;
}
