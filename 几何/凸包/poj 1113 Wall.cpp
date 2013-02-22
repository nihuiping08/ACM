/*

��һ��͹���⡣

graham��˼����ʵͦ�򵥵ģ������ȶ����еĵ���м���������������У�����������ͬ�Ļ���
�Ͱ��������ţ�Ȼ��õ������������е�����꣬Ȼ��ʼ��ʱ���ҵ���������ĵ㣬�ж����Ƿ�
��ǰһ���߶̣�����������ʱ͹���ϵ��߶Σ�����࣬���ǵĻ��Ͱ���һ�����ջ��ֱ��û������ת
�ĵ�Ϊֹ��Ȼ��������ĵ���뵽ջ�У��Ӷ��õ�͹�����㷨��ʱ�临�Ӷ�ΪO(nlogn)��

��Ŀ��
    ̰�ĵĹ����������ٵ�ʯͷ��Χ�ʹ���������Ҫ������ʹ�һ���ľ��룬������ö೤���߰���
    ��������

������
    ���󵽵�͹���м���һ��������Բ���ܳ�����

*/
/*
    ���ǿ����Ƚ�������һ��ת����������Ǳ������͹����Ȼ�����͹���ľ���ΪL�ıպ�ͼ�ε��ܳ���

    ����Ϊʲô��ת����͹�������ǲ����÷�֤�������Χǽ��͹���ڲ��ķ�������Ļ���Ȼ��Ҫ����
    �����������ͻ�����ϡ�

    Χǽ����״��������һ�����Ǻͱ�ƽ���ҵ��ڸ��ߵı߳��ģ�����һ���־���ǽ��λ�õĻ��Σ�
    ����������ε�Բ�Ľ����������ߵķ��������ļнǡ�

    �ڼ����ܳ���ʱ��һ���־���͹�����ܳ�����һ���־�����Щ���ĳ���֮�͡����ǵ�Ȼ�������
    ÿ�����ϵĻ���Ȼ���ۼӵ�һ�𣬵��������漰�ܶ�����Ǻ����Ϳ������������㣬�ͻ��и��ྫ
    ���ϵ���ʧ����ʵϸ��һ�»ᷢ�ְ���Щ��ƴ��������һ��������Բ���������͹�����ܳ�֮����
    ����һ���뾶ΪL��Բ���ܳ����ɡ�

*/
/*

���������ˮƽ���ŵġ�����

*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define PI 3.14159265
#define X 1005
struct point{
    int x,y;
    friend bool operator <(point a,point b){
        return a.y<b.y||(a.y==b.y&&a.x<b.x);
    }

}p[X],res[X];

int n,m,P;

int det(int x1,int y1,int x2,int y2)    //���
{
        return x1*y2-x2*y1;
}

bool del(int top,int i) //����ת�Ļ�������true�����򷵻�false
{
    if(det(res[top].x-res[top-1].x,res[top].y-res[top-1].y,p[i].x-res[top].x,p[i].y-res[top].y)<0)
        return true;
    return false;
}
int graham()       //��͹��
{
    int top = 1;
    res[0] = p[0],res[1] = p[1];
    for(int i=2;i<n;i++){
        while(top&&del(top,i))  //������ת����ջ
            top--;
        res[++top] = p[i];      //�������ĵ���ջ
    }
    int mint = top;
    res[++top] = p[n-2];
    for(int i=n-3;i>=0;i--){
        while(top!=mint&&del(top,i))
            --top;
        res[++top] = p[i];
    }
    return top;
}

void cal()
{
    double ans = 0;
    res[P+1] = res[1];
    for(int i=0;i<P;i++)
        ans += sqrt(1.0*(res[i].x-res[i+1].x)*(res[i].x-res[i+1].x)+(res[i].y-res[i+1].y)*(res[i].y-res[i+1].y));
    printf("%d\n",(int)(ans+PI*2*m+0.5));
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(cin>>n>>m){
        for(int i=0;i<n;i++)
            scanf("%d%d",&p[i].x,&p[i].y);
        sort(p,p+n);
        P = graham();
        cal();
    }
    return 0;
}
