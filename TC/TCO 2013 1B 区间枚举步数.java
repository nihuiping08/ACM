/*
 * 题目：
 *   在数轴上给出n个区间，现在从0开始走到len，每次走的步长固定，问不经过这些区间（在区间的端点上是允许的）
 * 	的最小步长
 * 
 * 分析：
 * 	我们知道，最优解一定会是经过某个端点，我们可以枚举步长（一定是区间[a,b],a表示最大的区间 长度，b表
 * 	示当前枚举到的右端端点），然后枚举步数，如果符合的话，就更新答案。步长加1，再更新当前的步长，然后再
 * 	重新判断是否满足。判断是否在区间的话，可以直接比较是否右区间的步数比左区间的步数多，注意eps
 * 
 * */
class TheFrog{
	public double getMinimum(int len, int[] a, int[] b){
		double ans = len;
		double tmp = 0;
		for(int i=0;i<a.length;i++)
			tmp = Math.max(b[i]-a[i],tmp);
		double eps = 1e-9;
		for(int i=0;i<a.length;i++){
			int step = 1;
			for(double j=b[i];j>=tmp-eps;){
				boolean ok = true;
				for(int k=0;k<a.length;k++){
					int p = (int)(a[k]/j+eps);
					int q = (int)(b[k]/j-eps);
					if(q>p){
						ok = false;
						break;
					}
				}
				if(ok)
					ans = Math.min(ans, j);
				step ++;
				j = (double)b[i]/step;
			}
		}
		return ans;
	}
}
