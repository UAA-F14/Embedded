# Orange Pi 4 Pro — Pinout (header 40 pines)

`gpioinfo` muestra las lineas como "unnamed" porque el device tree de este
kernel no registra nombres de linea. Esta tabla une los nombres de
`gpio readall` (wiringOP) con el chip/offset real que usa libgpiod.

| Pin fisico | Nombre   | GPIO (wiringOP) | Chip libgpiod | Offset |
|-----------:|----------|-----------------:|----------------|-------:|
| 3          | SDA.0    | 35               | gpiochip0      | 35     |
| 5          | SCL.0    | 34               | gpiochip0      | 34     |
| 7          | PWM0-2   | 356              | gpiochip1      | 4      |
| 8          | TXD.7    | 358              | gpiochip1      | 6      |
| 10         | RXD.7    | 359              | gpiochip1      | 7      |
| 11         | PL9      | 361              | gpiochip1      | 9      |
| 12         | PL8      | 360              | gpiochip1      | 8      |
| 13         | PL12     | 364              | gpiochip1      | 12     |
| 15         | PK9      | 329              | gpiochip0      | 329    |
| 16         | PL5      | 357              | gpiochip1      | 5      |
| 18         | PL2      | 354              | gpiochip1      | 2      |
| 19         | MOSI.3   | 130              | gpiochip0      | 130    |
| 21         | MISO.3   | 131              | gpiochip0      | 131    |
| 22         | PD23     | 119              | gpiochip0      | 119    |
| 23         | SCLK.3   | 129              | gpiochip0      | 129    |
| 24         | CE.0     | 140              | gpiochip0      | 140    |
| 26         | PE4      | 132              | gpiochip0      | 132    |
| 27         | PB5      | 37               | gpiochip0      | 37     |
| 28         | PB4      | 36               | gpiochip0      | 36     |
| 29         | PD0      | 96               | gpiochip0      | 96     |
| 31         | PD1      | 97               | gpiochip0      | 97     |
| 32         | PD5      | 101              | gpiochip0      | 101    |
| 33         | PD2      | 98               | gpiochip0      | 98     |
| 35         | PD3      | 99               | gpiochip0      | 99     |
| 36         | PD6      | 102              | gpiochip0      | 102    |
| 37         | PD4      | 100              | gpiochip0      | 100    |
| 38         | PD7      | 103              | gpiochip0      | 103    |
| 40         | PL13     | 365              | gpiochip1      | 13     |

Pines no listados (1, 2, 4, 6, 9, 14, 17, 20, 25, 30, 34, 39) son
3.3V / 5V / GND, no son GPIO.

## Regla de conversion GPIO -> chip/offset de libgpiod

- Si `GPIO < 352` -> **gpiochip0**, offset = GPIO
- Si `GPIO >= 352` -> **gpiochip1**, offset = GPIO - 352

## LED de pruebas

Actualmente conectado en **pin fisico 7** (PWM0-2, GPIO 356) ->
`gpiochip1`, offset `4`. Es el pin que usa `1GPIO/main.c`, `4Blink.c` y
`5Temp.c`.