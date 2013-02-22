/*

问题：
    排列1到n,现在给出输出的序列，若到达尾部返回头部，达到的元素要删除，
    比如输出的序列为2 3 5 7 9，在排列1 2 3 4 5中，表示开始先删除2，然后继续往后走3，到达
    5，因为已到达尾部，开始从头部往后走

分析：
    树状数组求第K小

*/
#include <cstdio>
#include <cstring>
#include <cmath>

const int X = 100005;
int c[X];
int step[X];
int nowpostion;
int forward;
int up = log(X-1) / log(2);

int lowbit(int x){
        return x & (-x);
}
void add(int x, int val){
    while(x<X){
        c[x] += val;
        x += lowbit(x);
    }
}
int sum(int x){
    int ret = 0;
    while(x>0){
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}
int findK(int k){
    int ans = 0, cnt = 0;
    for (int i = up; i >= 0; i--){
        ans += ( 1 << i );
        if ( ans >= X || cnt + c[ans] >= k )
            ans -= ( 1 << i );
        else
            cnt += c[ans];
    }
    return ans + 1;
}
int main(){
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int n;
    while ( scanf("%d", &n) == 1 && n){
        memset(c, 0, sizeof(int) * (n + 1));
        for (int i = 0; i < n; ++i){
            scanf("%d", step + i);
            add(i + 1, 1);
        }
        nowpostion = 0;
        forward = 0;
        for (int i = 0; i < n; ++i){
            if ( i ) printf(" ");
            forward = sum(nowpostion);
            int k = (forward + step[i] - 1) % (n - i) + 1;
            //printf("%d ", k);
            nowpostion = findK(k);
            printf("%d", nowpostion);
            add(nowpostion, -1);
        }
        printf("\n");
    }
    return 0;
}
