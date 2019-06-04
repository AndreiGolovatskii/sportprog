for ((i = 1;; i++)) ; do
	echo Test $i
	./gen > input || exit
	./sol_slow < input > answer || exit
	./sol_fast < input > output || exit
	diff answer output || exit
done

