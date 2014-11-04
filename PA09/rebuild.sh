#!/bin/bash

CC=color-gcc.pl
FILES="answer09.c main.c"
BUILDNO=0

build()
{
    BUILDNO=$(expr $BUILDNO + 1)
    clear
    $CC -Wall -Wshadow -g -Wno-unused-variable $FILES -o pa09 && \
	echo "Build #$BUILDNO successful"
}

checksum()
{
    cat $FILES | md5sum | awk '{ print $1 }'
}

MD5=
while (( 1 > 0 )) ; do
    SUM=$(checksum)
    [ "$MD5" != "$SUM" ] && MD5=$SUM && build
    sleep 0.25
done





