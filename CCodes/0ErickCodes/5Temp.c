#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    system("gpio mode 2 out");
    system("gpio mode 2 in");

    char estado[100];
    while(1){
        FILE *archivo;
        archivo = popen("gpio read 2", "r");
        fgets(estado,sizeof(estado),archivo);
        pclose(archivo);
        printf("%s", estado);

        if(strstr(estado,"lo") != NULL)
            system("gpio write 2 1");
            
        else
        {
            system("gpio write 2 0");
        }
        usleep(100000); // 100 ms 
    }
    return 0;
}
