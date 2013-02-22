/*

��֦����

*/
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int len[22],n,ave,sum;
bool use[22];

bool dfs(int rest,int cur,int p)    //rest����ʣ��ı�����cur:��ǰ���Ѿ�ƥ��ĳ��ȣ�p��ö��λ��
{               //  p����֦
    int temp;
    if(rest==1)
        return true;
    for(int i=p;i<n;i++)
    {
        if(use[i])
            continue;
        use[i] = true;
        temp = cur+len[i];
        if(temp==ave)   //�պ�ʹ�õ�ǰ�ı�ƥ��
        {
            if(dfs(rest-1,0,1)) //��ǰƥ��Ļ���Ӧ�ó�=��1��ʼ����Ϊ��0����ƥ�䣬ʣ�µĿ϶���ƥ��
                return true;
        }
        else if(temp<ave)
        {
            if(dfs(rest,temp,i+1))
                return true;
        }
        if(!i)
            return false;
        use[i] = false;
        while(len[i]==len[i+1]) //��֦
            i++;
    }
    return false;
}
bool cmp(int a,int b)
{
    return a>b;
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(use,false,sizeof(use));
        sum = 0;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%d",&len[i]);
            sum += len[i];
        }
        if(sum%4)   //��֦
        {
            printf("no\n");
            continue;
        }
        ave = sum/4;
        sort(len,len+n,cmp);
        if(ave<len[0])   //��֦
        {
            printf("no\n");
            continue;
        }
        if(dfs(4,0,0))
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
