#!/bin/bash
SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

matr=`cat matr.txt`

echo MATRICOLA: $matr
echo PATH: 	$SCRIPTPATH
#echo inserisci matricola
#read $matr
echo 		comprimendo
zip -r $matr.zip $matr
echo 		compresso
