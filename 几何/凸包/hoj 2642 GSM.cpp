/*

��Ŀ��
    ����n��ͭ����ÿ��ͭ��ӵ�����ͽ�ĺ���si,gi��Ȼ�������հ���Щͭ������һ���
    ���ĺ���Ϊm��Ȼ���ʽ�ĺ�������ж���

������
    ������ӳ��Ϊ���꣬�����ĺ�����ʾΪx������꣬Ȼ���ĺ�����ʾΪy�ᣬȻ����
    ͹������������ֱ��x���ֱ�ߣ���͹�������㣬�����㼴Ϊ������û�еĻ���ֱ��
    ���0
    ע�⣺
    1.�㶼��͹���ϵ�ֱ��
    2.����͹���ϵĵ�
    3.�㲻��͹���ϵķ�Χ��
    4.����������С�෴

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int X = 5005;
#define debug puts("here");
#define esp 1e-8

int n,m;

struct node
{
    double x,y;
    friend bool operator < (node a,node b)
    {
        return a.y<b.y||(a.y==b.y&&a.x<b.x);
    }
}res[X],p[X];
int top;

int dcmp(double x)  //�ж��Ƿ�Ϊ0
{
    if(abs(x)<esp)
        return 0;
    return x<0?-1:1;
}

int det(double x1,double y1,double x2,double y2)
{
    return dcmp(x1*y2-x2*y1);
}

bool del(int top,int i)
{
    if(det(res[top].x-res[top-1].x,res[top].y-res[top-1].y,p[i].x-res[top].x,p[i].y-res[top].y)<=0)
        return true;
    return false;
}

void graham()
{
    top = 1;
    res[0] = p[0];
    res[1] = p[1];
    for(int i=2;i<n;i++)
    {
        while(top&&del(top,i))
            top--;
        res[++top] = p[i];
    }
    int mint = top;
    res[++top] = p[n-2];
    for(int i=n-3;i>=0;i--)
    {
        while(top!=mint&&del(top,i))
            --top;
        res[++top] = p[i];
    }
}

double a[5];
int cnt;

void cal(int i) //���㽻��
{
    int x1,y1,x2,y2;
    x1 = res[i].x;
    y1 = res[i].y;
    x2 = res[i+1].x;
    y2 = res[i+1].y;
    a[cnt++] = y1+(m-x1)*1.0*(y2-y1)/(x2-x1);
}

void solve()
{
    a[0] = a[1] = 0;
    cnt = 0;
    for(int i=0;i<top;i++)
        if(m>=min(res[i].x,res[i+1].x)&&m<=max(res[i].x,res[i+1].x))
        {
            if(cnt==2)
                break;
            if(dcmp(res[i].x-m)==0&&dcmp(res[i+1].x-m)==0)//�պ��ص���͹���ϵ��߶�
            {
                a[cnt++] = min(res[i].y,res[i+1].y);
                a[cnt++] = max(res[i].y,res[i+1].y);
                break;
                continue;
            }
            if(dcmp(res[i].x-m)==0) //�պ�Ϊ͹���ϵĵ�
            {
                a[cnt++] = res[i].y;
                continue;
            }
            if(dcmp(res[i+1].x-m)==0)   //�պ�Ϊ��һλʱ��i��Ҫ��һ
            {
                a[cnt++] = res[i+1].y;
                i++;
                continue;
            }
            cal(i);
        }
    if(a[0]>a[1])
        swap(a[0],a[1]);
    printf("%.3lf %.3lf\n",a[0],a[1]);
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(cin>>n>>m)
    {
        for(int i=0;i<n;i++)
            scanf("%lf",&p[i].x);
        for(int i=0;i<n;i++)
            scanf("%lf",&p[i].y);
        sort(p,p+n);
        graham();
        solve();
    }
    return 0;
}
