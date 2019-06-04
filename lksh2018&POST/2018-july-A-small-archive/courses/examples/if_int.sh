l=10
r=12
for ((i = 0; i <= 100; i++)) ; do
  if ((l <= i && i <= r)) ; then
    echo -n "[$i]"
  fi
done