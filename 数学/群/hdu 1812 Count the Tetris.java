/*
 * 题目：
 *		给出n*n的方格矩阵，有t种颜色，在旋转、沿中心反射、沿对角线反射的情况下涂色，
 *		问不等价类的总数
 *	分析：
 *		对于旋转，有四种情况：
 *		0度：循环群有n*n个
 *		90度、270度：循环群有(n*n-n)/2+n个
 *		180度：循环群有(n*n+1)/2个
 *		
 *		对于反射：
 *		1.沿对角线：有两种，都是(n*n-n)/2+n
 *		2.沿中心：有两种，当n为奇数的时候：(n*n-n)/2+n;当n为偶数的时候：(n*n)/2
 *
 *		所以答案 = {  t^(n*n) + t^(n*n+n) + t^(n*n+1)/2 + t^(n*n+n) } + 
 *					t^(n*n+n) // 奇数
 *					t^(n*n) // 偶数
 *
 * */
import java.math.*;
import java.util.*;

public class Main{
	
	public static BigInteger pw(int q,int cnt){
		BigInteger t = BigInteger.valueOf(q);
		BigInteger ans = BigInteger.ONE;
		for(int i=0;i<cnt;i++)
			ans = ans.multiply(t);
		return ans;
	}

	public static void main(String [] args){
		Scanner cin = new Scanner(System.in);
		BigInteger two = BigInteger.valueOf(2);
		while(cin.hasNext()){
			int n = cin.nextInt();
			int t = cin.nextInt();
			BigInteger ans = BigInteger.ZERO;
			ans = ans.add( pw( t , n*n ) ); // 0
			ans = ans.add( pw( t , (n*n+3)/4) ); // 90
			ans = ans.add( pw( t , (n*n+1)/2 ) ); // 180
			ans = ans.add( pw( t , (n*n+3)/4 ) ); // 270
			ans = ans.add( pw( t , (n*n-n)/2+n ).multiply(two) ); // 对角线
			if(n%2==1)  // 对称
				ans = ans.add( pw( t , (n*n-n)/2+n ).multiply(two) );
			else
				ans = ans.add( pw( t , (n*n)/2 ).multiply(two) );
			System.out.println(ans.divide(BigInteger.valueOf(8)));
		}
	}
}
