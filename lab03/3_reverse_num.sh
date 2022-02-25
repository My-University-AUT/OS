#!/usr/bin/bash


is_valid_number () {

    re='^[0-9]+$'
    if ! [[ $1 =~ $re ]] ; then
        echo "Invalid number"; 
        echo "please enter valid number"; 
        return 0;
    fi
    return 1;
}

reverse () {
    let num=$1;
    let rev=0;
    let sum=0;
    while [ $num -ne 0 ]; do
        let rem=$(($num % 10));

        rev=$(($rev*10 + $rem));
        num=$(($num / 10));

        sum=$(($sum + $rem));
    done
    echo "reverse of $1 is $rev"
    echo "sum of $1 is $sum"
}


while true; do
    echo "please enter number: ";
    read number;

    is_valid_number $number;
    # echo $is_valid;
    if [ $? -eq 1 ]; then
        reverse $number;
    fi
    
done
reverse $1