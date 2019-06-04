sols[0]="solutions/forbidden_basic_ra"
scores[0]=10

sols[1]="solutions/forbidden_mp_greedy"
scores[1]=50

# $1, $2, .... $*
echo ${sols[1]}

echo We have ${#sols[*]} solutions, 
echo scores = ${scores[*]}

# f=a b c d 
# for solution in f ; do
# done
