#include <stdio.h>

int main(void){
	FILE *archivo;
	int temperatura;
	archivo=fopen("/sys/class/thermal/thermal_zone0/temp","r");
	if(archivo == NULL){
		printf("No se pudo leer el archivo\n");
		return 1;
	}
	if(fscanf(archivo,"%d",&temperatura)!=1){
		printf("Error: no se puede leer la temperatura\n");
		fclose(archivo);
		return 1;
	}
	fclose(archivo);
	printf("Temperatura :%.2f C\n",temperatura/1000.0);
	return 0;
}
