#!/bin/sh
#count all n-gram of n
if [ $# -ne 1 ]
then
   echo "please input filename"
   exit
fi
maxwordlength=9
datafile=$1
for ((i=1;i<=${maxwordlength};i++))
do
    ./ngram_count.py ${datafile} $i
    echo "process gram "${i}"success !!"
done

cat ${datafile}.gram-*> ${datafile}.count
rm ${datafile}.gram-*
