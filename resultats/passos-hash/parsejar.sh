#!/bin/bash

rm parseig.txt

ENTRADA=`cat hash-open-v1.txt`

LINIA2=""

while read -r LINIA; do
	if [[ $LINIA == "K:"* ]]; then
		VAR=`echo $LINIA | awk '{print $2}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "JOC:"* ]]; then
		VAR=`echo $LINIA | awk '{print $2}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Salts:"* ]]; then
		VAR=`echo $LINIA | awk '{print $2}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Temps:"* ]]; then
		VAR=`echo $LINIA | awk '{print $2}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Temps total:"* ]]; then
		VAR=`echo $LINIA | awk '{print $3}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Temps trobats:"* ]]; then
		VAR=`echo $LINIA | awk '{print $3}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Temps no trobats:"* ]]; then
		VAR=`echo $LINIA | awk '{print $4}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "#&#&#&#&#" ]]; then
		LINIA2=`echo $LINIA2 | tr . ,`
		LINIA2=${LINIA2%?}
		echo $LINIA2 >> parseig.txt
		LINIA2=""
	fi
done <<< "$ENTRADA"
