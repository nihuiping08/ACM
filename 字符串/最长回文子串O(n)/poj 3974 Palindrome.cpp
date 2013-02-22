#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int X = 2000005;

char str[X],s[X];
int rad[X],n,len,ans;

void Manacher()
{
    int id;
    int mx = 0;
    for(int i=1;i<n;i++)
    {
        if(mx>i)
            rad[i] = min(mx-i,rad[2*id-i]);
        else
            rad[i] = 1;
        for(;str[i-rad[i]]==str[i+rad[i]];rad[i]++)
            ;
        if(rad[i]+i>mx)
        {
            mx = rad[i]+i;
            id = i;
        }
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int cnt = 0;
    while(gets(s),s[0]!='E')
    {
        len = strlen(s);

        n = 2;
        str[0] = '@';
        str[1] = '#';
        for(int i=0;i<len;i++)
        {
            str[n++] = s[i];
            str[n++] = '#';
        }
        str[n] = '\0';
        Manacher();

        ans = 0;
        for(int i=1;i<n;i++)
            ans = max(ans,rad[i]);
        printf("Case %d: %d\n",++cnt,ans-1);
    }

    return 0;
}
