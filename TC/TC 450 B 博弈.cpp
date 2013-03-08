/*

题目：给出n堆石子，数量分别为a1,...,an。order Nim游戏是指从a1开始，如果该堆石子还有的话，只能够从该
	  堆石子中拿一个或者多个，问两者都是足够聪明，问谁能够最后拿石子。
分析：当数列前K项为 1...1时。若k+1不为1，轮到谁谁就赢。若都是1，则判断n的奇偶性

*/
#include <string>
#include <vector>

using namespace std;

class OrderedNim{
public:
    string winner(vector <int> vec){
        int n = vec.size();
        if(n==1)
  	    	return "Alice";
        int ok = 0;
        for(int i=0;i<n;i++){
            if(vec[i]==1)
                ok ^= 1;
            else{
                if(ok==0)
                    return "Alice";
                else
                    return "Bob";
            }
        }
        if(n&1)
            return "Alice";
        return "Bob";
    }
};
