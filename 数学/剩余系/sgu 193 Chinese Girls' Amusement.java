/*
 * 题目：
 * 		约瑟夫环问题，给出n，问最大的k使得每个人都会轮流到（1<k<=n/2）
 * 分析：
 * 		k,k*2,...k*(n-1)构成n的剩余系。所以我们知道k%n！=0
 * 		1.对于n = 2*mid+1，所以gcd(n,mid) = gcd(mid+1,mid) == 1
 * 		2.对于n = 2*mid，所以需要确定mid-1是不是满足条件
 * 			gcd(n,mid-1) = gcd(mid+1,mid-1) = gcd(mid-1,2)
 * 			1.mid|2，ans = mid-2
 * 			2.ans = mid-1
 * 
 * */
import java.math.*;
import java.util.*;

public class Main{
	public static void main(String [] agus){
		Scanner cin = new Scanner(System.in);
		while(cin.hasNext()){
			BigInteger ans = cin.nextBigInteger();
			BigInteger two = BigInteger.valueOf(2);
			
			BigInteger mid = ans.divide(two);
			BigInteger tmp = mid.subtract(BigInteger.ONE);
			
			if(ans.mod(two)==BigInteger.ZERO){
				if(tmp.mod(two)==BigInteger.ZERO)
					System.out.println(mid.subtract(two));
				else
					System.out.println(mid.subtract(BigInteger.ONE));
			}else
				System.out.println(mid);
		}
	}
}