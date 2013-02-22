/*

题目：
    n个人在排队，现给出了这n个人的高度，两个人之间若没有比他们任意一个高的话，
    那么这两个人可以互相看见，现在问队伍中有多少人是可以相互看见的

分析：
    利用非上升的单调队列来记录当前队伍中的高度变化，当新加入队列的元素大于当前
    队伍头部中的高度时，队伍头部出队，直到队伍为空或者有人比新加入的高度更高（
    或相等）时为止，然后在相等时的处理是每次往前面找有多少个跟他一样高度的人，然
    后直到找到一个比他高的人或者已到达队伍末尾为止

*/
#include <cstdio>
#include <cstring>

const int X = 500001;

int a[X],n;
int q[X];

int main()
{
    freopen("sum.in","r",stdin);
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        int top = 1;
        q[0] = a[0];
        long long ans = 0;
        for(int i=1;i<n;i++)
        {
            while(top&&q[top-1]<a[i])
            {
                ans++;
                top--;
            }
            for(int j=top-1;j>=0;j--)
            {
                if(q[j]==a[i])
                    ans++;
                else
                {
                    ans++;
                    break;
                }
            }
            q[top] = a[i];
            top++;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
