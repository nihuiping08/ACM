/*

题目：
    询问公共前缀的单词总数

分析：
    在trie树上的数据域添加一个num，记录每个单词的总数即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 11;

char s[X];

struct node
{
    int num;
    node *p[26];
    node()
    {
        memset(p,NULL,sizeof(p));
        num = 0;
    }
}root;

void insert(node *r)
{
    int id;
    for(int i=0;s[i];i++)
    {
        id = s[i]-'a';
        if(r->p[id]==NULL)
            r->p[id] = new node();
        (r->p[id]->num)++;
        r = r->p[id];
    }
}

int query(node *r)
{
    int id;
    for(int i=0;s[i];i++)
    {
        id = s[i]-'a';
        if(r->p[id]==NULL)
            return 0;
        r = r->p[id];
    }
    return r->num;
}

int main()
{
    freopen("sum.in","r",stdin);
    node *r = &root;
    while(gets(s),s[0])
        insert(r);
    while(gets(s))
        printf("%d\n",query(r));
    return 0;
}
