#include <stdio.h>
#include <unistd.h>

int main(void){
	for(int i=0; i<10; i++){
		sleep(1);
		printf("Contador %d \n",i);
		//sleep(1);
	}
	return 0;
}
