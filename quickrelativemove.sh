#!/bin/bash

[ -z "$SERIALLINE" ] && export SERIALLINE=/dev/ttyUSB0

MOTOR=$2
[ -z "$MOTOR" ] && MOTOR=1

echo "C,I${MOTOR}M${1},R" > $SERIALLINE
