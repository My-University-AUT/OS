#!/usr/bin/bash



if [ -z $1 ] || [ -z $2 ] ||  [ -z $3 ]; then
    echo "you should enter two numbers and operand as argument";
    exit 1;
fi

re='^[+-]?[0-9]+$'
if ! [[ $1 =~ $re ]] || ! [[ $3 =~ $re ]] ; then
   echo "Invalid number"; 
   echo "please enter two number"; 
   exit 1;
fi

op_re='^[x/+-]$'
if ! [[ $2 =~ $op_re ]] ; then
   echo "Invalid operator"; 
   echo "Please enter +, -, x or / as operator"; 
   exit 1;
fi



let num_1=$1;
op=$2;
let num_2=$3;


case "$op" in
    
    "+") 
        res=$(($num_1+$num_2))
    ;;

    "-")
        res=$(($num_1-$num_2))
    ;;

    "x")
        res=$(($num_1*$num_2))
    ;;

    "/")
        res=$(($num_1/$num_2))
    ;;

esac


echo "result: $num_1 $op $num_2 = $res"