#!/usr/bin/bash


first () {
    for i in $(seq 1 5); do
        for j in $(seq 1 $i); do
            echo -n $i
        done
        echo;
    done
}

second () {
    for i in $(seq 1 6); do
        for k in $(seq 1 $((6-$i)));do
            echo -n " ";
        done
        for j in $(seq 1 $i); do
            echo -n "* ";
        done
        echo
    done

    for i in $(seq 1 6); do
        for k in $(seq 1 $(($i - 1)));do
            echo -n " ";
        done
        for j in $(seq 1 $((6 - $i + 1))); do
            echo -n "* ";
        done
        echo
    done
}

third () {

    for i in {1..5}; do
        for j in $(seq 1 $(($i - 1))); do
            echo -n "| "
        done
        echo "|_";

    done
}

print () {

    
    case "$1" in
        "1") 
            first
        ;;

        "2")
            second
        ;;

        "3")
            third
        ;;
    esac

}


while true; do
    echo "Please enter number between 1 to 3"
    read number
    re='^[123]$'
    if [[ $number =~ $re ]]; then
        print $number
    else
        echo "Invalid number";
    fi

done