/*

题目：
    奶牛们计划着去海滩上享受日光浴。为了避免皮肤被阳光灼伤，
    所有C(1 <= C <= 2500)头奶牛必须在出门之前在身上抹防晒霜。
    第i头奶牛适合的最小和最 大的SPF值分别为minSPF_i和maxSPF_i
    (1 <= minSPF_i <= 1,000; minSPF_i <= maxSPF_i <= 1,000)。
    如果某头奶牛涂的防晒霜的SPF值过小，那么阳光仍然能 把她的皮
    肤灼伤；如果防晒霜的SPF值过大，则会使日光浴与躺在屋里睡觉
    变得 几乎没有差别。为此，奶牛们准备了一大篮子防晒霜，一共
    L(1 <= L <= 2500)瓶。第i瓶 防晒霜的SPF值为SPF_i
    (1 <= SPF_i <= 1,000)。瓶子的大小也不一定相同，第i 瓶防晒霜
    可供cover_i头奶牛使用。当然，每头奶牛只能涂某一个瓶子里的防
    晒霜 ，而不能把若干个瓶里的混合着用。 请你计算一下，如果使
    用奶牛们准备的防晒霜，最多有多少奶牛能在不被灼 伤的前提下，
    享受到日光浴的效果？
    Input

    * 第1行: 2个用空格隔开的整数：C和L * 第2..C+1行: 第i+1行给
    出了适合第i头奶牛的SPF值的范围：minSPF_i以及 maxSPF_i * 第
    C+2..C+L+1行: 第i+C+1行为了第i瓶防晒霜的参数：SPF_i和
    cover_i，两个 数间用空格隔开。
    Output

    * 第1行: 输出1个整数，表示最多有多少头奶牛能享受到日光浴

分析：
    贪心，对max_spf进行升序排列，然后每次找到最小的spf满足条件

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int X = 2505;

int m,n;

struct cow{
    int min,max;
    friend bool operator < (cow a,cow b){
        return a.max<b.max||(a.max==b.max&&a.min<b.min);
    }
}c[X];

struct spf{
    int num,sp;
    friend bool operator < (spf a,spf b){
        return a.sp<b.sp;
    }
}s[X];

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>m>>n){
        for(int i=0;i<m;i++)
            scanf("%d%d",&c[i].min,&c[i].max);
        for(int i=0;i<n;i++)
            scanf("%d%d",&s[i].sp,&s[i].num);
        sort(c,c+m);
        sort(s,s+n);
        int ans = 0;
        for(int i=0;i<m;i++){
            int ok = 0;
            for(int j=0;j<n;j++){
                if(s[j].num&&s[j].sp>=c[i].min&&s[j].sp<=c[i].max){
                    ok = 1;
                    s[j].num --;
                    break;
                }
            }
            ans += ok;
        }
        cout<<ans<<endl;
    }
    return 0;
}
