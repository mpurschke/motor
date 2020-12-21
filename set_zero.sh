#!/bin/sh

[ -z "$SERIALLINE" ] && export SERIALLINE=/dev/ttyUSB0

echo "C,IA1M-0,R" > $SERIALLINE

