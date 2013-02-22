/*

题目：
    Given two strings a and b we define a*b to be their concatenation. For example,
    if a = "abc" and b = "def" then a*b = "abcdef". If we think of concatenation as
    multiplication, exponentiation by a non-negative integer is defined in the normal
    way: a^0 = "" (the empty string) and a^(n+1) = a*(a^n).

分析：
    a  b  c  d  a b c d a b c d的next分别为
    -1 -1 -1 -1 0 1 2 3 4 5 6 7
    我们发现，next[i]指向的是第几个字符，并且i字符的前缀拥有next[i]字符的所有前缀。另外，
    当next[len-1]的时候，用len-next[len-1]-1后，得到的是a（题目中的要求串）的长度，用len
    除以他就是答案了

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1000005;

char s[X];
int next[X];

int main()
{
    freopen("sum.in","r",stdin);
    while(gets(s),s[0]!='.')
    {
        //memset(next,-1,sizeof(next));
        int j = -1;
        next[0] = -1;
        for(int i=1;s[i];i++)
        {
            while(j!=-1&&s[i]!=s[j+1])
                j = next[j];
            if(s[i]==s[j+1])
                j++;
            next[i] = j;
        }
        /*for(int i=0;s[i];i++)
            cout<<next[i]<<"  ";
        puts("");*/
        int len = strlen(s);
        int ans = len/(len-next[len-1]-1);
        printf("%d\n",ans);
    }
    return 0;
}
