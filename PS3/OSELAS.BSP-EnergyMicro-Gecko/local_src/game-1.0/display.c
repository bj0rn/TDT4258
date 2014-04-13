#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

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


void create_paddle(int x, int y, int width, int length){ 
	for(int i = x; i < width; i++){
		for(int j = y; j < lenght; j++){
			screen_values[i + j * width] = 0xFFFF; 
		}

	refresh_screen();
}


void create_ball(int x, int y){
	
}




