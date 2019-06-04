# exit, break, continue

for ((t=1;;t++)) ; do
	echo "Test $t"
	./gen $t > input || break 
	cat input
	# tac, head, tail 
	time ./solution < input > output || break
	# /usr/bin/time --format="%Mkb %Usec" ./solution < input > output || break
	./slow_solution < input > answer || break
	diff output answer || break
	# ./check input output answer || break
done
# less input

# A || B
# A && B

#./solution < input
#./solution
