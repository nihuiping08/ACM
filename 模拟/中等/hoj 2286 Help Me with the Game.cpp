#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

#define debug cout<<"dsa"<<endl;

const int X = 9;

struct node
{
    int a,b,c;
};

vector<vector<node> > q(12);

bool cmpw(node a,node b)
{
    return a.c>b.c||(a.c==b.c&&a.b<b.b);
}

bool cmpb(node a,node b)
{
    return a.c<b.c||(a.c==b.c&&a.b<b.b);
}

int use[150];
node p;
char s[100];

void init()
{
    memset(use,-1,sizeof(use));
    use[int('K')] = 0;
    use[int('Q')] = 1;
    use[int('R')] = 2;
    use[int('B')] = 3;
    use[int('N')] = 4;
    use[int('P')] = 5;

    use[int('k')] = 6;
    use[int('q')] = 7;
    use[int('r')] = 8;
    use[int('b')] = 9;
    use[int('n')] = 10;
    use[int('p')] = 11;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);

    int id;
    init();
    char ch;
    for(int y=1;y<9;y++)
    {
        gets(s);
        for(int x=1;x<9;x++)
        {
            getchar();
            getchar();
            scanf("%c",&ch);
            getchar();
            if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
            {
                id = (int)ch;
                if(!isupper(ch))
                    p.a = (int)(ch-'a'+'A');
                else
                    p.a = (int)ch;
                id = use[id];
                p.b = x;
                p.c = 9-y;
                q[id].push_back(p);
            }
        }
        gets(s);
    }
    for(int i=0;i<6;i++)
        sort(q[i].begin(),q[i].end(),cmpb);
    for(int i=6;i<11;i++)
        sort(q[i].begin(),q[i].end(),cmpw);
    bool ok = false;
    printf("White: ");
    for(int i=0;i<12;i++)
    {
        if(i==6)
        {
            printf("\nBlack: ");
            ok = false;
        }
        int len = q[i].size();
        for(int j=0;j<len;j++)
        {
            ok?printf(","):ok = true;
            if(q[i][j].a==(int)'p'||q[i][j].a==(int)'P')
                cout<<(char)(q[i][j].b+'a'-1)<<q[i][j].c;
            else
                cout<<(char)q[i][j].a<<(char)(q[i][j].b+'a'-1)<<q[i][j].c;
        }
    }
    cout<<endl;
    return 0;
}
