/*

��Ŀ��
    �����и����ĵ���������У�ÿ̨������Ҫ�����ĵĸ����������һ��������ÿ�����������Ӧ
    �ļ۸��Լ���ֵ�����ڶ�����Եļ�ֵΪ����������е���С��ֵ�����ڸ�����ӵ�еĽ�Ǯ�Լ�n
    �������������Ե�����ֵ

������
    �ȶ����������������ͬ�Ļ�Ȼ���ռ�ֵ���򣬶��ִ𰸣�Ȼ����ÿһ���������С�۸�ʹ��
    �����ֵ���ڶ��ֵĴ�

*/
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

const int X = 1005;

int n,fare,mid;

struct node
{
    string a,b;
    int price,value;
    friend bool operator < (node a,node b)
    {
        return a.a<b.a||(a.a==b.a&&a.value<b.value);
    }
}p[X];

int check()
{
    string s;
    s = p[0].a;
    int cnt = -1,temp = 0;
    if(p[0].value>=mid)
        cnt = p[0].price;
    for(int i=0;i<n;i++)
    {
        if(s==p[i].a)
        {
            if(p[i].value>=mid)
            {
                if(cnt==-1)
                    cnt = p[i].price;
                else
                    cnt = min(cnt,p[i].price);
            }
        }
        else
        {
            s = p[i].a;
            if(cnt==-1)
                return -1;
            temp += cnt;
            if(mid<=p[i].value)
                cnt = p[i].price;
            else
                cnt = -1;
        }
    }
    if(cnt==-1)
        return -1;
    temp += cnt;
    if(temp==fare)
        return 0;
    else if(temp>fare)
        return -1;
    else
        return 1;
}

void binary()
{
    int right = mid;
    int left = 0;
    int temp;
    while(left<right)
    {
        mid = (left+right)>>1;
        temp = check();
        if(temp==0)
            left = mid;
        else if(temp==1)
            left = mid+1;
        else
            right = mid-1;
    }
    mid = left;
    if(check()!=-1)
        cout<<left<<endl;
    else
        cout<<left-1<<endl;
}

int main()
{
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        cin>>n>>fare;
        mid = 0;
        for(int i=0;i<n;i++)
        {
            cin>>p[i].a>>p[i].b>>p[i].price>>p[i].value;
            mid = max(mid,p[i].value);
        }

        sort(p,p+n);

        binary();
    }
    return 0;
}
