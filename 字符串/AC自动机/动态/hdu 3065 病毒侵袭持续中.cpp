/*

题目：
    统计模式串拥有的病毒特征的数目


分析：
    由于内存不够，开128的数组MLE，由于病毒的特征只能是大写的字母，所以
    跑ac自动机时遇到非大写字母时直接指向根

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

struct node
{
    int id;
    node *fail,*next[26];
    node()
    {
        memset(next,NULL,sizeof(next));
        fail = NULL;
        id = 0;
    }
};

queue<node*> q;

int ans[1002],n,m;
char vir[1002][51];
char str[2000002];

void insert(node *root,char *s,int num)
{
    int idex;
    for(int i=0;s[i];i++)
    {
        idex = s[i]-'A';
        if(root->next[idex]==NULL)
            root->next[idex] = new node();
        root = root->next[idex];
    }
    root->id = num;
}

void ac_build(node *root)
{
    node *temp,*p;
    root->fail = NULL;
    q.push(root);
    while(q.size())
    {
        temp = q.front();
        q.pop();
        p = NULL;
        for(int i=0;i<26;i++)
        {
            if(temp->next[i])
            {
                p = temp->fail;
                while(p&&p->next[i]==NULL)
                    p = p->fail;
                if(!p)
                    temp->next[i]->fail = root;
                else
                    temp->next[i]->fail = p->next[i];
                q.push(temp->next[i]);
            }
        }
    }
}

void ac_run(node *root)
{
    node *p = root;
    node *temp;
    int idex;
    for(int i=0;str[i];i++)
    {
        if(!isupper(str[i]))
        {
            p = root;
            continue;
        }
        idex = str[i]-'A';
        while(p->next[idex]==NULL&&p!=root)
            p = p->fail;
        p = p->next[idex];
        if(!p)
            p = root;
        temp = p;
        while(temp!=root)
        {
            ans[temp->id]++;
            temp = temp->fail;
        }
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(scanf("%d ",&n)!=EOF)
    {
        node *root = new node();
        for(int i=1;i<=n;i++)
        {
            gets(vir[i]);
            insert(root,vir[i],i);
        }
        gets(str);
        ac_build(root);
        memset(ans,0,sizeof(ans));
        ac_run(root);
        for(int i=1;i<=n;i++)
            if(ans[i])
                printf("%s: %d\n",vir[i],ans[i]);
    }

    return 0;
}
