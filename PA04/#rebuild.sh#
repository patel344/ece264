#!/bin/bash

# The source file we are compiling
SOURCE_F=""

usage()
{
    cat <<EOF

  Usage: $(basename $0) [echo|cat|grep] args...

EOF
}

# Parse command line arguments
(( $# == 0 )) && usage && exit 1
if [ "$1" == "echo" ] ; then 
    SOURCE_F="echo-lite.c"
elif [ "$1" == "cat" ] ; then 
    SOURCE_F="cat-lite.c"
elif [ "$1" == "grep" ] ; then 
    SOURCE_F="grep-lite.c"
elif [ "$1" == "--help" ] ; then 
    usage
    exit 0
else 
    echo "Invalid input: $1"
    usage 
    exit 1
fi

# Remove argv[1], and left-shift all the arguments by one
shift

RAN=0
gcc -Wall -Wshadow -g $SOURCE_F && \
    RAN=1 && \
    valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log ./a.out "$@" 

if (( RAN == 1 )) ; then
# Leave a space before printing valgrind summary line
    echo
    cat memcheck.log | grep "ERROR SUMMARY" | tail -n 1
fi
