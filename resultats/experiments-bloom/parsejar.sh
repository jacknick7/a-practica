#!/bin/bash

rm parseig-v1.txt

ENTRADA=`cat bloom-v1.txt`

LINIA2=""

while read -r LINIA; do
	if [[ $LINIA == "K:"* ]]; then
		VAR=`echo $LINIA | awk '{print $2}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "JOC:"* ]]; then
		VAR=`echo $LINIA | awk '{print $2}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Temps per generar la taula de bloom:"* ]]; then
		VAR=`echo $LINIA | awk '{print $8}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Temps per fer totes les cerques:"* ]]; then
		VAR=`echo $LINIA | awk '{print $7}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Numero de fals positius:"* ]]; then
		VAR=`echo $LINIA | awk '{print $5}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "Numero total de positius:"* ]]; then
		VAR=`echo $LINIA | awk '{print $5}'`
		LINIA2="$LINIA2$VAR;"
	elif [[ $LINIA == "#&#&#&#&#" ]]; then
		LINIA2=`echo $LINIA2 | tr . ,`
		LINIA2=${LINIA2%?}
		echo $LINIA2 >> parseig-v1.txt
		LINIA2=""
	fi
done <<< "$ENTRADA"
