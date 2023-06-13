#!/bin/bash
RESET='\033[0m'

RED='\033[00;31m'
GREEN='\033[00;32m'
YELLOW='\033[00;33m'
BLUE='\033[00;34m'
PURPLE='\033[00;35m'
CYAN='\033[00;36m'
LIGHTGRAY='\033[00;37m'

LRED='\033[01;31m'
LGREEN='\033[01;32m'
LYELLOW='\033[01;33m'
LBLUE='\033[01;34m'
LPURPLE='\033[01;35m'
LCYAN='\033[01;36m'
WHITE='\033[01;37m'

if [ -z $1 ]
then
	echo "Please specify a port between 6660 and 7000: ./test-flood-script.sh <port>"
	exit 1
fi

PORT=$1
PORT_STATUS=$(nc -w5 -z -v localhost $PORT 2>&1)
echo "Port status: ${PORT_STATUS}"

if [[ ${PORT_STATUS} != *"open"* ]]
then
	exit 1
fi

echo "Flooding port $PORT"
RESULT=""
while [[ ${PORT_STATUS} == *"open"* ]]
do
	echo "-- Connecting to port ${PORT} and registering an IRC user"
	RESULT=$(perl -e 'print "USER a a a a\r\n" . "NICK nick\r\n" . "QUIT\r\n"' | nc localhost $PORT)
	if [[ ${RESULT} == *"Welcome"* ]]
		then
			echo -e "${GREEN}OK: Got expected \"Welcome\" reply${RESET}"
			echo "${RESULT}"
		else
			echo -e "${RED}ERROR: Got unexpected reply:${RESET}"
			echo "Reply: [${RESULT}]"
	fi
	echo "-- Closed connection to port ${PORT}"
	PORT_STATUS=$(nc -w5 -z -v localhost $PORT 2>&1)
	echo "-- Checking port ${PORT} status"
	echo
done

echo "Terminating: ${PORT_STATUS}"
