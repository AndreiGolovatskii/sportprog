ll = input().strip()
rr = input().strip()

n = len(rr)

l = [0 for i in range(n)]
r = [0 for i in range(n)]

for i in range(n):
    r[i] = int(rr[i])

for i in range(len(ll)):
    l[n - i - 1] = int(ll[len(ll) - i - 1])

def tn(a):
    s = ''.join(map(str, a))
    return int(s)
def gv(a):
    res = 1
    for i in a:
        res *= i
    return res

def clc(a, pos):
    c = a[::]
    for i in range(len(a)):
        # if i == pos:
            # r[i] -= 1
        if i > pos:
            c[i] = 9
    while c[0] == 0:
        c = c[1:]
    return c

ln = int(ll)
rn = int(rr)

opt = r[::]
for i in range(n):
    if r[i] > 0:
        r[i] -= 1
        k = clc(r, i)
        if ln <= tn(k):
            if gv(k) > gv(opt):
                opt = k
        r[i] += 1

print(''.join(map(str, opt)))
