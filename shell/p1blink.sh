


gpio mode 2 out

while true
do
gpio write 2 0
echo "Apagando..." 
sleep 0.5
gpio write 2 1
echo "Encendiendo..."
sleep 0.5
done
