inpa = open("./run/my_ans")
inpb = open("./run/corr_ans")
inpt = open("./run/test")

l = int(inpt.readline().strip())
r = int(inpt.readline().strip())

ma = inpa.readline().strip()
ca = inpb.readline().strip()
if(l > int(ma) or r < int(ma)):
 	print("Wrong answer (incorrect segment)", end=' ')
 	exit(-1)


sm = 1
for i in ma:
	sm *= int(i)

sc = 1
for i in ca:
	sc *= int(i)

if sc != sm:
	print("Wrong answer", end=' ')
	exit(1)

print("test ok", end=' ')