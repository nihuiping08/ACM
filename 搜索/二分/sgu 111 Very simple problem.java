/*
 * 题目：
 * 		找出满足x*x<=n最大的x的数，n<=10^1000
 * 分析：
 * 		二分加大数
 * 
 * */
import java.math.*;
import java.util.*;

public class Main{
	public static void main(String [] args){
		Scanner cin = new Scanner(System.in);
		while(cin.hasNext()){
			
			BigInteger n = cin.nextBigInteger();
			BigInteger l = BigInteger.ONE;
			BigInteger r = n.subtract(l);
			BigInteger two = l.add(l);
			BigInteger ans = BigInteger.ONE;
			
			while(l.compareTo(r)<=0){
				BigInteger mid = l.add(r);
				mid = mid.divide(two);
				BigInteger tmp = mid.multiply(mid);
				
				int ok = tmp.compareTo(n);
				
				if(ok<0){
					ans = mid;
					l = mid.add(BigInteger.ONE);
				}else if(ok==0){
					ans = mid;
					break;
				}else
					r = mid.subtract(BigInteger.ONE);
			}
			System.out.println(ans);
		}
	}
}