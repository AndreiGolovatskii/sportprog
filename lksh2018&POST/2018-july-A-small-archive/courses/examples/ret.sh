function some_useful_stuff {
	echo $(($1+1))
}
some_useful_stuff 10

s=`some_useful_stuff`
echo $s
