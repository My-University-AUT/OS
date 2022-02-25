#!/usr/bin/bash


if [ -z $1 ] || [ -z $2 ] ; then
    echo "you should enter two numbers as argument";
    exit 1;
fi

re='^[+-]?[0-9]+$'
if ! [[ $1 =~ $re ]] || ! [[ $2 =~ $re ]] ; then
   echo "please enter two number"; 
   exit 1;
fi


let num_1=$1;
let num_2=$2;

echo "sum of numbers is $(($num_1 + $num_2))"

if [ $num_1 -gt $num_2 ]; then
    echo "$num_1 is greather that $num_2";
elif [ $num_2 -gt $num_1 ]; then
    echo "$num_2 is greather that $num_1";
fi