print('21'>'2')
def srt(a, b):
    return True
fin = open("number.in", "r")
fout = open("number.out", "w")
Arr = fin.readlines()
for i in range(len(Arr)):
    Arr[i] = list(Arr[i])
    if Arr[i][-1] == '\n':
        Arr[i].pop(-1)
Arr.sort(reverse = True)
Ans = []
for i in Arr:
    Ans += i
str = ''.join(Ans)
fout.write(str)
