/*

题目：
	给出两个矩形的左下右上坐标，求两矩形的位置关系
	
分析：
	种子填充法，直接对一个矩形在坐标轴上染色，然后再判断是否内含，再判断相邻的是否为顶点，
	若没有相邻的话，输出none，否则若存在被染色的顶点数大于1或者相邻的不都为顶点。。

*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

#define debug puts("here");

class 
TwoRectangles
{
public:
	string describeIntersection(vector <int> A, vector <int> B){
		const int X = 1005;
		bool use[X][X];
		memset(use,false,sizeof(use));
		for(int i=A[0]+1;i<=A[2];i++)
			for(int j=A[1]+1;j<=A[3];j++)
				use[i][j] = true;
		for(int i=B[0]+1;i<=B[2];i++)
			for(int j=B[1]+1;j<=B[3];j++)
				if(use[i][j])
					return "rectangle";
		int ans = 0;
		
		for(int i=A[0];i<=A[2];i++)
			for(int j=A[1];j<=A[3];j++)
				use[i][j] = true;
				
		for(int i=B[0];i<=B[2];i++)
			for(int j=B[1];j<=B[3];j++){
				if(use[i][j]){
					ans++;
					if((i==A[0]||i==A[2])&&(j==A[1]||j==A[3])&&(i==B[0]||i==B[2])&&(j==B[1]||j==B[3]))
						continue;
					else
						return "segment";
				}
			}
		if(ans>1)
			return "segment";
		else if(ans==1)
			return "point";
		return "none";
	}
};