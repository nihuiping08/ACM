/*

题目：
    两个快递员要在方格上送外卖，方格矩阵中有楼、饭店以及空地，每块空
    地有个高度。
    任意相邻的格子都能够走到该楼，花费为2。
    任意相邻的空地如果高度差为0，费用为1，高度差为2的话，费用为3，否则
    不能够走。
    饭店相当于楼。
    问两个送外卖的人的需要最小的时间花费。

分析：
    BFS预处理出要送外卖的每个位置的单次时间花费。然后二进制枚举出每个
    地方分别属于哪个人送，然后再取两者中最大的最小为答案


*/
#include <queue>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 55;

int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

struct node{
    int x,y,step;
    node(){}
    node(int _x,int _y,int _step):x(_x),y(_y),step(_step){}
};

class PizzaDelivery{
public:
    int n,m,sx,sy;
    int use[MAXN][MAXN];
    vector<int> a;
    int dp[1500000];

    int cal(char x,char y){
        if(x>='0'&&x<='9'&&y>='0'&&y<='9'){
            int h = max(x-y,y-x);
            if(h>1) return -1;
            return x==y?1:3;
        }
        return 2;
    }

    void init(vector<string> map){
        a.clear();
        n = map.size();
        m = map[0].size();
        rep(i,n)
            rep(j,m)
                if(map[i][j]=='X'){
                    sx = i,sy = j;
                    return;
                }
    }

    bool out(int x,int y){
        return x<0||y<0||x>=n||y>=m;
    }

    void BFS(vector<string> map){
        memset(use,0x3f,sizeof(use));
        queue<node> q;
        q.push(node(sx,sy,0));
        while(q.size()){
            node pre = q.front();
            q.pop();
            int cx = pre.x;
            int cy = pre.y;
            if(use[cx][cy]<=pre.step)
                continue;
            use[cx][cy] = pre.step;
            rep(d,4){
                int x = cx+dx[d];
                int y = cy+dy[d];
                if(out(x,y))
                    continue;
                int tmp = cal(map[x][y],map[cx][cy]);
                if(tmp==-1)
                    continue;
                q.push(node(x,y,pre.step+tmp));
            }
        }
    }

    int solve(vector <string> map){
        int sum = 0;
        rep(i,n)
            rep(j,m){
                if(map[i][j]=='$'){
                    if(use[i][j]==use[54][54])
                        return -1;
                    a.pb(use[i][j]);
                    sum += use[i][j];
                }
            }

        sort(a.begin(),a.end());
        reverse(a.begin(),a.end());
        int len = a.size();
        rep(i,(1<<len)){
            bool ok = true;
            rep(j,len)
                if( i&(1<<j) ){
                    dp[i] += ok?a[j]:a[j]*2;
                    ok = false;
                }
        }
        int ans = 1000000000;
        rep(i,(1<<len))
            ans = min(ans,max(dp[i],dp[(1<<len)-1-i]));
        return ans;
    }

    int deliverAll(vector <string> map){
        init(map);
        BFS(map);
        return solve(map);
    }
};
