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
#include <time.h>
#include <math.h>
#include <stdbool.h>


#define SPEED 2

/*Function prototypes*/
int init_gamepad();
void gpio_handler();
void move_paddle_up(int y, int paddle);
void move_paddle_down(int y, int paddle);
int map_buttons(int input);
vector_t *vec_normalized(vector_t *vec);
int gotdata = 0;
FILE *driver;


paddle_t player1;
paddle_t player2;

circle_t ball;


void gpio_handler(int signo){
	
	//map_buttons(getc(fp));
	printf("Enter handler\n");
	int button;	
	if(signo == SIGIO){
		printf("Got data\n");
		gotdata++;
		button = map_buttons((int)getc(driver));
		//printf("Button: %d\n", button);
	}

}


void init_ball(){
	ball.x = 100;
	ball.y = 100;
	ball.r = 5;
	ball.acc = 10;
	ball.speed.x = -5;
	ball.speed.y = 5;
	vector_t *speed = vec_normalized(&ball.speed);
	ball.speed = *speed;
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


float vec_magnitude(vector_t *v){
	return sqrt(v->x * v->x + v->y * v->y);
}

vector_t *vec_normalized(vector_t *v){
	float m = vec_magnitude(v);
	vector_t *new = (vector_t*)malloc(sizeof(vector_t));
	new->x = v->x / m;
	new->y = v->y / m;
	return new;	
}


vector_t *intersect_rectangle_circle(vector_t *rec_pos, int w, int h, circle_t *c){
	int top = rec_pos->y - c->y;
	int bottom = (rec_pos->y + h) - c->y;
	int left = rec_pos->x - c->x;
	int right  = (rec_pos->x + w) - c->x;

	bool intersecting = left <= c->r && top <= c->r && right >= -c->r && bottom >= -c->r;
	vector_t *impulse = NULL;
	if(intersecting){
		impulse = vec_normalized(&c->speed);
		//if(abs(left) < c->r && impulse->x > 0){
		//	impulse->x = -impulse->x;
		//}
		//if(abs(right) < c->r && impulse->x < 0){
		//	impulse->x = -impulse->x;
		//}

		//if(abs(top) < c->r && impulse->y > 0){
		//	impulse->y = -impulse->y;		
		//}

		//if(abs(bottom) < c->r && impulse->y < 0){
		//	impulse->y = -impulse->y;
		//}

		return vec_normalized(impulse);
	}

	return impulse;

		

	
}




void move_ball(circle_t *c){
	vector_t rec_pos, *speed;

	
	//Clear old ball
	draw_ball(c, 34);
	
	rec_pos.x = 0;
	rec_pos.y = 0;
	
	//Collision top 
	if((speed = intersect_rectangle_circle(&rec_pos, SCREEN_WIDTH, 0, c)) != NULL){
		printf("Collision TOP\n");
		c->speed = *speed;
		c->speed.y = -c->speed.y;
	}

	rec_pos.y = SCREEN_HEIGHT;
	rec_pos.x = 0;

	if((speed = intersect_rectangle_circle(&rec_pos, SCREEN_WIDTH, 0, c)) != NULL){
		printf("Collision bottom\n");
		c->speed = *speed;
		c->speed.y = -c->speed.y;
		printf("X: %f\n",c->speed.x);
		printf("Y: %f\n", c->speed.y);
	}

	rec_pos.y = 0;
	rec_pos.x = SCREEN_WIDTH;
	if((speed = intersect_rectangle_circle(&rec_pos, 0, SCREEN_HEIGHT, c)) != NULL){
		printf("Collision right\n");
		c->speed = *speed;
		c->speed.x = -c->speed.x;
	}
	
	rec_pos.y = 0;
	rec_pos.x = 0;
	if((speed = intersect_rectangle_circle(&rec_pos, 0, SCREEN_HEIGHT, c)) != NULL){
		printf("Collsion left\n");
		c->speed = *speed;
		c->speed.x = -c->speed.x;
	}
	
	

	ball.x += ball.speed.x * ball.acc;
	ball.y += ball.speed.y * ball.acc;

	

	draw_ball(c, 0xFFFF);		
}




void move_paddle(paddle_t *player, int dir){
	
	if(dir == 1){
		player->y -= MOVE_PIXELS;
		if(player->y <= 0){
			player->y = 0;
		}
		printf("Y: %d\n", player->y);

	}else if(dir == -1){
		player->y += MOVE_PIXELS;
		if(player->y > SCREEN_HEIGHT + player->height){
			player->y = SCREEN_HEIGHT;
		}
		printf("Y: %d\n", player->y);
	}
}

int map_buttons(int input){
	
	printf("Input: %d\n", input);

	switch(input){
		case 0xFD:
		//UP player 1
		printf("Move up\n");
		move_paddle(&player1, 1);
		draw_paddle(&player1, -MOVE_PIXELS);
		return 3;
		case 0xF7:
		//DOWN player 1
		printf("Move down\n");
		move_paddle(&player1, -1);
		draw_paddle(&player1, MOVE_PIXELS);
		return 4;

		case 0xDF:
		//up player 2
		move_paddle(&player2, 1);
		draw_paddle(&player2, -MOVE_PIXELS);
		return 7;

		case 0x7F:
		//down player 2
		move_paddle(&player2, -1);
		draw_paddle(&player2, MOVE_PIXELS);
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
	init_ball();
		
	draw_paddle(&player1, 0);
	draw_paddle(&player2, 0);
	draw_ball(&ball, 0xFFFF);	



	//while(1) {}	
	while(1) {
		usleep(500);
		move_ball(&ball);
	}
	
	
	
	exit(EXIT_SUCCESS);
}

