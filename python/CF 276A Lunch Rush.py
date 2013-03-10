#水一道python题。。。
def Max(x,y):
	if x>y:
		return x
	return y

#s = input()
s = raw_input()
q = s.split(' ')
n = int(q[0])
m = int(q[1])

ans = -10000000000000000000
for i in range(0,n):
	s = raw_input()
	q = s.split()
	x = int(q[0])
	y = int(q[1])
	ans = Max( ans, x-Max(y-m,0) )
#print(ans)
print ans

