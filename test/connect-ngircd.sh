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
	echo "Usage: ./connect.sh <port> <nickname>"
	exit 1
fi
if [ -z $2 ]
then
	echo "Please specify a nickname"
	echo "Usage: ./connect-ngircd.sh <port> <nickname>"
	exit 1
fi

PORT=$1
NICK=$2
PORT_STATUS=$(nc -w5 -z -v localhost $PORT 2>&1)

if [[ ${PORT} -lt 6660 ]] || [[ ${PORT} -gt 7000 ]]
then
	echo "Invalid port: port must be between 6660 and 7000"
	echo "Usage: ./connect.sh <port> <nickname>"
	exit 1
elif [[ ${PORT_STATUS} != *"open"* ]]
then
	echo "Port status: ${PORT_STATUS}"
	exit 1
fi

echo "USER a a a a" > /tmp/irc_commands.tmp
echo "NICK ${NICK}" >> /tmp/irc_commands.tmp
cat /tmp/irc_commands.tmp
cat /tmp/irc_commands.tmp - | ncat -C localhost $PORT

rm -f /tmp/irc_commands.tmp
