/*

题目：
    在下列给出的电脑零配件中，每台电脑需要给出的的各个零配件的一件，并且每种零配件有相应
    的价格以及价值。现在定义电脑的价值为所有零配件中的最小价值，现在给出你拥有的金钱以及n
    个配件，问你电脑的最大价值

分析：
    先对配件的名字排序，相同的话然后按照价值排序，二分答案，然后找每一种配件的最小价格使得
    满足价值大于二分的答案

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
