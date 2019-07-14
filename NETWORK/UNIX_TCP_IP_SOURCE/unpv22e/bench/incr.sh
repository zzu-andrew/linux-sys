#!/usr/dt/bin/dtksh
#!/bin/ksh
#set -x

# Requires a ksh newer than 11/16/88 because it uses floating point
# arithmetic and printf.  /usr/dt/bin/dtksh on Solaris and Digital Unix
# is such a beast, as are some vendor's ksh93 binary.

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

function average
{
	n=$1
	echo average: sum=$sum n=$1
	printf "%.1f\n\n" $(( sum/(n*1000000) ))
	sum=0
}

##########################################################################
float sum=0
nloop=1000000

if [ -x incr_pxmutex1 ]
then
	echo "______________________________ mutex lock; threads"
	for nthreads in 1 2 3 4 5
	do
			# 3 measurements to average
		for i in 1 2 3
		do
			doit "incr_pxmutex1 $nloop $nthreads"
		done
		average 3
	done
fi

# incr_rwlock1 uses Solaris read-write locks.
if [ -x incr_rwlock1 ]
then
	echo "______________________________ read-write lock; threads"
	for nthreads in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_rwlock1 $nloop $nthreads"
		done
		average 3
	done
fi

# incr_rwlock2 uses Digital Unix thread-independent services read-write locks.
if [ -x incr_rwlock2 ]
then
	echo "______________________________ read-write lock; threads"
	for nthreads in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_rwlock2 $nloop $nthreads"
		done
		average 3
	done
fi

if [ -x incr_pxsem1 ]
then
	echo "______________________________ Posix memory-based semaphore; threads"
	for nthreads in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_pxsem1 $nloop $nthreads"
		done
		average 3
	done
fi

if [ -x incr_pxsem2 ]
then
	echo "______________________________ Posix named semaphore; threads"
	for nthreads in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_pxsem2 $nloop $nthreads"
		done
		average 3
	done
fi

if [ -x incr_svsem1 ]
then
	echo "______________________________ System V semaphore; threads"
	for nthreads in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_svsem1 $nloop $nthreads"
		done
		average 3
	done
fi

if [ -x incr_svsem2 ]
then
	echo "______________________________ System V semaphores w/UNDO; threads"
	for nthreads in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_svsem2 $nloop $nthreads"
		done
		average 3
	done
fi

if [ -x incr_fcntl1 ]
then
	echo "______________________________ fcntl lock; threads (1 only)"
	# Cannot do fcntl locking between multiple threads.
	for nthreads in 1
	do
		for i in 1 2 3
		do
			doit "incr_fcntl1 /tmp/incr_fcntl1 $nloop $nthreads"
		done
		average 3
	done
fi

##########################################################################

if [ -x incr_pxmutex5 ]
then
	echo "______________________________ mutex lock; processes"
	for nproc in 1 2 3 4 5
	do
			# 3 measurements to average
		for i in 1 2 3
		do
			doit "incr_pxmutex5 $nloop $nproc"
		done
		average 3
	done
fi

if [ -x incr_rwlock5 ]
then
	echo "______________________________ read-write lock; processes"
	for nproc in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_rwlock5 $nloop $nproc"
		done
		average 3
	done
fi

if [ -x incr_pxsem5 ]
then
	echo "______________________________ Posix memory-based semaphore; processes"
	for nproc in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_pxsem5 $nloop $nproc"
		done
		average 3
	done
fi

if [ -x incr_pxsem6 ]
then
	echo "______________________________ Posix named semaphore; processes"
	for nproc in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_pxsem6 $nloop $nproc"
		done
		average 3
	done
fi

if [ -x incr_svsem5 ]
then
	echo "______________________________ System V semaphore; processes"
	for nproc in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_svsem5 $nloop $nproc"
		done
		average 3
	done
fi

if [ -x incr_svsem6 ]
then
	echo "______________________________ System V semaphore w/UNDO; processes"
	for nproc in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_svsem6 $nloop $nproc"
		done
		average 3
	done
fi

if [ -x incr_fcntl5 ]
then
	echo "______________________________ fcntl lock; processes"
	for nproc in 1 2 3 4 5
	do
		for i in 1 2 3
		do
			doit "incr_fcntl5 /tmp/incr_fcntl5 $nloop $nproc"
		done
		average 3
	done
fi
