/*

��Ŀ��
    ����n���ַ����������ǵ�������Ӵ���������ͬ���ȵĻ�������ֵ�����С��

������
    ����+KMP�����ҳ������ַ�������С���ȵĴ�������ö�ٸô����г��ȵ��Ӵ���Ȼ����KMP
    �ж��Ƿ����е��ַ��������и��Ӵ����еĻ������´�

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int NUM = 4005;
const int LEN = 205;

char in[NUM][LEN],ans[LEN],p[LEN];
int fail[LEN],len[NUM],n,lens,mid,ma,pos;

void shift()
{
    fail[0] = -1;
    int j = -1;
    for(int i=1;i<mid;i++)
    {
        while(j!=-1&&p[i]!=p[j+1])
            j = fail[j];
        if(p[i]==p[j+1])
            j++;
        fail[i] = j;
    }
}

bool kmp(char *s)
{
    int j = -1;
    for(int i=0;i<lens;i++)
    {
        while(j!=-1&&s[i]!=p[j+1])
            j = fail[j];
        if(s[i]==p[j+1])
            j++;
        if(j+1==mid)
            return true;
    }
    return false;
}

void solve()    //����ö��
{
    int left = 0,right = ma;
    int temp,cnt;
    bool ans_flag = false;
    bool ok;

    while(left<=right)
    {
        mid = (left+right+1)>>1;
        temp = len[pos]-mid;
        ok = true;
        bool flag = false;
        for(int i=0;i<=temp;i++)
        {
            cnt = 0;
            for(int j=i;j<mid+i;j++)
                p[cnt++] = in[pos][j];
            p[mid] = '\0';

            shift();

            ok = true;

            for(int j=0;j<n;j++)
            {
                if(j==pos)
                    continue;

                lens = len[j];
                if(kmp(in[j]))
                    continue;

                ok = false;
                break;
            }

            if(ok)  //���еĴ���ӵ�и��Ӵ������´�
            {
                if(ans_flag)
                {
                    if(flag&&strcmp(ans,p)>0)
                        strcpy(ans,p);
                    else if(!flag)
                    {
                        flag = true;
                        strcpy(ans,p);
                    }
                }
                else
                {
                    flag = true;
                    ans_flag = true;
                    strcpy(ans,p);
                }
            }
        }
        if(flag)
            left = mid+1;
        else
            right = mid-1;
    }
    if(right)
        printf("%s\n",ans);
    else
        printf("IDENTITY LOST\n");
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(scanf("%d ",&n),n)
    {
        ma = 10000;
        for(int i=0;i<n;i++)
        {
            gets(in[i]);
            len[i] = strlen(in[i]);
            if(ma>len[i])
            {
                ma = len[i];
                pos = i;
            }
        }
        solve();
    }
    return 0;
}
