#!/bin/bash 



DBDIR=`pwd`



./configure --prefix=${DBDIR}/lib

make install prefix=${DBDIR}/lib


cp ./lib/lib/libsqlite3.a ./../libsqlite3.a 
cp -rf ./lib/include ./../






