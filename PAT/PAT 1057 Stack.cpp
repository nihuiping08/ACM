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
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>

/******** program ********************/

const int MAXN = 2e5+5;

int sta[MAXN],top;
int c[MAXN];

int lowbit(int x){ // 树状数组--位运算
    return x & -x;
}

void modify(int x,int val){ // 树状数组--更新
    while(x<MAXN){
        c[x] += val;
        x += lowbit(x);
    }
}

int ask(int x){ // 树状数组--查询
    int ans = 0;
    while(x>0){
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}

int binary(int Kth){ // 二分部分
    int l = 1 , r = MAXN-1;
    int ans = -1;
    while(l<=r){
        int mid = (l+r)/2;
        int t = ask(mid);
        if(t>=Kth){
            ans = mid;
            r = mid-1;
        }
        else
            l = mid+1;
    }
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    top = 0;
    int ncase;
    scanf("%d",&ncase);
    char op[15];
    int val;

    memset(c,0,sizeof(c));
    while(ncase--){
        scanf("%s",op);

        if(op[1]=='e'){         // PeekMedian
            if(top)
                printf("%d\n", binary( (top+1)/2 ) );
            else
                puts("Invalid");
        }else if(op[1]=='u'){   // Push
            scanf("%d",&val);
            sta[ ++top ] = val; // 进栈
            modify(val,1);
        }else{                  // Pop
            if(top){ // 栈中有元素，出栈
                printf("%d\n",sta[top]);
                modify(sta[top],-1);
                top --;
            }
            else
                puts("Invalid");
        }
    }

	return 0;
}
