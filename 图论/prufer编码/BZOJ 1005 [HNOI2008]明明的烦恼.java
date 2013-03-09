/*
 * 题目：
 * 		给出标号为1到N的点,以及某些点最终的度数,允许在任意两点间连线,可产生多少棵度数满足要求的树?
 * 分析：
 * 		prufer编码方式。n个节点的树的prufer编码一共有n-2项。
 * 		
 * 		1.已知树，求prufer编码：每次取出编号最小的叶子节点，然后把叶子节点相邻的节点放在当前prufer
 * 		编码队列的后面，把该叶子节点拿掉。重复以上直到剩余两个节点为止。
 * 		
 * 		2.已知prufer编码，求树：写下 1到n ,找出一个没有出现在prufer编码里的数x，把当前遍历到的
 * 		prufer编码y与x连边，把x去掉，遍历位置后移一位。重复以上直到序列为空。
 * 
 * 		这题的解题方式：
 * 		在prufer编码里，度为du[i]的节点出现了du[i]-1次。
 * 		所以我们利用乘法计数原理可知，对于有限制的节点来说：
 * 		tot = sigma(du[i]-1)
 * 		ans = (n-2)! / ( (n-2-tot)*PI((du[i]-1)!) )
 * 		对于没有限制的节点（个数为sum），sum^(n-2-tot)。
 * 
 * */
import java.util.*;
import java.math.*;

public class Main{
	public static void main(String [] args){
		Scanner cin = new Scanner(System.in);
		
		int [] du = new int[2005];
		
		int n = cin.nextInt();
		
		int tot = 0,sum = 0;
		boolean ok = true;
		for(int i=1;i<=n;i++){
			du[i] = cin.nextInt();
			if(du[i]<-1 || du[i]>n-1){
				ok = false;
				continue;
			}
			
			if(du[i]==-1)
				sum ++;
			else
				tot += du[i]-1;
		}
		if(!ok){
			System.out.println(0);
			return;
		}
		
		if(tot>n-2||(sum==0&&tot<n-2)){
			System.out.println(0);
			return;
		}
		
		if(n==1||n==2){
			System.out.println(1);
			return;
		}
		
		BigInteger [] f = new BigInteger[1005];
		f[0] = f[1] = BigInteger.ONE;
		for(int i=2;i<=n;i++)
			f[i] = f[i-1].multiply(BigInteger.valueOf(i));
		
		BigInteger tmp = f[0];
		for(int i=1;i<=n;i++)
			if(du[i]>0)
				tmp = tmp.multiply(f[du[i]-1]);
		
		BigInteger ans = f[n-2].divide(f[n-2-tot]);
		BigInteger ret = BigInteger.valueOf(sum).pow(n-2-tot);
		ans = ans.multiply(ret).divide(tmp);
		System.out.println(ans);
	}
}