#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int kind = 26;

struct node{
    node *p[kind];
    char s[22];
    bool ok;
    node(){
        memset(p,NULL,sizeof(p));
        ok = false;
    }
};

char a[22],b[22];
char str[105];
char ans[101][22];

void insert(node *r){
    int id;
    for(int i=0;a[i];i++){
        id = a[i]-'a';
        if(r->p[id]==NULL)
            r->p[id] = new node();
        r = r->p[id];
    }
    r->ok = true;
    strcpy(r->s,b);
}

bool ask(node *r,char *s){
    for(int i=0;s[i];i++){
        int id = s[i]-'a';
        if(id<0||id>=26)
            return false;
        if(r->p[id]==NULL)
            return false;
        r = r->p[id];
    }
    if(r->ok==false)
        return false;
    strcpy(b,r->s);
    return true;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase,n,m;
    RD(ncase);
    rep1(qqq,ncase){
        node *r = new node();
        RD2(n,m);
        rep(i,m){
            scanf("%s%s",a,b);
            insert(r);
        }

        getchar();
        gets(str);
        int len = strlen(str);
        int top = 0,ok = 0;
        rep(i,len){
            if(str[i]>='a'&&str[i]<='z')
                ans[top][ok++] = str[i];
            else{
                if(ok)
                    ans[top++][ok] = '\0';
                ok = 0;
                ans[top][0] = str[i];
                ans[top++][1] = '\0';
            }
        }
        if(ok)
            ans[top++][ok] = '\0';

        /*
        puts("------------------");
        puts(str);
        rep(i,top)
            cout<<ans[i];
        cout<<endl;
        */
        rep(i,n-1)
            rep(j,top)
                if(ask(r,ans[j]))
                    strcpy(ans[j],b);

        printf("Case #%d: ",qqq);
        rep(i,top)
            printf("%s",ans[i]);
        puts("");
    }

	return 0;
}
