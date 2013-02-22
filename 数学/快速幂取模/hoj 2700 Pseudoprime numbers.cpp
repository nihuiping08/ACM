/*This Code is Submitted by 1113710427 for Problem 2700 at 2012-04-14 22:40:00*/
#include <cstdio>
#include <iostream>
using namespace std;
int power(int a,int b,int p)
{
        int r = 1;
        while(b>0)
        {
                if(b&1)
                        r = (long long)r*a%p;
                a = (long long)a*a%p;
                b = b>>1;
        }
        return r;
}
bool check(int p)
{
        for(int i=2;i*i<=p;i++)
                if(p%i==0)
                        return false;
        return true;
}
int main()
{
        int a,p;
        while(cin>>p>>a,a||p)
        {
                if(!check(p)&&power(a,p,p)==a)
                        cout<<"yes"<<endl;
                else
                        cout<<"no"<<endl;
        }
        return 0;
}