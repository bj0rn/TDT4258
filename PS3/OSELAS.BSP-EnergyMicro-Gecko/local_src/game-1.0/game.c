#include <stdio.h>
#include <stdlib.h>

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

	exit(EXIT_SUCCESS);
}
