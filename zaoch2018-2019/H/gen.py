import random

A = int(10 ** 10)
B = 8 * int(10 ** 10)

l = random.randint(A, B)
r = random.randint(A, B)
if l > r:
    l, r = r, l
print("999" + str(l))
print("999" + str(r))
# print(r)