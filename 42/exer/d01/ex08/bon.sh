#!/bin/sh
echo $( ldapsearch -Q sn | grep sn: | grep -i bon | wc -l ) 
