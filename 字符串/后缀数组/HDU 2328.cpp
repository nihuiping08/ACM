#include <set>
#include <map>
#include <list>
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
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>
#define PQ priority_queue
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)
#define Clear(x) memset(x,0,sizeof(x))
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 8e5+5;

char s[MAXN];
int wa[MAXN],wb[MAXN],wx[MAXN],wy[MAXN];
int r[MAXN],sa[MAXN],Height[MAXN],Rank[MAXN];
bool use[1004];
int loc[MAXN],m;

bool cmp(int *r,int a,int b,int d){
    return r[a]==r[b]&&r[a+d]==r[b+d];
}

void da(int *r,int *sa,int n,int m){
    int *x = wa , *y = wb;

    // 基数排序
    rep(i,m)
        wx[i] = 0;
    rep(i,n)
        wx[ x[i] = r[i] ] ++;
    rep1(i,m-1)
        wx[i] += wx[i-1];
    for(int i=n-1;i>=0;i--)
        sa[ --wx[x[i]] ] = i;

    int p = 1;
    for(int j = 1;p<n;j<<=1,m=p){
        // 第二关键字排序
        p = 0;
        for(int i=n-j;i<n;i++)
            y[p++] = i;
        rep(i,n)
            if(sa[i]>=j)
                y[p++] = sa[i]-j;

        // 第一关键字排序
        rep(i,n)
            wy[i] = x[y[i]];
        rep(i,m)
            wx[i] = 0;
        rep(i,n)
            wx[ wy[i] ] ++;
        rep1(i,m-1)
            wx[i] += wx[i-1];
        for(int i=n-1;i>=0;i--)
            sa[ --wx[ wy[i] ] ] = y[i];

        swap(x,y);
        p = 1;
        x[sa[0]] = 0;
        rep1(i,n-1)
            x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}

void calHeight(int *r,int *sa,int n){
    rep1(i,n)
        Rank[sa[i]] = i;
    for(int i=0,k=0,j;i<n;Height[Rank[i++]]=k)
        for(k?k--:0,j=sa[Rank[i]-1];r[i+k]==r[j+k];k++);
}

/***************** 单调队列的做法 *****************/


int q[MAXN];

int pq(int top){ // 单调队列
    int ans = 0;

    int head = 0 , tail = 0;
    int pos = 0;

    memset(use,false,sizeof(use));
    for(int i=2;i<top;i++){
        while(  )
    }


    int t = 0;
    for(int i=pos;i<pos+ans;i++)
        s[t++] = char(r[i]+'a'-1);
    s[t] = '\0';
    return ans;
}

/***************** 二分的做法 *********************/
bool ok(int mid,int top){
    int tot = 0;
    memset(use,false,sizeof(use));
    for(int i=2;i<top;i++){

        if( Height[i]<mid ){
            memset(use,false,sizeof(use));
            tot = 0;
        }else{
            if( !use[ loc[sa[i]] ] ){
                use[ loc[sa[i]] ] = true;
                tot ++;
            }
            if( !use[ loc[sa[i-1]] ] ){
                use[ loc[sa[i-1]] ] = true;
                tot ++;
            }
            if(tot==m){
                int t = 0;
                int pos = sa[i];
                for(int j=pos;j<pos+mid;j++)
                    s[t++] = char(r[j]+'a'-1);
                s[t] = '\0';
                return true;
            }
        }
    }
    return false;
}

int bin(int top){ // 二分
    int ans = 0;
    int l = 0 , r = 4000;
    while(l<=r){
        int mid = (l+r)>>1;
        if(ok(mid,top)){
            l = mid+1;
            ans = mid;
        }else
            r = mid-1;
    }

    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>m,m){
        int top = 0;
        rep(i,m){
            scanf("%s",s+top);
            top = strlen(s);
            s[top++] = 'a'+27;
        }
        s[top-1] = 'a'-1;

        int t = 0;
        rep(i,top){
            r[i] = s[i]-'a'+1;
            if(r[i]==28)
                loc[i] = ++ t;
            else
                loc[i] = t;
        }
        /*
        rep(i,top)
            cout<<s[i]<<" ";
        cout<<endl;
        rep(i,top)
            cout<<loc[i]<<" ";
        cout<<endl;
        */

        da(r,sa,top,29);
        calHeight(r,sa,top-1);


        int ans = pq(top);
        if(ans)
            puts(s);
        else
            puts("IDENTITY LOST");
        /*
        int tmp = bin(top);
        if(tmp)
            puts(s);
        else
            puts("IDENTITY LOST");
        */
        //cout<<ans<<" "<<tmp<<endl;
    }

	return 0;
}
