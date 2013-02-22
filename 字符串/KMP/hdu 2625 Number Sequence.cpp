/*

kmp模板题，求匹配串的最小下标

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1000005;

int a[X],b[X],fail[X],n,m;

int main()
{
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        cin>>n>>m;
        for(int i=0;i<n;i++)
            scanf("%d",&b[i]);
        for(int i=0;i<m;i++)
            scanf("%d",&a[i]);
        fail[0] = -1;
        int j = -1;
        for(int i=1;i<m;i++)
        {
            while(j!=-1&&a[j+1]!=a[i])
                j = fail[j];
            if(a[j+1]==a[i])
                j++;
            fail[i] = j;
        }
        int pos = -1;
        j = -1;
        for(int i=0;i<n;i++)
        {
            while(j!=-1&&a[j+1]!=b[i])
                j = fail[j];
            if(a[j+1]==b[i])
                j++;
            if(j==m-1)
            {
                pos = i-m+2;
                break;
            }
        }
        cout<<pos<<endl;
    }
    return 0;
}
