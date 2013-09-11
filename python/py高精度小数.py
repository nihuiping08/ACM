from decimal import *
getcontext().prec = 50

n = 0
ans = Decimal(0)
a = [ 0 for i in range(55) ]
b = [ 0 for i in range(55) ]
p = [ 0 for i in range(55) ]
use = [ False for i in range(55) ]

def dfs(i,sum):
	global ans
	if i== n+1:
		ans += sum
		return
	if p[i] != 0:
		if use[a[i]]==False:
			use[a[i]] = True
			dfs(i+1,sum * Decimal(p[i])/Decimal(100) )
			use[a[i]] = False
	if 100-p[i]>0:
		if use[ b[i] ]==False:
			use[b[i]] = True
			dfs(i+1,sum * Decimal(100-p[i])/Decimal(100) )
			use[b[i]] = False


ncase = int(input())
while ncase:
	ncase -= 1
	n = int(input())
	for i in range(1,n+1):
		s = input().split(' ')
		p[i] = int(s[0])
		a[i] = int(s[1])
		b[i] = int(s[2])
	ans = Decimal(0)
	for i in range(1,20):
		use[i] = False
	dfs(1,Decimal(1))
	print( Decimal(ans) )