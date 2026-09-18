#!/bin/bash

BOTON=9
LED=0

gpio mode $BOTON in
gpio mode $LED out
gpio mode $BOTON down
while true
do
	estado=$(gpio read $BOTON)

	if [[ $estado == 1 ]]; then
		gpio write $LED 1
		echo "LED encendido"
	else 
		gpio write $LED 0
		echo "LED apagado"
	fi
	sleep 0.1
done
