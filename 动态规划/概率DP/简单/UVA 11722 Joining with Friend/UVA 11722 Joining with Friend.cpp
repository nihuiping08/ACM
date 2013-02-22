#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

#define debug puts("here");

int s1,s2,t1,t2;
double tot;

double area(int w){
    int lc = t1+w;
    int rc = t2+w;
    int uc = s2-w;
    int dc = s1-w;
    if(lc>=s2)
        return tot;
    if(rc<=s1)
        return 0;
    bool okl = (lc>=s1)&&(lc<=s2);
    bool okd = (dc>=t1)&&(dc<=t2);
    bool okr = (rc>=s1)&&(rc<=s2);
    bool oku = (uc>=t1)&&(uc<=t2);
    if(okl&&oku)
        return tot-(uc-t1)*(s2-lc)*0.5;
    if(okl&&okr)
        return ((lc-s1)+(rc-s1))*(t2-t1)*0.5;
    if(okd&&oku)
        return ((t2-uc)+(t2-dc))*(s2-s1)*0.5;
    if(okd&&okr)
        return (t2-dc)*(rc-s1)*0.5;
    return 0;
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase,cnt = 0;
    int w;
    cin>>ncase;
    while(ncase--){
        cin>>t1>>t2>>s1>>s2>>w;
        tot = (t2-t1)*(s2-s1);
        double ans = area(w)-area(-w);
        ans /= tot;
        printf("Case #%d: %.8lf\n",++cnt,ans);
    }
    return 0;
}
