#!/bin/sh

[ -z "$SERIALLINE" ] && export SERIALLINE=/dev/ttyUSB0

MOTOR=$2
[ -z "$MOTOR" ] && MOTOR=1

echo "C,IA${MOTOR}M${1},R" > $SERIALLINE

exit
