#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 210005;

char s[X],str[X];
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
        if(i+rad[i]>mx)
        {
            mx = i+rad[i];
            id = i;
        }
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(scanf("%s",s)!=EOF)
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
        cout<<ans-1<<endl;
    }

    return 0;
}
