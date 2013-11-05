/*

判断点是否在多边形内

*/
const int MAXN = 1e5+5;

int n,m;

struct node{
    ll x,y;
    void input(){
        LL(x);LL(y);
    }
}p[MAXN];

ll det(node a,node b,node o){
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}

bool cc(node now){
    if(det(p[1],now,p[n])>=0)
        return false;
    int l = 1 , r = n-1;
    int ans = -1;
    while(l<=r){
        int mid = (l+r)>>1;
        if(det(p[mid],now,p[n])<=0){
            l = mid+1;
            ans = mid;
        }else r = mid-1;
    }
    return det(p[ans],now,p[ans+1])>0;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n){
        rep1(i,n)
            p[i].input();
        RD(m);
        bool ok = true;
        node now;
        while(m--){
            now.input();
            ok = ok&&cc(now);
        }
        puts(ok?"YES":"NO");
    }

	return 0;
}
