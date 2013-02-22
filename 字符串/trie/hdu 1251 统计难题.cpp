/*

��Ŀ��
    ѯ�ʹ���ǰ׺�ĵ�������

������
    ��trie���ϵ����������һ��num����¼ÿ�����ʵ���������

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
