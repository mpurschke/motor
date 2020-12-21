#!/bin/sh

[ -z "$SERIALLINE" ] && export SERIALLINE=/dev/ttyUSB0

echo "C,IA1M0,R" > $SERIALLINE

