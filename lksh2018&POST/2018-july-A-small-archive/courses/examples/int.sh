a=10
echo $a
let a=$a+1
echo $((a+1))
echo $[$a+1]
#if [[ $a < 2 ]] ; then # as strings
# gt, lt, ge, le, ne, eq
if [[ $a -lt 2 ]] ; then # as integers
	echo less
fi