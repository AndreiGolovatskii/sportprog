output_dir=solutions
rm -rf $output_dir
mkdir $output_dir

cnt=0
for f in *.cpp ; do
	cnt=$(($cnt+1))
	# cat optimization.h && 
	(cat optimization.h && sed -e "/optimization.h/d" $f) > $output_dir/${f:0:1}$cnt.cpp
done
