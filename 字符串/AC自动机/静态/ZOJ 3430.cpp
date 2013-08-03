/*

给出base64的编码，问在原码中模式串出现的次数

ac自动机简单题
转换编码后，跟这个HDU 3065病毒侵袭持续中一样

*/
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

const int X = 5005;
const int MAXN = 50010;
const int kind = 256;

int s[MAXN];
char str[MAXN];
map<char,int> ma;
bool use[X];

char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
/*
struct base64{

    unsigned char in[3];
    unsigned char out[4];

    void encodeblock(int len) {
        out[0] = cb64[ in[0] >> 2 ];
        out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
        out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
        out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
    }

    void encode(){
        int tot = 0;
        for(int i=0;s[i];){

            int j = 0;
            while(j<3&&s[i])
                in[j++] = s[i++];
            in[j] = '\0';

            cout<<j<<" "<<in<<endl;

            encodeblock(j);
            rep(k,4)
                str[tot++] = out[k];
        }
        cout<<tot<<endl;
        str[tot] = '\0';
    }
}base;
*/
struct AC{
    int ch[MAXN][kind],fail[MAXN],last[MAXN];
    int ed[MAXN],val[MAXN],tot;

    void set(int x){
        Clear(ch[x]);
        ed[x] = last[x] = fail[x] = val[x] = 0;
    }

    void init(){
        set(0);
        tot = 0;
    }

    int newNode(){
        set(++ tot);
        return tot;
    }


    void insert(int len,int id){
        int r = 0;
        rep(i,len){
            int c = s[i];
            if(ch[r][c]==0)
                ch[r][c] = newNode();
            r = ch[r][c];
        }
        val[r] ++;
        ed[r] = id;
    }

    void build(){
        queue<int> q;
        rep(c,kind){
            int x = ch[0][c];
            if(x) q.push(x);
        }
        while(!q.empty()){
            int r = q.front();
            q.pop();
            rep(c,kind){
                int x = ch[r][c];
                if(!x){
                    ch[r][c] = ch[ fail[r] ][c];
                    continue;
                }
                q.push(x);
                int y = fail[r];
                while( y && ch[y][c]==0 )
                    y = fail[y];
                fail[x] = ch[y][c];
                last[x] = ed[ fail[x] ]?fail[x]:last[ fail[x] ];
            }
        }
    }

    void run(int len){
        int r = 0;

        int ans = 0;

        rep(i,len){
            int c = s[i];
            r = ch[r][c];

            int x = 0;
            if(ed[r])
                x = r;
            else if( last[r] )
                x = last[r];

            while(x){
                ans += val[x]*(!use[ed[x]]);
                use[ed[x]] = 1;
                x = last[x];
            }
        }
        printf("%d\n",ans);
    }
}ac;

void init(){
    rep(i,64)
        ma[ cb64[i] ] = i;
}

int bit[MAXN*10];

int encode(){
    int top = 0;
    int a[10];

    for(int i=0;str[i];i++){
        if(str[i]!='='){
            int x = ma[ str[i] ];
            for(int j=5;j>=0;j--){
                a[j] = x & 1;
                x >>= 1;
            }
            rep(j,6)
                bit[top++] = a[j];
        }else
            top -= 2;
    }

    /*
    cout<<top<<endl;
    for(int i=0;i<top;){
        for(int j=0;j<8;j++)
            cout<<bit[i++];
        cout<<"  ";
    }
    cout<<endl;
    */

    int x = 0;
    int tot = 0;
    for(int i=0;i<top;){
        x = 0;
        for(int j=0;j<8;j++)
            x = x<<1 | bit[i++];
        s[tot++] = x;
        //cout<<x<<" ";
    }
    //cout<<endl;
    //cout<<"length = "<<tot<<endl;
    return tot;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    init();
    int n,m;
    while(cin>>n){
        ac.init();

        rep1(i,n){
            scanf("%s",str);
            int t = encode();
            //cout<<"insert = "<<s<<" "<<strlen(s)<<endl;
            ac.insert(t,i);
        }

        ac.build();

        RD(m);
        rep1(i,m){
            memset(use,false,sizeof(use));
            scanf("%s",str);
            int t = encode();
            //cout<<"aks = "<<s<<" "<<strlen(s)<<endl;
            ac.run(t);
        }
        puts("");
    }

	return 0;
}
