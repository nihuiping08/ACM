/*

��Ŀ��
    n�������Ŷӣ��ָ�������n���˵ĸ߶ȣ�������֮����û�б���������һ���ߵĻ���
    ��ô�������˿��Ի��࿴���������ʶ������ж������ǿ����໥������

������
    ���÷������ĵ�����������¼��ǰ�����еĸ߶ȱ仯�����¼�����е�Ԫ�ش��ڵ�ǰ
    ����ͷ���еĸ߶�ʱ������ͷ�����ӣ�ֱ������Ϊ�ջ������˱��¼���ĸ߶ȸ��ߣ�
    ����ȣ�ʱΪֹ��Ȼ�������ʱ�Ĵ�����ÿ����ǰ�����ж��ٸ�����һ���߶ȵ��ˣ�Ȼ
    ��ֱ���ҵ�һ�������ߵ��˻����ѵ������ĩβΪֹ

*/
#include <cstdio>
#include <cstring>

const int X = 500001;

int a[X],n;
int q[X];

int main()
{
    freopen("sum.in","r",stdin);
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        int top = 1;
        q[0] = a[0];
        long long ans = 0;
        for(int i=1;i<n;i++)
        {
            while(top&&q[top-1]<a[i])
            {
                ans++;
                top--;
            }
            for(int j=top-1;j>=0;j--)
            {
                if(q[j]==a[i])
                    ans++;
                else
                {
                    ans++;
                    break;
                }
            }
            q[top] = a[i];
            top++;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
