#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

#include <display.h>

uint16_t *screen_values;
struct fb_copyarea rect;
struct fb_var_screeninfo screen_info;
int fp;

int screensize_bytes;

void initDisplay(){	
	
	rect.dx = 0;
	rect.dy = 0;
	rect.width = 320;
	rect.height = 240;


	fp = open("/dev/fb0", O_RDWR);
	if(!fp){
		printf("Failed to open file");
		exit(EXIT_FAILURE);		
	}
	printf("File opened successfully. Awaiting read/write instructions to/from framebuffer...\n");
	
	//get screen info 
	if(ioctl(fp, FBIOGET_VSCREENINFO, &screen_info) == -1){
		printf("Error: failed to get screen info\n");
		return -1;
	} 

	screensize_bytes = (SCREEN_WIDTH * SCREEN_HEIGHT) * screen_info.bits_per_pixel/8;

	screen_values =(uint16_t*) mmap(NULL, screensize_bytes, PROT_READ | PROT_WRITE, MAP_SHARED, fp, 0);
}

void fill_screen(uint16_t value){
	for(int i=0; i<SCREEN_WIDTH*SCREEN_HEIGHT; i++){
		screen_values[i]=value;
	}
	
	//comand driver to update display
	ioctl(fp, 0x4680, &rect);
}


void refresh_screen(){
	ioctl(fp, 0x4680, &rect);
}


static void clean_paddle_path(paddle_t *p, int remove_y){
	for(int i = p->x; i < p->x + p->width; i++){
		for(int j = p->y + length; j < p->y 
	}
}


void draw_paddle(paddle_t *p, int new_y){		

	printf("Create paddle\n");
	for(int i = p->x; i < p->x + p->width; i++){
		for(int j = p->y; j < p->y + p->height; j++){
			screen_values[i + j * SCREEN_WIDTH] = 0xFFFF; 
		}
	}
	
	if(new_y > 0){
		//Moving down

	
	}else if(new_y < 0){
		//Moving up
		for(int i = p->x; i < p->x + p->width; i++){
			for(int j = p->y + p->height; j < new_y; j++){
				screen_values[i + j * SCREEN_WIDTH] = 34;
			}
		}
	}

	refresh_screen();
}


void draw_ball(int x, int y){
	return;	
}




