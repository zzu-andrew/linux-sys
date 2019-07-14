#!/bin/ksh

cat > seqno <<FOO
1
FOO

ls -l seqno
cat seqno

loopfcntl 10000 &
sleep 2
loopnone 10000 &
wait

cat seqno
