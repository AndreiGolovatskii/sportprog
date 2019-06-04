def getP(a):
    if a == "(" or a == ")":
        return 0
    elif a == "|":
        return 1
    elif a == "&":
        return 2
    elif a == "!":
        return 3
    else:
        return -1


values = [0 for i in range(100)]


def getV(a):
    if a == "1":
        return 1
    elif a == "0":
        return 0
    else:
        return values[ord(a) - ord("A")]


def revV(a):
    global values
    values[ord(a) - ord("A")] = not values[ord(a) - ord("A")]


def calc():
    st = []
    for op in res:
        if getP(op) == -1:
            st.append(getV(op))
        elif op == "|":
            fi = st.pop()
            se = st.pop()
            st.append(fi | se)
        elif op == '&':
            fi = st.pop()
            se = st.pop()
            st.append(fi & se)
        elif op == "!":
            fi = st.pop()
            st.append(not fi)
    return st[0]


s = input()
s = s.replace("NOT", " ! ")
s = s.replace("AND", " & ")
s = s.replace("OR", " | ")
s = s.replace("TRUE", " 1 ")
s = s.replace("FALSE", " 0 ")
s = s.replace("(", " ( ")
s = s.replace(")", " ) ")

vec = s.split()

res = []
st = []
for op in vec:
    k = getP(op)
    if k == -1:
        res.append(op)
    else:
        if op == "(":
            st.append(op)
        elif op == ")":
            while st[-1] != "(":
                res.append(st.pop())
            st.pop()
        else:
            while len(st) and getP(st[-1]) > k:
                res.append(st.pop())
            st.append(op)
while len(st):
    if st[-1] != "(" and st[-1] != ")":
        res.append(st[-1])
    st.pop()


inp = list(map(int, input().split()))
n = inp[0]
m = inp[1]
k = inp[2]


g = [[0 for j in range(300)] for i in range(300)]
for i in range(m):
    dot = list(map(int, input().split()))
    x = int(dot[0])
    y = int(dot[1])
    if abs(x) <= n and abs(y) <= n:
        g[x][y] = 1

for i in range(k):
    dot = input().split()
    x = int(dot[0])
    y = int(dot[1])
    if abs(x) <= n and abs(y) <= n:
        g[x][y] = dot[2]


cur = (0, 0)
st = (1, 0)
while abs(cur[0]) <= n and abs(cur[1]) <= n:
    if g[cur[0]][cur[1]] == 1:
        k = calc()
        if not k:
            st = (-st[1], st[0])
        else:
            st = (st[1], -st[0])
    elif g[cur[0]][cur[1]] != 0:
        revV(g[cur[0]][cur[1]])
    print(str(cur[0]) + " " + str(cur[1]))
    cur = (cur[0] + st[0], cur[1] + st[1])





