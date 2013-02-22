#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define esp 1e-8
#define PI 3.1415926535897932
#define X 10005

int n,f;
double r[X];
double totalarea;

void binary()
{
	double right = totalarea/f;
	double left = 0;
	double mid;
	while(right-left>esp)
	{
		mid = (left+right)/2;
		int cnt = 0;
		for(int i=0;i<n;i++)
			cnt += (int)(r[i]/mid);
		if(cnt>=f)
			left = mid;
		else
			right = mid;
	}
	printf("%.4lf\n",left*PI);
}

int main()
{
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        totalarea = 0;
        cin>>n>>f;
        f++;
        for(int i=0;i<n;i++)
        {
            scanf("%lf",&r[i]);
            r[i] *= r[i];
            totalarea += r[i];
        }
        binary();
    }
    return 0;
}
