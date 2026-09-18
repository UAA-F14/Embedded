#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    system("gpio mode 2 in");

    // Test Pins 0-9 as INPUTS
    char cmd[100];
    for(int i=0; i<26; i++){
        snprintf(cmd, sizeof(cmd), "gpio mode %d out", i);
        system(cmd);
        sleep(1);
        snprintf(cmd, sizeof(cmd), "gpio mode %d up", i);
        system(cmd);
        sleep(1);
    }


    while(1){
        system("gpio write 2 1");
        sleep(1);
        system("gpio write 2 0");
        sleep(1);

    }
    return 0;

}

/*
    system("gpio mode 2 out");
    while(1){
        system("pinctl set 17 dh");
        sleep(1);
        system("pinctl set 17 dl");
        sleep(1);
    }

*/