/*

��Ŀ��
    ÿ����ƽ����x���y��Ͳ����޽�΢�ӷ�����������˵�����ǿ����໥ͨ�ŵģ�
    ���ڸ���n��������꣬����������Ҫ�޽����ٸ�΢�ӷ�����

������
    ��x[a],y[b]��������¼����(a,b)���ڵ�λ�ú��룬������������е�a��b�Ѿ�
    ���ֹ��ˣ����ò��鼯�ķ�ʽʹ�ø�λ�õĺ�����x[a]��y[b]�ĸ�������

*/
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int X = 200005;

int aa,bb,n;
int x[X],y[X],f[X];
bool use[X];

int find_set(int x)
{
    if(x!=f[x])
        f[x] = find_set(f[x]);
    return f[x];
}

int main()
{
    freopen("sum.in","r",stdin);
    scanf("%d%d%d",&aa,&bb,&n);
    int a,b;
    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));

    for(int i=1;i<=n;i++)
        f[i] = i;

    int pa,pb;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a,&b);
        if(x[a])
        {
            pa = find_set(x[a]);
            pb = find_set(i);
            if(pa!=pb)
                f[pb] = pa;
        }
        else
            x[a] = i;
        if(y[b])
        {
            pa = find_set(y[b]);
            pb = find_set(i);
            if(pa!=pb)
                f[pb] = pa;
        }
        else
            y[b] = i;
    }
    memset(use,false,sizeof(use));
    int ans = 0;
    for(int i=1;i<=n;i++)
    {
        pa = find_set(i);
        if(!use[pa])
        {
            use[pa] = true;
            ans++;
        }
    }
    cout<<ans-1<<endl;
    return 0;
}
