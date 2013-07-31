/*

题目：
    给出n个病毒的特征，再给出m个网页的信息，输出这m个网页中分别有哪些病毒特征，
    并输出有多少个网页中毒

*/
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

char vir[202],str[10005];
bool use[505];
int n,m;
int head,tail;

struct trie
{
    int id;
    trie *fail,*next[128];
    trie()
    {
        memset(next,NULL,sizeof(next));
        id = 0;
        fail = NULL;
    }
}*q[1000005];   //此处的数组要开足够大

void insert(trie *root,int num)     //trie树的建立
{
    int idex;
    for(int i=0;vir[i];i++)
    {
        idex = (int)vir[i];
        if(root->next[idex]==NULL)
            root->next[idex] = new trie();
        root = root->next[idex];
    }
    root->id = num;
}

void ac_build(trie *root)
{
    head = tail = 0;
    trie *temp,*p;
    root->fail = NULL;
    q[head++] = root;

    while(head!=tail)
    {
        temp = q[tail++];
        p = NULL;
        for(int i=0;i<128;i++)
        {
            if(temp->next[i]!=NULL)
            {
                p = temp->fail;
                while(p&&p->next[i]==NULL)
                    p = p->fail;
                if(p==NULL)
                    temp->next[i]->fail = root;
                else
                    temp->next[i]->fail = p->next[i];
                q[head++] = temp->next[i];
            }
        }
    }
}

int ac_run(trie *root)
{
    trie * temp;
    trie *p = root;
    int cnt = 0,idex;

    for(int i=0;str[i];i++)
    {
        idex = str[i];
        while(p->next[idex]==NULL&&p!=root)
            p = p->fail;
        p = p->next[idex];
        if(p==NULL)
            p = root;
        temp = p;
        while(temp!=root)
        {
            use[temp->id] = true;
            if(temp->id)
                cnt++;
            temp = temp->fail;
        }
    }

    return cnt;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    scanf("%d ",&n);
    trie *root = new trie();
    for(int i=1;i<=n;i++)
    {
        gets(vir);
        insert(root,i);
    }
    ac_build(root);

    scanf("%d ",&m);
    int temp,cnt = 0;
    for(int i=1;i<=m;i++)
    {
        gets(str);
        memset(use,false,sizeof(use));
        temp = ac_run(root);
        if(temp)
        {
            cnt++;
            printf("web %d:",i);
            for(int i=1;i<=n;i++)
                if(use[i])
                    printf(" %d",i);
            printf("\n");
        }
    }
    printf("total: %d\n",cnt);

    return 0;
}
