#!/bin/bash

sleep_time=0.5
min_time=0.05
max_time=1.0

# Declaro salidas
for i in {0..7}
do
    gpio mode $i out
done

# Declaro entradas
gpio mode 9 in
gpio mode 10 in

# GPIO pull-down
gpio mode 9 down
gpio mode 10 down


apagar_leds() {
    for i in {0..7}; do
        gpio write $i 0
    done
}


actualizar_botones() {

    # Botón 9: aumentar tiempo
    if [ "$(gpio read 9)" -eq 1 ]; then

        sleep_time=$(echo "$sleep_time + 0.1" | bc)

        if (( $(echo "$sleep_time > $max_time" | bc -l) )); then
            sleep_time=$max_time
        fi

        echo "Sleep time: $sleep_time"

        sleep 0.2
    fi


    # Botón 10: disminuir tiempo
    if [ "$(gpio read 10)" -eq 1 ]; then

        sleep_time=$(echo "$sleep_time - 0.1" | bc)

        if (( $(echo "$sleep_time < $min_time" | bc -l) )); then
            sleep_time=$min_time
        fi

        echo "Sleep time: $sleep_time"

        sleep 0.2
    fi
}


encender_led() {

    # Preguntar botones antes de cada LED
    actualizar_botones

    apagar_leds
    gpio write "$1" 1

    sleep "$sleep_time"
}


while true
do

    # De izquierda a derecha
    for a in {0..7}
    do
        encender_led "$a"
    done

    # De derecha a izquierda
    for a in {6..1}
    do
        encender_led "$a"
    done

done
