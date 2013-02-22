#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define X 1000010
#define esp 1e-8

struct point
{
	double x,y;
	friend bool operator < (point a,point b)
    {
        return a.y<b.y||(abs(a.y-b.y)<esp&&a.x<b.x);
    }
}p[X],res[X];

point p0,p1,p2;

double Area()
{
	return ((p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y))/2;
}

double dot(point o,point b,point a)
{
    return (a.x-o.x)*(b.x-o.x)+(a.y-o.y)*(b.y-o.y);
}

double dis(double x,double y)
{
    return x*x+y*y;
}
double dis(point a,point b)
{
    return dis(a.x-b.x,a.y-b.y);
}

int top,n;

int dcmp(double x)  //ÅÐ¶ÏÊÇ·ñÎª0
{
    if(abs(x)<esp)
        return 0;
    return x<0?-1:1;
}

int det(double x1,double y1,double x2,double y2)
{
    return dcmp(x1*y2-x2*y1);
}

bool del(int top,int i)
{
    if(det(res[top].x-res[top-1].x,res[top].y-res[top-1].y,p[i].x-res[top].x,p[i].y-res[top].y)<=0)
        return true;
    return false;
}

void graham()
{
    sort(p,p+n);
    top = 1;
    res[0] = p[0];
    res[1] = p[1];
    for(int i=2;i<n;i++)
    {
        while(top&&del(top,i))
            top--;
        res[++top] = p[i];
    }
    int mint = top;
    res[++top] = p[n-2];
    for(int i=n-3;i>=0;i--)
    {
        while(top!=mint&&del(top,i))
            --top;
        res[++top] = p[i];
    }
}

int main()
{
	freopen("sum.in","r",stdin);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;

		cin>>p0.x>>p0.y;
		p[0].x = p0.x;
		p[0].y = p0.y;

		cin>>p1.x>>p1.y;
		p[1].x = p1.x;
		p[1].y = p1.y;

		double area,tarea = 0,sum_x = 0,sum_y = 0;

		for(int i=2;i<n;i++)
		{
			scanf("%lf%lf",&p2.x,&p2.y);
			p[i].x = p2.x;
			p[i].y = p2.y;
			area = Area();
			tarea += area;
			sum_x += (p0.x+p1.x+p2.x)*area;
			sum_y += (p0.y+p1.y+p2.y)*area;
			p1 = p2;
		}
		if(abs(tarea)<esp)
        {
		    puts("0");
		    continue;
        }
		point qq;

		qq.x = sum_x/tarea/3;
		qq.y = sum_y/tarea/3;
		int ans = 0;
		double a,b;

		graham();

		for(int i=1;i<=top;i++)
        {
            a = dot(res[i-1],qq,res[i]);
            b = dot(res[i],qq,res[i-1]);
            if(dcmp(a)>0&&dcmp(b)>0)
                ans++;
        }
        cout<<ans<<endl;
	}

	return 0;
}
