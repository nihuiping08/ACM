/*

题目：
    问串有多少个循环节

分析：
    KMP算法的fail指针是指向该位置的字符相同的位置，且该位置之前有相同的前缀串。

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1000005;

char p[X];
int len;
int fail[X];

void shift()
{
    int j = -1;
    fail[0] = -1;
    for(int i=1;i<len;i++)
    {
        while(j!=-1&&p[i]!=p[j+1])
            j = fail[j];
        if(p[i]==p[j+1])
            j++;
        fail[i] = j;
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(gets(p),p[0]!='.')
    {
        len = strlen(p);
        shift();
        if(len%(len-fail[len-1]-1)==0)
            printf("%d\n",len/(len-fail[len-1]-1));
        else
            printf("1\n");
    }
    return 0;
}
