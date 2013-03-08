/*

题目：
    你拥有n个士兵，然后需要分成 攻击木塔 和 攻击石塔 两个兵种，并且
    一旦分好之后不能够再次划分。每个木兵或者石兵每轮都只能够对木塔或者
    石塔造成一点伤害。每个木塔或者石塔的生命力是hp。现在有num_stone
    个石塔和num_woden个木塔。每轮过后，剩下的每个石塔或者每个木塔都会
    杀死per个石兵或者木兵。每轮造成的伤害会累积到下一轮。
    现在问如何安排士兵分组，使得攻击的轮数最少。
分析：
    如何划分士兵具有单调性。二分出划分木兵的数目，然后分别判断是否可行。
    可行的话，根据木兵以及石兵的攻击轮数来判断二分界限。

*/
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

class EnemyTowers{
public:

    int ok(int n,int hp,int num,int per){
        int ans = 0;
        int sum = hp*num;
        while(sum>0){
            ans ++;
            if(n<=0)
                return -1;
            sum -= n;
            if(sum<=0)
                return ans;
            n -= (sum+hp-1)/hp*per;
        }
        return ans;
    }

    int solve(int n, int hp, int per, int woden, int stone){
        int l = 0,r = n;
        int ans = 1000000005;
        while(l<=r){
            int mid = (l+r)>>1;
            int x = mid;
            int y = n-mid;
            int tmp = ok(x,hp,woden,per); // 算出木兵的轮数
            int ret = ok(y,hp,stone,per); // 算出石兵的轮数
            if(ret==-1&&tmp==-1) // 都不可行
                return 1000000005;
            if(tmp==-1) // 木兵不够
                l = mid+1;
            else if(ret==-1) // 石兵不够
                r = mid-1;
            else{
                ans = min( ans,max(tmp,ret) );
                if(tmp>ret) // 木兵的轮数多
                    l = mid+1;
                else
                    r = mid-1;
            }
        }
        return ans;
    }

    int attack(int n, int hp, int per, int woden, int stone){
        int ans = solve(n,hp,per,woden,stone);
        if(ans==1000000005)
            return -1;
        return ans;
    }
};
