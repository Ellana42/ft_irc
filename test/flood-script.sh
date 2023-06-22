#!/bin/bash
RESET='\033[0m'

RED='\033[00;31m'
GREEN='\033[00;32m'
YELLOW='\033[00;33m'
BLUE='\033[00;34m'
PURPLE='\033[00;35m'
CYAN='\033[00;36m'

if [ -z $1 ]
then
	echo "Please specify a port between 6660 and 7000"
	echo "Usage: ./test-flood-script.sh <port>"
	exit 1
fi

PORT=$1
PORT_STATUS=$(nc -w5 -z -v localhost $PORT 2>&1)

if [[ ${PORT} -lt 6660 ]] || [[ ${PORT} -gt 7000 ]]
then
	echo "Invalid port: port must be between 6660 and 7000"
	echo "Usage: ./test-flood-script.sh <port>"
	exit 1
elif [[ ${PORT_STATUS} != *"open"* ]]
then
	echo "Port status: ${PORT_STATUS}"
	exit 1
fi

echo "Flooding port $PORT"
RESULT=""
declare -i COUNT=0
while [[ ${PORT_STATUS} == *"open"* ]]
do
	(( COUNT++))
	echo -e "${CYAN}------------------ Connection ${COUNT}${RESET}"
	echo "-- Connecting to port ${PORT}"
	echo -n "-- Registering IRC client: " 
	RESULT=$(perl -e 'print "PASS pass\r\n" . "USER a a a a\r\n" . "NICK nick\r\n"' | timeout -k 0.5 0.5s nc localhost $PORT)
	if [[ ${RESULT} == *"Welcome"* ]]
		then
			echo -e "${GREEN}OK: Got expected \"Welcome\" reply${RESET}"
			echo -e "${CYAN}${RESULT}${RESET}"
		else
			echo -e "${RED}ERROR: Got unexpected reply:${RESET}"
			echo "Reply: [${RESULT}]"
	fi
	echo "-- Closed connection to port ${PORT}"
	PORT_STATUS=$(nc -w5 -z -v localhost $PORT 2>&1)
	echo -n "-- Checking port ${PORT} status: "
	if [[ ${PORT_STATUS} == *"open"* ]]
		then
			echo -e "${GREEN}OK${RESET}"
		else
			echo -e "${RED}KO${RESET}"
	fi
	echo
done

echo "Terminating: ${PORT_STATUS}"
