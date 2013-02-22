/*

题目：
    简单的询问是否是某个单词是另一个单词的前缀

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 1002;
#define debug cout<<"here"<<endl;

char s[X];

struct node
{
    bool end;
    bool path;
    node *p[3];
    node()
    {
        memset(p,NULL,sizeof(p));
        path = end = false;
    }
}root;

bool insert(node *r,char *s)
{
    int id;
    for(int i=0;s[i];i++)
    {
        id = s[i]-'0';
        if(r->p[id]==NULL)
            r->p[id] = new node();
        else if(r->p[id]->end)
            return false;
        r->path = true;
        r = r->p[id];
    }
    if(r->path)
    {
        //debug;
        return false;
    }
    r->end = r->path = true;
    return true;
}

int main()
{
    freopen("sum.in","r",stdin);
    int ncase = 0;
    while(scanf("%s",s)!=EOF)
    {
        bool ok = true;
        node *r;
        r = new node();
        while(strcmp(s,"9")!=0)
        {
            if(ok&&!insert(r,s))
                ok = false;
            scanf("%s",s);
        }
        if(ok)
            printf("Set %d is immediately decodable\n",++ncase);
        else
            printf("Set %d is not immediately decodable\n",++ncase);
    }
    return 0;
}
