#!/usr/bin/bash


echo_file_lines () {

    let head_line=$1;
    let tail_line=$2;
    input=$3;

    let counter=0;
    while IFS= read -r line
    do
        if [ $counter -ge $head_line ] && [ $counter -le $tail_line ]; then
            echo "$line";
        fi
        counter=$(($counter +1));
    done < "$input"
}


# input="test_file.txt"


if [ -z $1 ] || [ -z $2 ] || [ -z $3 ]; then
    echo "you should enter two numbers and file name";
    exit 1;
fi

# input=$3

re='^[0-9]+$'
if ! [[ $1 =~ $re ]] || ! [[ $2 =~ $re ]] ; then
   echo "Invalid number"; 
   echo "please enter two number"; 
   exit 1;
fi

echo_file_lines $1 $2 $3