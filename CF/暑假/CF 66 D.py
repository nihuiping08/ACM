
#要求一串数列：a1,..,an，使得gcd(a1,...,an) = 1，Gcd(ai,aj) != 1。ai互不相同	
#直接筛法筛出n个素数，把他们全部分配到每一个ai中，最后ai /= pi


p = [0]*1005
use = [0]*1005

def init():
    tot = 0
    for i in range(2,1000):
        if not use[i]:
            p[tot] = i
            tot += 1
            j = i+i
            while j<1000:
                use[j] = True;
                j += i


init()
n = int(raw_input())

if n==2:
    print -1
    exit(0)

ans = [0]*1000
tmp = 1
for i in range(n):
    tmp *= p[i]
for i in range(n):
    ans[i] = tmp//p[i]

for i in range(n):
    print ans[i]
