/*

��Ŀ��
	�����������ε������������꣬�������ε�λ�ù�ϵ
	
������
	������䷨��ֱ�Ӷ�һ����������������Ⱦɫ��Ȼ�����ж��Ƿ��ں������ж����ڵ��Ƿ�Ϊ���㣬
	��û�����ڵĻ������none�����������ڱ�Ⱦɫ�Ķ���������1�������ڵĲ���Ϊ���㡣��

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