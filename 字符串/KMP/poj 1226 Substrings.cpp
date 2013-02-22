/*

题目：
    查找最长子串在所有给出的字符串或者它的反转的串中出现

分析：
    二分枚举所有可能的长度，然后用KMP算法判断该枚举的子串是否在所有给出的字符串
    或者它的翻转串中出现。

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 205;

char in[X][X],p[X];

int fail[X],len[X],n,lens;
int mid;    //mid 表示枚举的长度
int ma,pos; //ma表示所有串中长度最小的，pos表示该最短串的位置

void shift()    //模式串先与自己进行模式匹配，算出fail指针
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

bool kmp(char *s) //模式串与文本串进行模式匹配，判断是否在文本串中出现模式串
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

void solve()        //二分枚举函数
{
    int right = ma,left = 0;
    int temp;
    while(left<=right)
    {
        bool ok = true;
        mid = (left+right+1)>>1;
        temp = len[pos]-mid;
        for(int i=0;i<=temp;i++)
        {
            int cnt = 0;
            for(int j=i;j<mid+i;j++)    //从该位开始枚举所有该长度的子串
                p[cnt++] = in[pos][j];
            p[mid] = '\0';  //结束

            shift();    //计算fail指针

            ok = true;
            for(int j=0;j<n;j+=2)
            {
                if(j==pos)
                    continue;
                lens = len[j];
                if(kmp(in[j])||kmp(in[j+1]))//如果当前的串或反串中出现了枚举的串
                    continue;
                ok = false;
                break;
            }
            if(ok)  //如果所有都符合可直接跳出
                break;
        }
        if(ok)
            left = mid+1;
        else
            right = mid-1;
    }
    cout<<right<<endl;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int ncase,cnt;
    cin>>ncase;
    while(ncase--)
    {
        ma = 1000;
        scanf("%d ",&n);
        n = n<<1;
        for(int i=0;i<n;i+=2)
        {
            cnt = 0;
            gets(in[i]);
            len[i] = len[i+1] = strlen(in[i]);
            if(len[i]<ma)
            {
                ma = len[i];
                pos = i;
            }
            for(int j=len[i]-1;j>=0;j--)    //求反串
                in[i+1][cnt++] = in[i][j];
            in[i+1][cnt] = '\0';
        }
        solve();
    }
    return 0;
}
