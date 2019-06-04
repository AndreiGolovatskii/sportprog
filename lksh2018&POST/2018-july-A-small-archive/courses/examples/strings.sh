#!/bin/bash

str="abcdcdef/"
echo $str
echo ${str:0:-1}
echo ${str:3:1}
echo ${str/d/cccccccccccccccccccc}
echo ${#str}

echo ${str#*cd}  # part after first "cd"
echo ${str##*cd} # get part after last 'cd'
echo ${str%cd*}  # get part before last 'cd'
echo ${str%%cd*} # get part before first 'cd'

function compile {
	if [ "$1" == "" ] ; then
		echo "Usage: <filename>"
		exit 1
	fi
	g++ $1.cpp -o $1 || exit 1
}

#compile 
for f in *.cpp ; do 
	echo $f abc
	echo ${f%.*}
	echo ${f:0:-4}
	compile ${f%.*}
done

# echo `echo "$f" | sed "s/ \(.*\)//g"` # get the first word in string f
