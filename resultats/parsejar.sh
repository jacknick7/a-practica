#!/bin/bash

rm parseig.txt

for FITXER in experiments-hash/hash-chain-exact-*.txt; do
	#cat ${FITXER} >> parseig.txt
	S=`sed -n '13p' ${FITXER} | awk '{print $2}'`
	E=`sed -n '14p' ${FITXER} | awk '{print $2}'`
	T1=`sed -n '15p' ${FITXER} | awk '{print $2}'`
	T2=`sed -n '18p' ${FITXER} | awk '{print $3}'`
	T3=`sed -n '19p' ${FITXER} | awk '{print $3}'`
	T4=`sed -n '20p' ${FITXER} | awk '{print $4}'`
	T1=`echo $T1 | tr . ,`
	T2=`echo $T2 | tr . ,`
	T3=`echo $T3 | tr . ,`
	T4=`echo $T4 | tr . ,`
	echo $S";"$E";"$T1";"$T2";"$T3";"$T4 >> parseig.txt
done
