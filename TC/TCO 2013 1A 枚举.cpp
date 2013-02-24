/*
 * 题目：
 *   给出一个字符方格矩阵，每个格子有数字0-9，现在需要把矩阵中所有数字的差值不超过一，问最少需要执行加一减一
 * 	操作多少次
 * 
 * 分析：
 * 	枚举最终的数字就行了。。。
 * 
 * */
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define rep(i,n) for(int i=0;i<n;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
class
HouseBuilding{
public:
    int getMinimum(vector <string> vec){
        int n = vec.size();
        int ans = 1000000000;
        for(int x=0;x<10;x++){
            for(int y=max(x-1,0);y<x+2 && y<10 ;y++){
                int cnt = 0;
                for(int i=0;i<n;i++){
                    foreach(j,vec[i]){
                        int id = vec[i][j]-'0';
                        cnt += min( max(id-x,x-id) , max(id-y,y-id) );
                    }
                }
               	ans = min(ans,cnt);
            }
        }
        return ans;
    }
};
