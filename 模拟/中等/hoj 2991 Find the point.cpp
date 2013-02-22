/*

题目：
    寻找最值

分析：
    就是得要输入字符串，然后转数字在比较，因为小数点不确定

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#define esp 1e-8

struct node
{
    double x,y;
    string s;
}ma,mi;

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int ncase,n;
    cin>>ncase;
    string s;
    while(ncase--)
    {
        cin>>n;
        bool first = false;
        for(int j=0;j<n;j++)
        {
            cin>>s;
            double temp = 0;
            bool flag = false;
            int cnt = -1;
            double ret;

            for(int i=1;s[i];i++)
            {
                if(s[i]=='-')
                    flag = true;
                else if(s[i]>='0'&&s[i]<='9')
                {
                    if(cnt!=-1)
                        cnt++;
                    temp = temp*10+s[i]-'0';
                }
                else if(s[i]=='.')
                    cnt = 0;
                else if(s[i]==',')
                {
                    for(int j=0;j<cnt;j++)
                        temp /= 10;
                    if(flag)
                        temp = -temp;
                    flag = false;
                    ret = temp;
                    temp = 0;
                }
                else if(s[i]==')')
                {
                    for(int j=0;j<cnt;j++)
                        temp /= 10;
                    cnt = -1;
                    if(flag)
                        temp = -temp;
                    flag = false;
                    //cout<<"ret  =  "<<ret<<"  temp =  "<<temp<<endl;
                    if(first)
                    {
                        //cout<<"dsasadsda"<<endl;
                        if(mi.y>temp||(fabs(mi.y-temp)<esp&&mi.x>ret))
                        {
                            mi.y = temp;
                            mi.x = ret;
                            mi.s = s;
                        }
                        else if((temp>ma.y)||(fabs(temp-ma.y)<esp&&ma.x-ret>0))
                        {
                            ma.y = temp;
                            ma.x = ret;
                            ma.s = s;
                        }
                    }
                    else
                    {
                        first = true;
                        ma.x = mi.x = ret;
                        ma.y = mi.y = temp;
                        ma.s = mi.s = s;
                    }
                    temp = 0;
                }
            }
            //cout<<ma.s<<"  "<<mi.s<<endl;
        }
        //cout<<endl;
        cout<<ma.s<<" "<<mi.s<<endl;
        //cout<<endl;
    }
    return 0;
}
