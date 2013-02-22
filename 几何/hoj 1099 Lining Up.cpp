/*

��Ŀ��
    �����㼯����������ж��ٵ���ͬһֱ����

������
    ֱ��ö�����еĵ㣬ʱ�临�Ӷ�ΪO(n^3)������ÿ�ζ�ö�ٵ�һ����Ϊ��㣬���б�ʣ�
    Ȼ�������ٰ�б����ͬ�ļ�������һ��ʱ�临�Ӷ�ΪO(n^2)

*/
/*
#include <iostream>
#include <cstdio>
using namespace std;
#define X 705
struct point
{
    int x,y;
}p[X];
int n,ret;
void online(point o,point a,point b)
{
    if((a.x-o.x)*(b.y-o.y)==(b.x-o.x)*(a.y-o.y))
        ret++;
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(cin>>n,n)
    {
        for(int i=1;i<=n;i++)
            scanf("%d%d",&p[i].x,&p[i].y);
        int ans = 0;
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                ret = 0;
                for(int k=j+1;k<=n;k++)
                    online(p[i],p[j],p[k]);
                ans = max(ans,ret);
            }
        }
        cout<<ans+2<<endl;
    }
    return 0;
}
*/
#include <algorithm>
#include <cstdio>
#include <iostream>
#define inf 1e20
using namespace std;
struct point
{
    int x,y;
}p[705];
double k[705];
double cal_k(point b,point a)   //��б��
{
    if(a.x==b.x)        //�����������ȣ�б�����޴�
        return inf;
    return (b.y-a.y)*1.0/(b.x-a.x);
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int n;
    while(scanf("%d",&n),n)
    {
        for(int i=0;i<n;i++)
            scanf("%d%d",&p[i].x,&p[i].y);
        int ans = 0,ret,cnt;
        for(int i=0;i<n;i++)
        {
            cnt = 0;
            for(int j=i+1;j<n;j++)
                k[cnt++] = cal_k(p[i],p[j]);//����б��
            sort(k,k+cnt);  //��б�ʽ�������
            ret = 1;
            for(int j=1;j<cnt;j++)  //ö��б���Ƿ���ȣ���������ͬ��㣬б����ȼ�Ϊ���㹲�ߣ�
            {
                if(k[j]==k[j-1])
                    ret++;
                else
                {
                    ans = max(ans,ret);
                    ret = 1;
                }
            }
            ans = max(ans,ret);
        }
        printf("%d\n",ans+1);
    }

    return 0;
}
