/*

这题比较简单

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>

using namespace std;

#define debug cout<<"here"<<endl;

string ma = "+---+---+---+---+---+---+---+---+";
string ma2 = "|...|:::|...|:::|...|:::|...|:::|";
string ma3 = "|:::|...|:::|...|:::|...|:::|...|";
string map[20];
string qqq,s;

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);

    for(int i=0;i<18;i++)
    {
        map[i] = ma;
        map[++i] = ma2;
        map[++i] = ma;
        map[++i] = ma3;
    }
    cin>>qqq;
    int x,y;
    cin>>s;
    for(int i=0;s[i];i++)
    {
        if(s[i]>='A'&&s[i]<'Z')
        {
            x = s[++i]-'a';
            y = s[++i]-'0';
            y = 8-y;
            map[2*y+1][x*4+2] = s[i-2];
        }
        else if(s[i]>='a'&&s[i]<='z')
        {
            x = s[i]-'a';
            y = s[++i]-'0';
            y = 8-y;
            map[2*y+1][x*4+2] = 'P';
        }
    }

    cin>>qqq;
    cin>>s;
    for(int i=0;s[i];i++)
    {
        if(s[i]>='A'&&s[i]<'Z')
        {
            x = s[++i]-'a';
            y = s[++i]-'0';
            y = 8-y;
            map[2*y+1][x*4+2] = s[i-2]-'A'+'a';
        }
        else if(s[i]>='a'&&s[i]<='z')
        {
            x = s[i]-'a';
            y = s[++i]-'0';
            y = 8-y;
            map[2*y+1][x*4+2] = 'p';
        }
    }
    for(int i=0;i<17;i++)
        cout<<map[i]<<endl;
    return 0;
}
