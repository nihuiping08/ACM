/*

��Ŀ��
    ����n������������������[-500000,500000]�����밴�Ӵ�С��˳���������ǰm�������

������
    ֱ����������use[i+500000]��ʾ����i�ĳ��ִ�����Ȼ�����������

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1000002;
const int T = 500000;

int n,m;
int use[X];

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m)
    {
        int x;
        memset(use,0,sizeof(use));
        for(int i=0;i<n;i++)
        {
            scanf("%d",&x);
            use[x+T]++;
        }
        bool ok = false;
        for(int i=X-2;i>=0&&m;i--)
            while(use[i]&&m)
            {
                m--;
                if(ok)
                    printf(" ");
                else
                    ok = true;
                printf("%d",i-T);
                use[i]--;
            }
        cout<<endl;
    }
    return 0;
}
