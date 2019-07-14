# !/usr/dt/bin/dtksh
# !/bin/ksh
# set -x

# Requires a ksh newer than 11/16/88 because it uses floating point
# arithmetic and printf.  /usr/dt/bin/dtksh on Solaris and Digital Unix
# is such a beast, as are some vendor's ksh93 binary.
# /usr/dt/bin/dtksh on Digital Unix 4.0B appears brain dead.

float sum=0.0 usec=0.0

function doit
{
	Cmd=$1
	echo $Cmd

	Output=`$Cmd`
	echo $Output
	usec=`echo $Output | nawk '{ print $2 }'`
	(( sum+=usec ))

	return
}

function average_bw
{
	n=$1
	echo average: sum=$sum n=$1
	printf "%.1f\n\n" $(( sum/n ))
	sum=0.0
}

function average_lat
{
	n=$1
	echo average: sum=$sum n=$1
	printf "%.1f\n\n" $(( sum/n ))
	sum=0.0
}

# Measure bandwidth and latency for message passing.
##########################################################################
if [ -x bw_pipe ]
then	for xfersize in 1024 2048 4096 8192 16384 32768 65536
	do
			# 5 measurements to average
		for i in 1 2 3 4 5
		do
				# 5 iterations, 10 megabytes
			doit "bw_pipe 5 10 $xfersize"
		done
		average_bw 5
	done
	echo "*****"
fi

if [ -x bw_pxmsg ]
then
	for xfersize in 1024 2048 4096 8192 16384 32768 65536
	do
		for i in 1 2 3 4 5
		do
			doit "bw_pxmsg 5 10 $xfersize"
		done
		average_bw 5
	done
	echo "*****"
fi

if [ -x bw_svmsg ]
then
	for xfersize in 1024 2048 4096 8192 16384
	do
		for i in 1 2 3 4 5
		do
			doit "bw_svmsg 5 10 $xfersize"
		done
		average_bw 5
	done
	echo "*****"
fi

if [ -x bw_door ]
then
	for xfersize in 1024 2048 4096 8192 16384 32768 65536
	do
		for i in 1 2 3 4 5
		do
			doit "bw_door /tmp/temp.door 5 10 $xfersize"
		done
		average_bw 5
	done
	echo "*****"
fi

if [ -x bw_sunrpc_client ]
then
	./bw_sunrpc_server &
	sleep 2		# let server start and register with port mapper
	ServerPID=$!

	for xfersize in 1024 2048 4096 8192 16384 32768 65536
	do
		for i in 1 2 3 4 5
		do
			doit "bw_sunrpc_client localhost 5 10 $xfersize tcp"
		done
		average_bw 5
	done
	echo "*****"

	for xfersize in 1024 2048 4096 8192 16384 32768 65536
	do
		for i in 1 2 3 4 5
		do
			doit "bw_sunrpc_client localhost 5 10 $xfersize udp"
		done
		average_bw 5
	done
	echo "*****"

	kill -9 $ServerPID
fi

##########################################################################
if [ -x lat_pipe ]
then
	for i in 1 2 3 4 5
	do
			# 5 measurements to average, 10,000 loops
		doit "lat_pipe 10000"
	done
	echo "*****"
	average_lat 5
fi

if [ -x lat_pxmsg ]
then
	for i in 1 2 3 4 5
	do
		doit "lat_pxmsg 10000"
	done
	echo "*****"
	average_lat 5
fi

if [ -x lat_svmsg ]
then
	for i in 1 2 3 4 5
	do
		doit "lat_svmsg 10000"
	done
	echo "*****"
	average_lat 5
fi

if [ -x lat_door ]
then
	for i in 1 2 3 4 5
	do
		doit "lat_door /tmp/temp.door 10000"
	done
	echo "*****"
	average_lat 5
fi

if [ -x lat_sunrpc_client ]
then
	./lat_sunrpc_server &
	sleep 2		# let server start and register with port mapper
	ServerPID=$!

	for i in 1 2 3 4 5
	do
		doit "lat_sunrpc_client localhost 10000 tcp"
	done
	echo "*****"
	average_lat 5

	for i in 1 2 3 4 5

	do
		doit "lat_sunrpc_client localhost 10000 udp" 
	done
	echo "*****"
	average_lat 5

	kill -9 $ServerPID
fi
