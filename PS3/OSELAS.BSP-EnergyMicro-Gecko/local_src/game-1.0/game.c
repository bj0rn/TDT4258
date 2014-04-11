#include <stdio.h>
#include <stdlib.h>
#include "display.h"

int main(int argc, char *argv[])
{
	printf("Hello World, I'm game or am I ?!\n");
	
	FILE *fp;
	
	fp = fopen("/dev/gamepad", "r");
	
	char res;
	
	while(1) {
		res = getc(fp);
		printf("test: %d\n", (int)res); 
	}
	
	initDisplay();
	fill_screen(34);
	
	exit(EXIT_SUCCESS);
}

