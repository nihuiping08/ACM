/*

题目：
    拓扑排序题，给出一些关系，问最快何时能够确定关系，或者出现矛盾，或者最后没有确定关系（即没有
    大小关系全部确定，有没有矛盾产生）。

分析：
    每输入一组关系时，都对有向图进行一次拓扑排序，若排序成功，说明当前为最优解，以后可以不用再次
    进行排序，若排序过程中出现矛盾，证明当前为出现矛盾的最优解，同样以后可以不用进行排序。

    拓扑排序的思想：
        在有向图中，每次寻找入度为0的顶点，若该顶点数为0，说明图中有环。若该顶点数大于一，说明暂时
        不能确定，但由于先得判断是否有矛盾，所以还得往下进行排序。而找到的入度为0的顶点储存到数组中，
        若最后排序成功后，该数组的元素即为该输入元素的大小关系。

*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int X = 105;
int ans[X],t[X],in[X],n,m;
bool map[X][X];

int topo(){     //出现矛盾，返回0，排序成功返回1，还没确定关系，返回-1
    int cnt,temp,ret = 0;
    for(int i=0;i<n;i++)
        t[i] = in[i];   //借助另一数组来储存当前的入度数
    int flag = 1;
    for(int i=0;i<n;i++){
        cnt = 0;
        for(int j=0;j<n;j++)
            if(t[j]==0){    //找到入度为0的点
                cnt++;
                temp = j;
            }
        if(cnt==0)  //&&cnt!=n  //证明有环
            return 0;
        if(cnt>1)   //说明不能确定关系，但先判断的是有没有矛盾
            flag = -1;
        t[temp] = -1;
        ans[ret++] = temp;  //储存答案
        for(int j=0;j<n;j++)
            if(map[temp][j])
                t[j]--;
    }
    return flag;
}

int main(){
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    char s[10];
    while(cin>>n>>m,n||m){
        bool flag = true;
        int temp,x,y;

        memset(map,false,sizeof(map));
        memset(in,0,sizeof(in));

        for(int i=1;i<=m;i++){
            scanf("%s",s);
            x = s[0]-'A';
            y = s[2]-'A';
            map[x][y] = true;
            in[y]++;
            if(flag)
                temp = topo();
            if(temp==1&&flag){
                flag = false;
                printf("Sorted sequence determined after %d relations: ",i);
                for(int i=0;i<n;i++)
                    printf("%c",(char)ans[i]+'A');
                printf(".\n");
            }
            if(temp==0&&flag){
                flag = false;
                printf("Inconsistency found after %d relations.\n",i);
            }
        }
        if(flag)
            printf("Sorted sequence cannot be determined.\n");
    }
    return 0;
}
