#ifndef _POSIX_C_SOURCE 
#define _POSIX_C_SOURCE 1
#define _GNU_SOURCE 1 
#endif

#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>

/*Function prototypes*/
int init_gamepad();
void gpio_handler();
void move_paddle_up(int y, int paddle);
void move_paddle_down(int y, int paddle);

int gotdata = 0;
FILE *fp;


typedef struct paddle {
	int xpos;
	int ypos;
	int width;
	int height;
}paddle_t;


void gpio_handler(int signo){
	
	printf("Enter handler\n");

}


void move_paddle_down(int y, int paddle){
	
}


int init_gamepad(){
	
	printf("Init gamepad \n");

	fp = fopen("/dev/gamepad", "rb");
	int oflags;
	int err;	
	//struct sigaction action;

	//memset(&action, 0, sizeof(action));
	//action.sa_handler = &gpio_handler;
	//action.sa_flags = 0;
	//sigaction(SIGIO, &action, NULL);
	
	if(signal(SIGIO, &gpio_handler) == SIG_ERR){
		printf("ERROR\n");
	}
	
        if((err = fcntl(fileno(fp), F_SETOWN, getpid())) == -1){
		printf("ERROR: 1\n");
	}


	if((oflags = fcntl(fileno(fp), F_GETFL)) == -1){
		printf("ERROR: 2\n");
	}


	if((err = fcntl(fileno(fp), F_SETFL, oflags | FASYNC)) == -1){
		printf("ERROR: 3 \n");
	}

	return 0;	
}



int main(int argc, char *argv[])
{
	
	init_gamepad();	

	//FILE *fp;
	
	//fp = fopen("/dev/gamepad", "r");
	
	//char res;
	
	//while(1) {
	//	if(!gotdata){
	//		continue;
	//	}
		
	//	res = getc(fp);
	//	printf("test: %d\n", (int)res); 
	//}
	
	initDisplay();
	
	
    	fill_screen(34);
	
	create_paddle(0, 0, 15, 50);
	
		//printf("Res: %d\n", res);
		//gotdata = 0;	
			
	//}	
	exit(EXIT_SUCCESS);
}

