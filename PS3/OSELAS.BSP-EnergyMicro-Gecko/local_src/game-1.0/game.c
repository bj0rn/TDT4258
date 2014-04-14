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



#define PADDLE_HEIGHT 50
#define PADDLE_WIDTH 15
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320 

/*Function prototypes*/
int init_gamepad();
void gpio_handler();
void move_paddle_up(int y, int paddle);
void move_paddle_down(int y, int paddle);
int map_buttons(int input);
int gotdata = 0;
FILE *driver;



/* Structures */

typedef struct paddle {
	int x;
	int y;
	int width;
	int height;
}paddle_t;

paddle_t player1;
paddle_t player2;


void gpio_handler(int signo){
	
	//map_buttons(getc(fp));
	printf("Enter handler\n");
	int button;	
	if(signo == SIGIO){
		printf("Got data\n");
		gotdata++;
		button = map_buttons((int)getc(driver));
		printf("Button: %d\n", button);
	}

}




void init_paddle(){
	player1.x = 0; 
	player1.y = 100;
	player1.width = PADDLE_WIDTH;
	player1.height = PADDLE_HEIGHT;

	player2.x = SCREEN_WIDTH - PADDLE_WIDTH;
	player2.y = 100;
	player2.width = PADDLE_WIDTH; 
	player2.height = PADDLE_HEIGHT; 
}


void move_paddle(paddle_t *player, int dir){
	
	if(dir == 1){
		player->y -= 5;
		if(player->y <= 0){
			player->y = 0;
		}
		printf("Y: %d\n", player->y);

	}else if(dir == -1){
		player->y += 5;
		if(player->y > SCREEN_HEIGHT + player->height){
			player->y = SCREEN_HEIGHT;
		}
		printf("Y: %d\n", player->y);
	}
}

int map_buttons(int input){
	
	printf("Input: %d\n", input);

	switch(input){
		case 0xFE:
		//LEFT player 1
		return 1;
		
		case 0xFB:
		//RIGHT player 1
		return 2;
		case 0xFD:
		//UP player 1
		printf("Move up\n");
		move_paddle(&player1, 1);
		create_paddle(player1.x, player1.y, player1.width, player1.height);
		return 3;
		case 0xF7:
		//DOWN player 1
		printf("Move down\n");
		move_paddle(&player1, -1);
		create_paddle(player1.x, player1.y, player1.width, player1.height);
		return 4;

		case 0xEF:
		//Left player 2
		return 5;

		case 0xBF:
		//Right player 2
		return 6;


		case 0xDF:
		//up player 2
		move_paddle(&player2, 1);
		create_paddle(player2.x, player2.y, player2.width, player2.height);
		return 7;

		case 0x7F:
		//down player 2
		move_paddle(&paddle2, -1);
		create_paddle(player2.x, player2.y, player2.width, player2.height);
		return 8;
		
	}
	return 0;		
}


int init_gamepad(){
	
	printf("Init gamepad \n");

	driver = fopen("/dev/gamepad", "rb");
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
	
        if((err = fcntl(fileno(driver), F_SETOWN, getpid())) == -1){
		printf("ERROR: 1\n");
	}


	if((oflags = fcntl(fileno(driver), F_GETFL)) == -1){
		printf("ERROR: 2\n");
	}


	if((err = fcntl(fileno(driver), F_SETFL, oflags | FASYNC)) == -1){
		printf("ERROR: 3 \n");
	}

	return 0;	
}



int main(int argc, char *argv[])
{
	init_gamepad();
	initDisplay();
	fill_screen(34);
	init_paddle();
		
	create_paddle(player1.x, player1.y, player1.width, player1.height);
	create_paddle(player2.x, player2.y, player2.width, player2.height);	



	//while(1) {}	
	while(1) {
	}
	
	
	
	exit(EXIT_SUCCESS);
}

