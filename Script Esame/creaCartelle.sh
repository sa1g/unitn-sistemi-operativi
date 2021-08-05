#!/bin/bash
SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"


echo $SCRIPTPATH
echo inserisci matricola
read matr;
matr=000$matr
echo creo file matricola
echo $matr > matr.txt

echo quanti esercizi sono?
read max;
n=1;

mkdir -p $SCRIPTPATH/$matr
cd $matr
while [ "$n" -le "$max" ]; do
  mkdir "$SCRIPTPATH/$matr/$matr.0$n"
  n=`expr "$n" + 1`;
done

