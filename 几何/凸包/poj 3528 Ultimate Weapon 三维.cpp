#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define esp 1e-7
#define X 505

struct pt
{
    double x,y,z;
    pt()
    {}
    pt(double _x,double _y,double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    pt operator - (pt p1)   ///��������
    {
        return pt(x-p1.x,y-p1.y,z-p1.z);
    }
    pt operator * (pt p)    ///���
    {
        return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);
    }
    double operator ^ (pt p)    ///���
    {
        return x*p.x+y*p.y+z*p.z;
    }
};

struct _3DCH
{
    struct fac
    {
        int a,b,c;  ///��ʾ͹����������ı��
        bool ok;    ///��ʾ�����Ƿ���������͹������
    };

    int n;          ///��ʵ����
    pt P[X];        ///��ʼ��

    int cnt;        ///͹���������������
    fac F[X<<3];    ///͹�������������

    int to[X][X];

    double vlen(pt a)   ///��������
    {
        return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
    }

    double area(pt a,pt b,pt c) ///���������*2
    {
        return vlen((b-a)*(c-a));
    }

    double volume(pt a,pt b,pt c,pt d)///�������������*6
    {
        return (b-a)*(c-a)^(d-a);
    }

    ///��������ͬ����
    double ptof(pt &p,fac &f)
    {
        pt m = P[f.b]-P[f.a];
        pt n = P[f.c]-P[f.a];
        pt t = p-P[f.a];
        return (m*n)^t;
    }

    void deal(int p,int a,int b)
    {
        int f = to[a][b];
        fac add;
        if(F[f].ok)
        {
            if(ptof(P[p],F[f])>esp)
                dfs(p,f);
            else
            {
                add.a = b;
                add.b = a;
                add.c = p;
                add.ok = true;
                to[p][b] = to[a][p] = to[b][a] = cnt;
                F[cnt++] = add;
            }
        }
    }

    void dfs(int p,int cur)
    {
        F[cur].ok = false;
        deal(p,F[cur].b,F[cur].a);
        deal(p,F[cur].c,F[cur].b);
        deal(p,F[cur].a,F[cur].c);
    }

    bool same(int s,int t)
    {
        pt &a = P[F[s].a];
        pt &b = P[F[s].b];
        pt &c = P[F[s].c];
        return fabs(volume(a,b,c,P[F[t].a]))<esp&&fabs(volume(a,b,c,P[F[t].b]))<esp&&fabs(volume(a,b,c,P[F[t].c]))<esp;
    }

    void construct()
    {
        cnt = 0;
        if(n<4)
            return;


        ///*******�˶���Ϊ�˱�֤ǰ�ĸ��㲻���ߣ����Ա�֤����ȥ��
        bool sb = 1;
        ///ʹǰ���㲻����
        for(int i=1;i<n;i++)
        {
            if(vlen(P[0]-P[i])>esp)
            {
                swap(P[1],P[i]);
                sb = 0;
                break;
            }
        }
        if(sb)
            return;


        ///ʹǰ���㲻����
        sb = 1;
        for(int i=2;i<n;i++)
        {
            if(vlen((P[0]-P[1])*(P[1]-P[i]))>esp)
            {
                swap(P[2],P[i]);
                sb = 0;
                break;
            }
        }
        if(sb)
            return;

        sb = 1;
        ///ʹǰ�ĵ㲻����
        for(int i=3;i<n;i++)
        {
            if(fabs((P[0]-P[1])*(P[1]-P[2])^(P[0]-P[i]))>esp)
            {
                swap(P[3],P[i]);
                sb = 0;
                break;
            }
        }
        if(sb)
            return;
        ///�˶���Ϊ�˱�֤ǰ�ĸ��㲻����


        fac add;

        for(int i=0;i<4;i++)
        {
            add.a = (i+1)%4;
            add.b = (i+2)%4;
            add.c = (i+3)%4;
            add.ok = true;

            if(ptof(P[i],add)>0)
                swap(add.b,add.c);
            to[add.a][add.b] = to[add.b][add.c] = to[add.c][add.a] = cnt;
            F[cnt++] = add;
        }

        for(int i=4;i<n;i++)
            for(int j=0;j<cnt;j++)
                if(F[j].ok&&ptof(P[i],F[j])>esp)
                {
                    dfs(i,j);
                    break;
                }

        int tmp = cnt;
        cnt = 0;
        for(int i=0;i<tmp;i++)
            if(F[i].ok)
                F[cnt++] = F[i];
    }

    ///�����
    double area()
    {
        double ret = 0.0;
        for(int i=0;i<cnt;i++)
            ret += area(P[F[i].a],P[F[i].b],P[F[i].c]);
        return ret/2.0;
    }

    ///���
    double volume()
    {
        pt o(0,0,0);
        double ret = 0.0;
        for(int i=0;i<cnt;i++)
            ret += volume(o,P[F[i].a],P[F[i].b],P[F[i].c]);
        return ret/6.0;
    }

    ///���������ε���
    int facetCnt_tri()
    {
        return cnt;
    }

    ///����������
    int facecnt()
    {
        int ans = 0;
        for(int i=0;i<cnt;i++)
        {
            bool nb = true;
            for(int j=0;j<i;j++)
                if(same(i,j))
                {
                    nb = 0;
                    break;
                }
            ans += nb;
        }
        return ans;
    }

};

_3DCH hull;     ///���д����飬���׷��ں�����

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(scanf("%d",&hull.n)!=EOF)
    {
        for(int i=0;i<hull.n;i++)
            scanf("%lf%lf%lf",&hull.P[i].x,&hull.P[i].y,&hull.P[i].z);
        hull.construct();
        printf("%.03f\n",hull.area());
    }
    return 0;
}
