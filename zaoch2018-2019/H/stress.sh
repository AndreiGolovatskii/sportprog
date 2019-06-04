echo 'compiling...'
rm ./run/gen ./run/sol ./run/corr_ans ./run/my_ans ./run/ok

# g++ -std=c++14 -O3 gen.cpp -o ./run/gen
# g++ -std=c++14 -O3 sol.cpp -o ./run/sol
# g++ -std=c++14 -O3 ok.cpp -o ./run/ok

echo 'start stress'

for((t = 0; t < 1000; t++));
do 
	# ./run/gen > "./run/test" || break
	python3 ./gen.py > "./run/test" || break 
	python3 ./ok.py < "./run/test" > ./run/corr_ans || break 
	python3 ./sol.py < "./run/test" > ./run/my_ans || break 
	# ./run/sol < "./run/test" > ./run/my_ans || break
	# ./run/ok < "./run/test" > ./run/corr_ans || break
	# diff ./run/my_ans ./run/corr_ans || break
	python3 ./check.py || break 

	echo 'ok, test'$t
done
 