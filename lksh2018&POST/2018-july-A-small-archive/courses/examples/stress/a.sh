n=10
testName=input.txt
outputName=output.txt
answerName=answer.txt

function compile {
	echo compile $1 # $1 -- аргумент функции
	if [ -e $1.cpp ] ; then
		g++ $1.cpp -std=c++17 -o $1 
	else
		echo $1.cpp is not found
		exit
	fi
	# A || B <---- 1. A, 2. if (A == 0)
}
# compile a
# compile b
# compile gen

for ((i = 1;; i++)) ; do
	#echo "Test $i"
	./gen $i > $testName || exit
	# --format="%Mkb %Usec"
	/usr/bin/time --format="%Usec" ./a < $testName > $outputName || exit
	./b < $testName > $answerName || exit
	diff $outputName $answerName || break
done
echo -n Test: 
cat $testName
#tac 

# Максимум в массиве
#   (bash a.sh) 2>&1 | sort | tac | grep "0." | head -n 1
