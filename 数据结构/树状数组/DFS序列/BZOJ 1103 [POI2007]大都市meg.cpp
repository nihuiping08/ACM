/*

题目：
    给出一棵树，起初每条边的边权为1，现在有以下两种操作：
    1.W a，询问从1到节点a的所有边权
    2.A a b，表示边a,b的边权置为0
    现在，需要输出每个询问的答案

分析：
    树状数组维护DFS序列。
    我们可以对于每个节点记录两个时间戳，一个表示进入该点的时间戳，另一个表示
    退出该点的时间戳。
    每当我们进入该点的时候，在树状数组中加1，表示该边的进入。
    每当我们退出该点的时候，在树状数组中减1，表示消除该边对以后统计的影响。
    所以我们可以把问题的点转换为区间。
    当修改的时候，我们需要把一个顶点的值减1，表示该边权为0，由于这里多减了，
    所以为了消除对以后的询问的影响，所以我们需要在退出的时间戳中加1

*/
#include <cstdio>
#include <cstring>

const int MAXN = 250005;
const int MAXM = 500005;

int c[MAXM],a[MAXN],b[MAXN],po[MAXN],tol,n;
bool use[MAXN];
char s[8];

struct node{
    int y,next;
}edge[MAXM];

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

int Int(){
    int ans = 0;
    for(int i=0;s[i];i++)
        ans = ans*10+s[i]-'0';
    return ans;
}

void modify(int x,int val){
    while(x<=n){
        c[x] += val;
        x = (x|(x-1))+1;
    }
}

int ask(int x){
    int ans = 0;
    while(x>0){
        ans += c[x];
        x = x&(x-1);
    }
    return ans;
}

void dfs(int x){
    use[x] = true;
    a[x] = ++tol;
    modify(tol,1);
    for(int i=po[x];i;i=edge[i].next)
        if(use[edge[i].y]^1)
            dfs(edge[i].y);
    b[x] = ++tol;
    modify(tol,-1);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y;
    scanf("%s",s);
    n = Int();

    for(int i=1;i<n;i++){
        scanf("%s",s);
        x = Int();
        scanf("%s",s);
        y = Int();

        add(x,y);
        add(y,x);
    }

    n <<= 1;
    tol = 0;
    dfs(1);

    scanf("%s",s);
    int m = Int();

    char op[2];

    while(m){
        scanf("%s%s",op,s);
        x = Int();
        if(op[0]!='A'){
            printf("%d\n",ask(a[x])-1);
            m --;
        }
        else{
            scanf("%s",s);
            y = Int();
            modify(a[y],-1);
            modify(b[y],1);
        }
    }

	return 0;
}
