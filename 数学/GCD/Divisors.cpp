#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

const int X = 432;
#define debug puts("here");

long long p[X],n,m,top;
bool use[18000];
long long qq[X][100];

void init()
{
    top = 0;
	memset(use,false,sizeof(use));
	use[1] = true;
	p[top++] = 2;
	for(int i=3;i<X;i+=2)
		if(!use[i])
		{
			p[top++] = i;
			for(int j=i*i;j<X;j+=i)
				use[j] = true;
		}
}

void solve()
{
    memset(qq,0,sizeof(qq));
    int temp;

    for(int k=2;k<X;k++)
        for(int j=1;j<=k;j++)
        {
            temp = j;
            for(int i=0;i<top&&p[i]<=temp;i++)
                while(temp%p[i]==0)
                {
                    qq[k][i]++;
                    temp /= p[i];
                }
        }
}

int main()
{
    freopen("sum.in","r",stdin);
    init();
    solve();
    while(scanf("%lld%lld",&n,&m)!=EOF)
    {
        if(n==m)
        {
            puts("1");
            continue;
        }

        long long ans = 1;

        for(int i=0;i<top&&p[i]<=n;i++)
            ans *= (qq[n][i]-qq[m][i]-qq[n-m][i]+1);

        printf("%lld\n",ans);
    }
    return 0;
}
