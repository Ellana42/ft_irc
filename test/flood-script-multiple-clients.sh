#!/bin/bash

if [ -z $1 ]
then
	echo "Please specify a port between 6660 and 7000"
	echo "Usage: ./test-flood-script.sh <port> <password> <number_of_clients>"
	exit 1
fi
if [ -z $2 ]
then
	echo "Please specify the server connection password"
	echo "Usage: ./test-flood-script.sh <port> <password> <number_of_clients>"
	exit 1
fi

PORT=$1
PASS=$2
PORT_STATUS=$(nc -w5 -z -v localhost $PORT 2>&1)

if [[ ${PORT} -lt 6000 ]] || [[ ${PORT} -gt 7000 ]]
then
	echo "Invalid port: port must be between 6660 and 7000"
	echo "Usage: ./test-flood-script.sh <port> <number_of_clients>"
	exit 1
elif [[ ${PORT_STATUS} != *"open"* ]]
then
	echo "Port status: ${PORT_STATUS}"
	exit 1
fi

NB_CLIENTS=$(($3))
if [ -z $3 ] 
then
	echo "Please specify the number of clients to simultaneously connect to the port"
	echo "Usage: ./test-flood-script.sh <port> <password> <number_of_clients>"
	exit 1
elif [[ ${NB_CLIENTS} -lt 1 ]] || [[ ${NB_CLIENTS} -gt 10000 ]]
then
	echo "Invalid number of clients: min 1, max 10000."
	echo "Usage: ./test-flood-script.sh <port> <password> <number_of_clients>"
	exit 1
fi

while [[ ${NB_CLIENTS} -ne 0 ]]
do
	echo
	echo "-- Connecting a new client #${NB_CLIENTS}"
	echo "-- Registering IRC client with nickname: nick_${NB_CLIENTS}"
	SEND_IRC_COMMANDS="print \"PASS ${PASS}\r\n\" . \"USER a a a a\r\n\" . \"NICK nick_${NB_CLIENTS}\r\n\""
	perl -e "$SEND_IRC_COMMANDS" | timeout -k 1 10s nc localhost $PORT &>/dev/null &
	NB_CLIENTS=$((${NB_CLIENTS} - 1))
done

wait
echo
echo "-- Closed all client connections"
