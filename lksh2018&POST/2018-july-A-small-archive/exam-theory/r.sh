for f in *.tex ; do 
  name=${f/.*}
  rm $name.{toc,log,out,aux}
  xelatex $f || exit
  xelatex $f >/dev/null || exit
  rm $name.{toc,log,out,aux}
done
