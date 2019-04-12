#!/bin/sh
#FT_NBR1=\\\'?\"\\\"\'\\
#FT_NBR2=rcrdmddd
a=$(echo $FT_NBR1 | sed "s/\'/0/g" | sed 's/\\/1/g' | sed 's/\"/2/g' | sed 's/?/3/g' | sed 's/!/4/g' )
b=$(echo $FT_NBR2 | tr "mrdoc" "01234" )
echo $a + $b | xargs echo "ibase=5; obase=23;" | bc | tr "0123456789ABC" "gtaio luSnemf"
