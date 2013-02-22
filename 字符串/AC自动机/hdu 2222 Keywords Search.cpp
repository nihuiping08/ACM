#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int kind = 26;

struct node
{
    node *fail;         ///failָ��
    node *next[kind];   ///trie��26���ӽڵ�
    int count;          ///�Ƿ�Ϊ�õ��ʵ����һ���ڵ�
    node()              ///���캯����ʼ��
    {
        fail = NULL;
        count = 0;
        memset(next,NULL,sizeof(next));
    }
}*q[500005];             ///���У���������BFS����ʧ��ָ��

char s[51];       ///����ĵ���
char str[1000005];      ///ģʽ��
int head,tail;          ///���еĶ��ף���β

void insert(node *root)
{
    int idex;
    for(int i=0;s[i];i++)
    {
        idex = s[i]-'a';
        if(root->next[idex]==NULL)
            root->next[idex] = new node();
        root = root->next[idex];
    }
    root->count++;
}

void ac_build(node *root)
{
    root->fail = NULL;
    q[head++] = root;
    node *temp,*p;
    while(head!=tail)
    {
        temp = q[tail++];
        p = NULL;
        for(int i=0;i<26;i++)
        {
            if(temp->next[i]!=NULL)
            {
                p  = temp->fail;
                while(p&&p->next[i]==NULL)
                    p = p->fail;
                if(!p)
                    temp->next[i]->fail = root;
                else
                    temp->next[i]->fail = p->next[i];
                q[head++] = temp->next[i];
            }
        }
    }
}

void ac_run(node *root)
{
    int cnt = 0,idex;
    node *p = root;
    node *temp;
    for(int i=0;str[i];i++)
    {
        idex = str[i]-'a';
        while(p->next[idex]==NULL&&p!=root)
            p = p->fail;
        p = p->next[idex];
        if(p==NULL)
            p = root;
        temp = p;
        while(temp!=root&&temp->count!=-1)
        {
            cnt += temp->count;
            temp->count = -1;
            temp = temp->fail;
        }
    }
    cout<<cnt<<endl;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int n,t;
    cin>>t;
    while(t--)
    {
        head = tail = 0;
        scanf("%d ",&n);
        node *root = new node();
        for(int i=0;i<n;i++)
        {
            gets(s);
            insert(root);
        }
        ac_build(root);
        gets(str);
        ac_run(root);
    }

    return 0;
}
