#a = [ [0 for i in range(305)] for i in range(305)]

def Min(x,y):
	if x<y:
		return x
	return y

def f():
	n = int(raw_input())
	#n = int(input())
	q = raw_input()
	#q = input()
	
	if n==1:
		x = int(q)
		if x:
			return True
		else:
			return False

	if n==2:
		s = q.split(' ')
		x = int(s[0])
		y = int(s[1])
		a = [ [0 for i in range(301)] for i in range(301) ]
		a[0][0] = 0
		for i in range(0,x+1):
			for j in range(0,y+1):
				if a[i][j]==0:
					tmp = x-i
					if tmp>y-j:
						tmp = y-j
					for d in range(1,tmp+1):
						a[i+d][j+d] = 1
					for d in range(1,x-i+1):
						a[i+d][j] = 1
					for d in range(1,y-j+1):
						a[i][j+d] = 1
		return a[x][y]
	
	
	a = [[ [0 for i in range(301)] for i in range(301) ] for i in range(301) ]
	
	s = q.split(' ')
	x = int(s[0])
	y = int(s[1])
	z = int(s[2])
	
	a[0][0][0] = 0
	for i in range(0,x+1):
		for j in range(0,y+1):
			for k in range(0,z+1):
				if a[i][j][k]==0:
					tmp = Min( x-i , Min(y-j,z-k) )+1
					for d in range(1,tmp):
						a[i+d][j+d][k+d] = 1
					for d in range(1,x-i+1):
						a[i+d][j][k] = 1
					for d in range(1,y-j+1):
						a[i][j+d][k] = 1
					for d in range(1,z-k+1):
						a[i][j][k+d] = 1
	return a[x][y][z]


if f():
	print "BitLGM"
	#print("BitLGM")
else:
	#print("BitAryo")
	print "BitAryo"

