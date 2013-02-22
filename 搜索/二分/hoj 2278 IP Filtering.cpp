/*

��Ŀ:
    ����n��IP��ַ��Ȼ�����һ��IP��ַ���������IP��ַ�ڲ�����ЩIP��ַ����

������
    a.b.c.d�������Ȱ����е�����תΪa*2^24+b*2^16+c*2^8+d��Ȼ����뵽�ṹ���У�
    ��һ����ʼ��IP��ַ��������Ȼ����ֲ���ѯ�ʵ�IP��ַ�Ƿ�����ЩIP��

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int X = 1000005;

char s[20];
int n;

struct node
{
    long long x,y;
    friend bool operator < (node a,node b)
    {
        return a.x<b.x||(a.x==b.x&&a.y<b.y);
    }
}p[X];

long long chang()
{
    long long ans = 0,temp = (1<<24);
    long long cnt = 0;
    for(int i=0;s[i];i++)
    {
        if(s[i]>='0'&&s[i]<='9')
            cnt = cnt*10+s[i]-'0';
        else
        {
            ans += (cnt*temp);
            temp = temp>>8;
            cnt = 0;
        }
    }
    ans += cnt;
    return ans;
}

bool binary(long long ans)
{
    int left = 0;
    int right = n-1;
    int mid;
    while(left<right)
    {
        mid = (left+right)>>1;
        if(p[mid].x==ans)
        {
            left = mid;
            break;
        }
        else if(p[mid].x>ans)
            right = mid-1;
        else
            left = mid+1;
    }
    for(int i=left;i>=0;i--)
        if(ans>=p[i].x&&ans<=p[i].y)
            return true;
    return false;
}

int main()
{
    freopen("sum.in","r",stdin);
    n = 0;
    while(scanf("%s",s),s[0]!='#')
    {
        p[n].x = chang();
        scanf("%s",s);
        p[n].y = chang();
        if(p[n].x>p[n].y)
            swap(p[n].x,p[n].y);
        n++;
    }
    sort(p,p+n);
    int a,b,c,d;
    long long temp;
    while(scanf("%d.%d.%d.%d",&a,&b,&c,&d)!=EOF)
    {
        temp = ((long long)a<<24)+((long long)b<<16)+((long long)c<<8)+(long long)d;
        if(binary(temp))
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
