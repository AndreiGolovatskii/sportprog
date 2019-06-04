#!/bin/bash

for f in conspect.tex; do 
  name=${f/.*}
  rm -f $name.{toc,log,out,aux}
  pdflatex -shell-escape $name.tex || exit #>/dev/null || exit
  pdflatex -shell-escape $name.tex >/dev/null || exit
  rm -f $name.{toc,log,out,aux,dvi,pyg}
done

