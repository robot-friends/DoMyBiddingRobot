#!/usr/bin/env sh

while IFS= read -r line; do
	echo $line
	wget -O- "http://robot.evilsciencewizard.com/set/$line" &>/dev/null || echo "ERROR $line"
done
