/*

��Ŀ��
    ����n��������n����Χ��һȦ���ʳ������Ϊk��ʱ������������

������
    ���ǿ�������sum[]�����¼��֮ǰ(������)��������֮�ͣ�Ȼ���õ�������ά��
    һ���������У��������Ƕ�β��λ������׵�λ�ó�����k����ɾ����β��ÿ�μ�
    ��Ԫ�ص�ʱ����Ҫ����һ�´𰸣����´𰸾����ö���Ԫ�ؼ�����βԪ�أ�λ��Ϊ
    ��βԪ�ص�λ��+1�������׵�λ�á�����������
    6 3
    6 -1 2 -6 5 -5
    sum������
    6 5 7 1 6 1 7 6
    Ȼ��ά��һ�������������У�
    6
    5
    5 7
    1
    1 6
    1
    1 7
    1 6

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 200005;
#define debug puts("here");
const int inf = 2e9;

int a[X],sum[X];
int n,k,m;
int head,tail;

struct node
{
    int data,id;
}q[X];


int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        cin>>m>>k;
        n = m+k-1;
        sum[0] = 0;
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&a[i]);
            sum[i] = sum[i-1]+a[i];
        }
        for(int i=m+1;i<=n;i++)
            sum[i] = sum[i-1]+a[i-m];
        head = tail = 0;
        int ans = sum[1];
        int x = 1,y = 1;
        for(int i=1;i<=n;i++)
        {
            while(tail<head&&q[tail+1].id+k<i)
                tail++;
            while(tail<head&&q[head].data>sum[i])
                head--;
            if(tail<head)
            {
                if(i<=k&&sum[i]>ans)
                {
                    ans = sum[i];
                    x = 1;
                    y = i;
                }
                if(sum[i]-q[tail+1].data>ans)
                {
                    ans = sum[i]-q[tail+1].data;
                    x = q[tail+1].id+1;
                    y = i;
                }
            }
            head++;
            q[head].data = sum[i];
            q[head].id = i;
        }
        tail++;
        if(tail<head&&q[head].data-q[tail].data>ans)
        {
            ans = q[head].data-q[tail].data;
            x = q[tail].id+1;
            y = q[head].id;
        }
        if(q[head].id<=k&&q[head].data>ans)
        {
            ans = q[head].data;
            x = 1;
            y = q[head].id;
        }
        if(y>m)
            y -= m;
        cout<<ans<<" "<<x<<" "<<y<<endl;
    }
    return 0;
}
