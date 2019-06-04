# inp = open("input.txt", "r")

def main():
    ll = input().strip()
    rr = input().strip()

    n = len(rr)

    r = [0 for i in range(n)]
    l = [0 for i in range(n)]

    for i in range(len(rr)):
        r[i] = int(rr[i])

    for i in range(len(ll)):
        l[n - i - 1] = int(ll[len(ll) - i - 1])

    coptpos = -1
    islmr = 0
    coptval = 0
    isnonzero = 0
    dc = 1
    d9 = 0
    for i in range(len(r)):
        if l[i] != 0:
            isnonzero = 1
        if dc == 0 and isnonzero == 0:
            dc = 1
            d9 = 0
        if l[i] < r[i]:
            islmr = 1

        if islmr and r[i] == 1:
            if isnonzero == 1:
                continue
            if coptpos == -1:
                dc = 1
                d9 = 0
                coptval = 1
                coptpos = i
                continue
            lopt9 = n - coptpos - 1

            lopt9 -= d9 + (n - i - 1)
            if lopt9 < 0:
                print("!")
                exit(-1)

            if (9 ** lopt9) * (coptval) < dc * (r[i] - 1):
                lopt9 = i
                dc = 1
                d9 = 0
                coptval = 1
                coptpos = i
                continue

        elif islmr and r[i] == 0:
            continue
        elif islmr:
            if coptpos == -1:
                dc = 1
                d9 = 0
                if r[i] == 9:
                    d9 += 1
                else:
                    dc *= r[i]
                coptval = r[i] - 1
                coptpos = i
                continue
            else:
                lopt9 = n - coptpos - d9 - n + i
                if lopt9 < 0:
                    print("!")
                    exit(-1)
                if (9 ** lopt9) * (coptval) < dc * (r[i] - 1):
                    dc = 1
                    d9 = 0

                    if r[i] == 9:
                        d9 += 1
                    else:
                        dc *= r[i]

                    coptpos = i
                    coptval = r[i] - 1
                    continue

        if r[i] == 9:
            d9 += 1
        else:
            dc *= r[i]
        if n - coptpos - d9 - n + i > 50:
            break

    lopt9 = n - coptpos - 1 - d9
    if(lopt9 < 50):
        if (9 ** lopt9) * coptval < dc:
            coptpos = -1

    if coptpos == -1:
        print(rr)
    else:
        s = []
        for i in range(0, coptpos):
            s.append(r[i])
        s.append(r[coptpos] - 1)
        for i in range(coptpos + 1, n):
            s.append(9)
        t = 0
        for i in s:
            if i == 0 and t == 0:
                continue
            t = 1
            print(i, end = '')
        print()
main()