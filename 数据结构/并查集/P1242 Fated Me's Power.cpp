/*

��Ŀ��
    YO-GI-OH������ôһ��ħ���������������������ĳ�ַ������豻װ����ǿ���������
    ���ſ���д�ţ�dota�����������˹�ϵ����x��y�����˹�ϵ������y��z�����˹�ϵ��
    ��x��zҲ�����˹�ϵ������������һ��Ӷ���ţ��ܿ�ϧ���ǵ����ֶ������֡�����
    ����LYD(����LYD���⾭������(����GF��è����������)���̣�������Ҳ�÷�����
    T_T)���ڵ�Ӷ�����еĳ�Ա�������ַ�Ϊ2�����ɣ��������ͷ���������Ӧwwwwodddd
    Ҫ���������ô��������Ϣ������..�����������е�ÿ��������Ժͷ��������е���
    �������ù�����ճ��һ�����Ϊһ����Ϊ���������Ͻ�������뵼�壨BIOS���Ķ�����
    �����������Ͻ�������뵼�壨BIOS����������������ħ�������ṩ��������

������
    ��Ŀ�����е�˵�ò�̫���ף�A��֮��ŷ������������ģ�
    �ȶ�n�����˹�ϵ�ò��鼯�ķ�ʽ���ӡ��Ը�����LYD�������ҵ����ĸ�ĸ�ڵ����֣�
    ��ö�����еĽڵ�Ѱ�����Ǹ��Եĸ�ĸ�ڵ����֣�����LYD����ͬ����������ͷ�����
    ����ͳ�ƣ���������С�ļ���

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 4005;

int f[X],n,m,pos;
bool use[X];

int find_set(int x)
{
    if(x!=f[x])
        f[x] = find_set(f[x]);
    return f[x];
}

void init()
{
    memset(use,false,sizeof(use));
    use[1] = true;
    for(int i=2;i<X;i++)
        if(!use[i])
            for(int j=i+i;j<X;j+=i)
                use[j] = true;
}

int main()
{
    freopen("sum.in","r",stdin);
    init();
    scanf("%d%d",&n,&m);
    int x,y;
    for(int i=1;i<=n;i++)
        f[i] = i;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        x = find_set(x);
        y = find_set(y);
        if(x!=y)
            f[y] = x;
    }
    scanf("%d",&pos);
    int ans = 0;
    x = find_set(pos);
    pos = 0;
    for(int i=1;i<=n;i++)
    {
        y = find_set(i);
        if(x==y)
        {
            if(use[i])
                ans++;
            else
                pos++;
        }
    }
    cout<<min(pos,ans)<<endl;
    return 0;
}
