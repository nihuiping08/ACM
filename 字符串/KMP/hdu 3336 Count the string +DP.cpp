#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int mod = 10007;
const int X = 200001;

char s[X];
int n;
int a[X],b[X];

int main()
{
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        cin>>n;
        scanf("%s",s);
        a[0] = -1;
        int j = -1;
        for(int i=1;s[i];i++)
        {
            while(j!=-1&&s[i]!=s[j+1])
                j = a[j];
            if(s[j+1]==s[i])
                j++;
            a[i] = j;
        }
        memset(b,0,sizeof(b));
        int ans = 0;
        /*for(int i=0;i<n;i++)
            cout<<a[i]<<" ";
            cout<<endl;*/
        for(int i=0;s[i];i++)
        {
            if(a[i]==-1)
                b[i]++;
            else
                b[i] = (b[i]+b[a[i]]+1)%mod;
        }
        for(int i=0;s[i];i++)
            ans = (ans+b[i])%mod;
        ans = ans%mod;
        cout<<ans<<endl;
    }
    return 0;
}
