#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

int *screen_values;
struct fb_copyarea rect;
FILE *fp;

void initDisplay(){	
	*fp=fopen("/dev/fb0", "rw");
	if(!fp){
		printf("Failed to open file");
		exit(EXIT_FAILURE);		
	}
	printf("File opened successfully. Awaiting read/write instructions to/from framebuffer...");
	screen_values=mmap(0, SCREEN_WIDTH*SCREEN_HEIGHT, PROT_READ | PROT_WRITE, fp, 0);
}

void fill_screen(uint16_t value){
	for(int i=0; i<SCREEN_WIDTH*SCREEN_HEIGHT; i++){
		screen_values[i]=value;
	}
	rect.dx=0;
	rect.dy=0;
	rect.width=200;
	rect.height=200;
	
	//comand driver to update display
	ioctl(fp, 0x4680, &rect);
}
