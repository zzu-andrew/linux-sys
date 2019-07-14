#!/bin/sh

echo "10 readers, 0 writers"
/bin/time ./test1 -r 10 -w 0 -n 1000000 > /dev/null
/bin/time ./test1 -r 10 -w 0 -n 1000000 > /dev/null

echo "8 readers, 2 writers"
/bin/time ./test1 -r 8 -w 2 -n 1000000 > /dev/null
/bin/time ./test1 -r 8 -w 2 -n 1000000 > /dev/null

echo "6 readers, 4 writers"
/bin/time ./test1 -r 6 -w 4 -n 1000000 > /dev/null
/bin/time ./test1 -r 6 -w 4 -n 1000000 > /dev/null

echo "4 readers, 6 writers"
/bin/time ./test1 -r 4 -w 6 -n 1000000 > /dev/null
/bin/time ./test1 -r 4 -w 6 -n 1000000 > /dev/null

echo "2 readers, 8 writers"
/bin/time ./test1 -r 2 -w 8 -n 1000000 > /dev/null
/bin/time ./test1 -r 2 -w 8 -n 1000000 > /dev/null

echo "0 readers, 10 writers"
/bin/time ./test1 -r 0 -w 10 -n 1000000 > /dev/null
/bin/time ./test1 -r 0 -w 10 -n 1000000 > /dev/null
