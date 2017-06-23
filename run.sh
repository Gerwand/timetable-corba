#!/bin/bash

if (($# != 1)); then
	echo "Wrong number of arguments, pass num of servers"
	exit -1
fi

ORBACUS_DIR="/home/gerwand/corba/OB-4.3.3"
LIB_PATH="${ORBACUS_DIR}/lib"

srv_num=$1

killall random_provider
killall server
killall nameserv

echo "Starting nameserv"
LD_LIBRARY_PATH=${LIB_PATH} ${ORBACUS_DIR}/bin/nameserv -OAport 5001 &

sleep 5
echo "Starting servers"
	LD_LIBRARY_PATH=${LIB_PATH} ./random_provider -ORBnaming corbaloc:iiop:localhost:5001/NameService "random_provider" &
sleep 5
for ((i = 0; i < srv_num; ++i)); do
	LD_LIBRARY_PATH=${LIB_PATH} ./server -ORBnaming corbaloc:iiop:localhost:5001/NameService "genetic${i}" "random_provider" &
done
sleep 5
echo "Done"
echo "Starting client"
LD_LIBRARY_PATH=${LIB_PATH} ./client -ORBnaming corbaloc:iiop:localhost:5001/NameService genetic ${srv_num} data.in data.out 30

