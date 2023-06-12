#!/bin/bash

perl -e 'print "USER a a a a\r\n" . "NICK nick\r\n" . "QUIT\r\n"' | nc localhost 6667
