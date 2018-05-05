#!/bin/bash

rm parseig-v1.txt

ENTRADA=`cat binary-v1.txt`

LINIA2=""

while read -r LINIA; do
	if [[ $LINIA == "K:"* ]]; then
		VAR=`echo $LINIA | awk '{print $2}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "JOC:"* ]]; then
		VAR=`echo $LINIA | awk '{print $2}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Numero comparacions per ordenar el diccionari:"* ]]; then
		VAR=`echo $LINIA | awk '{print $7}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Temps per ordenar el diccionari:"* ]]; then
		VAR=`echo $LINIA | awk '{print $6}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Numero comparacions total de les cerques:"* ]]; then
		VAR=`echo $LINIA | awk '{print $7}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Temps per fer totes les cerques:"* ]]; then
		VAR=`echo $LINIA | awk '{print $7}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "#&#&#&#&#" ]]; then
		LINIA2=`echo $LINIA2 | tr . ,`
		LINIA2=${LINIA2%?}
		echo $LINIA2 >> parseig-v1.txt
		LINIA2=""
	fi
done <<< "$ENTRADA"
