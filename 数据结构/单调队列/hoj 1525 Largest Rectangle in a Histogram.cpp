/*

��Ŀ��
    ���������ϸ���n�����εĸߣ�����ÿ�����εĿ��ǵ�λһ���ֿ�����Щ�������һ���µľ��Σ�
    ���ܹ���ɾ��ε�������

����:
    ���õ������У�ά����ÿһ������Ϊ�ߵ�����£���ǰ������ܹ�����ľ��롣Ȼ����ö��ÿ��
    ���Σ��������ǵ���������´𰸡�
    ά���������еĻ��������ýṹ��洢һ��pos����¼�����ܹ��ҵ�����С����������һ������
    data(��¼���Ǹ�λ����)��
    ����������
    7 2 1 4 5 1 3 3
    ���ȣ����еĽ���������£�
    data  7   \\  2(����7����2,7����,2��pos����ָ����ǰ��)
    pos  -1   \\  -1

    data  1   \\  1   4��4��1С������û��ɾȥ������Ԫ�أ�4��pos�����Լ���λ���±��һ��
    pos   -1  \\  -1  2

    data 1   4 5  \\  1�����Է��֣�1������ʱ�������е�����Ԫ�ض���Ҫ���ӣ�
    pos  -1  2 3  \\  -1

    data 1   3      \\  1   3(��3�Ǳ�3)
    pos  -1  5      \\  -1  5
*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 100005;
#define debug puts("here");

int num[X],a[X],b[X],n;

struct node
{
    int pos,data;
}l[X],r[X];

int top;

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n,n)
    {
        for(int i=0;i<n;i++)
            scanf("%d",&num[i]);
        top = 0;
        l[0].data = num[0];
        l[0].pos = -1;
        a[0] = -1;
        int cnt;
        for(int i=1;i<n;i++)
        {
            cnt = top;
            while(top>=0&&l[top].data>=num[i])
                top--;
            if(top==-1)
            {
                l[++top].pos = -1;
                l[top].data = num[i];
            }
            else if(top==cnt)
            {
                l[++top].data = num[i];
                l[top].pos = i-1;
            }
            else
            {
                cnt = top;
                l[++top].pos = l[cnt+1].pos;
                l[top].data = num[i];
            }
            a[i] = l[top].pos;
        }
        top = 0;
        r[top].data = num[n-1];
        r[top].pos = n-1;
        b[n-1] = n-1;
        for(int i=n-2;i>=0;i--)
        {
            cnt = top;
            while(top>=0&&r[top].data>=num[i])
                top--;
            if(top==-1)
            {
                r[++top].pos = n-1;
                r[top].data = num[i];
            }
            else if(top==cnt)
            {
                r[++top].data = num[i];
                r[top].pos = i;
            }
            else
            {
                cnt = top;
                r[++top].pos = r[cnt+1].pos;
                r[top].data = num[i];
            }
            b[i] = r[top].pos;
        }
        long long sum = 0;
        for(int i=0;i<n;i++)
            sum = max(sum,(long long)(b[i]-a[i])*num[i]);
        cout<<sum<<endl;
    }
    return 0;
}
