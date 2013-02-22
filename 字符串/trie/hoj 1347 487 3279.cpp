/*

trie树建立，然后递归打印所有的电话号码

*/
#include <cstdio>
#include <cstring>
#define X 125
char s[X];
int n;
struct trie
{
    int id;
    trie *p[10];
    trie()
    {
        id = 0;
        memset(p,NULL,sizeof(p));
    }
}root;
int ma[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,-1,7,7,8,8,8,9,9,9,-1};
void insert(trie *r)
{
    int c;
    for(int i=0;s[i];i++)
    {
        c = -1;
        if(s[i]>='0'&&s[i]<='9')
            c = s[i]-'0';
        else if(s[i]>='A'&&s[i]<='Z')
            c = ma[s[i]-'A'];
        if(c==-1)
            continue;
        if(r->p[c]==NULL)
            r->p[c] = new trie();
        r = r->p[c];
    }
    r->id++;
}
bool flag;
void print(trie *r,char temp[],int cnt)
{
    for(int i=0;i<10;i++)
    {
        if(r->p[i]!=NULL)
        {
            temp[cnt] = '0'+i;
            print(r->p[i],temp,cnt+1);
        }
        if(r->id>1)
        {
            flag = true;
            for(int j=0;j<7;j++)
            {
                if(j==3)
                    printf("-");
                printf("%c",temp[j]);
            }
            printf(" %d\n",r->id);
            r->id = 0;
        }
        else
            r->id = 0;
    }
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        flag = false;
        trie *r = &root;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%s",s);
            insert(r);
        }
        char temp[10];
        print(r,temp,0);
        if(!flag)
            printf("No duplicates.\n");
        if(t)
            printf("\n");
    }
    return 0;
}
