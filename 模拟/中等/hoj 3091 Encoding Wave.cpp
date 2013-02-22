
/*
2
    _    __     __   _
___| |__|  |___|  |_|
   ____    _    ____
__|    |__| |__|

6
     _    __     __   _   _
____| |__|  |___|  |_| |_|
9
    ____    _    ______
___|    |__| |__|
*/

#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

#define debug cout<<"here"<<endl;

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int ncase;
    string u,d;
    scanf("%d",&ncase);
    getchar();
    while(ncase--)
    {
        getline(cin,u);
        getline(cin,d);
        int odd = 0;
        int len = u.size();
        for(int i=0;i<len;i++)
            if(u[i]=='_')
                odd++;
        cout<<odd<<endl;
        string ans_u,ans_d;
        if(u[0]=='_')
        {
            ans_u += "  ";
            ans_d += "_|";
        }
        else
        {
            ans_u +=" ";
            ans_d += "_";
        }
        ans_u += u;
        ans_d += d;
        if(odd&1)   //输出高电位
        {
            if(u[len-1]=='_')
            {
                ans_u += "_";
                ans_d += " ";
            }
            else
            {
                ans_u += " _";
                ans_d += "| ";
            }
        }
        else    ///输出低电位
        {
            if(u[len-1]=='_')
            {
                ans_u += "  ";
                ans_d += "|_";
            }
            else
            {
                ans_u += " ";
                ans_d += "_";
            }
        }
        len = ans_d.size();
        if(ans_u[len-1]=='_')
        {
            ans_u += "_";
            ans_d += " ";
        }
        else
        {
            ans_u += " _";
            ans_d += "| ";
        }
        cout<<ans_u<<endl<<ans_d<<endl;
    }
    return 0;
}
