/*

題目：求dp[n]。dp[i] = min{ dp[j]+ [(sigma(c_q)+i-j-1-len)^2] }
分析：
    由於n太大了，O(n^2)會TLE。
    很顯然，該目標轉移方程函數為 1D1D型的DP決策問題。我們可以用單調隊列
    來進行優化。

    假設有兩個決策點j,k。有
    dp[k]+[(sigma(c_q)+i-k-1-len)^2]<dp[j]+[(sigma(c_q)+i-j-1-len)^2]
    我們令
    sum[i]為前驅和
    A[i] = sum[i]+i
    B[i] = sum[i]+i+1+len
    則有
    dp[k]+(A[i]-A[k])^2 < dp[j]+(A[i]-A[j])^2
    我們可以繼續化簡，有：
    dp[k]+B[k]*B[k] - (dp[j]+B[j]*B[j]) < 2*A[i]*(B[k]-B[j])
    很顯然，當k>j時，B[k]>B[j]。即有上述不等式成立。

    所以我們使用單調隊列進行優化時：
    隊首元素的判斷：是否需要出隊。
    隊尾元素的判斷：是否斜率更優。

*/
/*

別人的題解：

DP方程不难想：
DP[I]=MIN(DP[J]+(SUM[I]-SUM[J]+I-J-1-L)^2) ,J<I
其中DP[I]表示处理到第I个玩具时最少的费用。



直接来显然TLE，一维方程一般用斜率优化。


先化简下方程：
令F[I]=SUM[I]+I,C=1+L,则化为
DP[I]=MIN(DP[J]+(F[I]-F[J]-C)^2)





以下是用这方法的步骤：
1.证明较优决策点对后续状态影响的持续性
假设在状态I处,有两个决策点J,K(J<K),且决策K比决策J好,即
   DP[K]+(F[I]-F[K]-C)^2<=DP[J]+(F[I]-F[J]-C)^2
则,对于状态I之后的某状态T,  F[T]=F[I]+V
要证
DP[K]+(F[T]-F[K]-C)^2<=DP[J]+(F[T]-F[J]-C)^2
只需证
DP[K]+(F[I]+V-F[K]-C)^2<=DP[J]+(F[I]+V-F[J]-C)^2
只需证
DP[K]+(F[I]-F[K]-C)^2+2*(F[I]-F[K]-C)*V+V^2 <=
    DP[J]+(F[I]-F[J]-C)^2+2*(F[I]-F[J]-C)*V+V^2

联系假设只需要证:
2*(F[I]-F[K]-C)*V<=2*(F[I]-F[J]-C)*V
即证:
F[K]>=F[J]
F[I]显然为增函数,且J<K,所以上式得证.





2.求斜率方程:一般化为左边是J，K，右边是I的形式
由DP[K]+(F[I]-F[K]-C)^2<=DP[J]+(F[I]-F[J]-C)^2
展开得:
DP[K]+F[I]^2-2*F[I]*(F[K]+C)+(F[K]+C)^2<=DP[J]+F[I]^2-2*F[I]*(F[J]+C)+(F[J]+C)^2
即:
DP[K]+(F[K]+C)^2-DP[J]-(F[J]+C)^2<=2*F[I]*(F[K]-F[J])
即
(DP[K]+(F[K]+C)^2-DP[J]-(F[J]+C)^2)/(2*(F[K]-F[J]))<=F[I]
令
G(K,J)=DP[K]+(F[K]+C)^2-DP[J]-(F[J]+C)^2
S(K,J)=2*(F[K]-F[J])
X(K,J)=G(K,J)/S(K,J)
所以斜率方程为X(K,J)<=F[I]




3.规定队列的维护规则
队首维护:
    假设A,B(A<B)是队首元素,若X(B,A)<=F[I],则B比A好,删除A,否则不需维护.

队尾维护:
    假设A,B,C(A<B<C)是队尾元素
    a.若X(B,A)<=F[I],且X(C,B)<=F[I],则C比B好,B比A好
    b.若X(B,A)<=F[I],且X(C,B)>F[I],则B比C好,B比A好,B为极大值
    c.若X(B,A)>F[I],A比B好
    a,c情况直接删掉B,b情况保留.b情况可改为X(B,A)<X(C,B)




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
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int MAXN = 50005;
const ll INF = 1e15;

ll A[MAXN],B[MAXN],sum[MAXN],dp[MAXN];
int q[MAXN],n,len;

ll G(int k,int j){
    return dp[k]+B[k]*B[k]-dp[j]-B[j]*B[j];
}

ll S(int k,int j){
    return 2*(B[k]-B[j]);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,len)){
        int x;
        rep1(i,n){
            RD(x);
            sum[i] = sum[i-1]+x;
        }

        len ++;
        rep(i,n+1){
            A[i] = sum[i]+i;
            B[i] = A[i]+len; // B[0] = len+1
        }

        dp[0] = 0;
        int H = 0,T = 0;
        q[++T] = 0;

        rep1(i,n){
            while(H<T && G(q[H+1],q[H])<=S(q[H+1],q[H])*A[i])
                H ++;
            int j = q[H];
            dp[i] = dp[j]+(A[i]-B[j])*(A[i]-B[j]);
            while(H<T && G(q[T],q[T-1])*S(i,q[T])>=G(i,q[T])*S(q[T],q[T-1]) )
                T --;
            q[++T] = i;
        }
        cout<<dp[n]<<endl;
    }

	return 0;
}
