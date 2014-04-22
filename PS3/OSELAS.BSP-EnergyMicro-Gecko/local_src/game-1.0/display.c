#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#include "display.h"

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


void draw_image(image_t *image){
	for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
		color_t col;
		col.r = image->pixel[i].pix[0];
		col.g = image->pixel[i].pix[1];
		col.r = image->pixel[i].pix[2];
		screen_values[i] = (uint16_t)col; 
	}
}


void refresh_screen(){
	ioctl(fp, 0x4680, &rect);
}



void draw_paddle(paddle_t *p, int new_y, int color){		

	for(int i = p->x; i < p->x + p->width; i++){
		for(int j = p->y; j < p->y + p->height; j++){
			screen_values[i + j * SCREEN_WIDTH] = color; 
		}
	}
	
	if(new_y > 0){
		//Moving down
		for(int i = p->x; i < p->x + p->width; i++){
			for(int j = (p->y - new_y); j <  p->y; j++) {
				screen_values[i + j * SCREEN_WIDTH] = 34;
			}
		}

	
	}else if(new_y < 0){
		//Moving up
		for(int i = p->x; i < p->x + p->width; i++){
			for(int j = (p->y + p->height); j < (p->y + p->height - new_y); j++){
				screen_values[i + j * SCREEN_WIDTH] = 34;
			}
		}
	}

}


void static set_pixel(int x, int y, int color){
	screen_values[x + y * SCREEN_WIDTH] = color;
}


/*
void draw_ball(circle_t *c, int color){
	//Change algorithm if the simple algorithm is to slow
	int r2 = c->r * c->r;
	for(int x = -c->r; x <= c->r; x++){
		int y = (int)sqrt(r2 - x*x) + 0.5;
		set_pixel(c->x + x, c->y + y, color);
		set_pixel(c->x + x, c->y -y, color);	
	}

	refresh_screen();	

	return;	
}
*/


image_t *load_image(int fp, int height, int width){
	lseek(fp, IMG_HEADER_LENGHT, SEEK_SET);

	int num_pix = height * width;

	image->height = height;
	image->width = width;


	image_t *image = (image_t *)malloc(sizeof(image_t));
	image->pixel = (pixel_t *)malloc(sizeof(pixel_t) * num_pix);


	for(int i = 0; i < num_pix; i++){
		for(int j = 0; j < 3; j++){
			char c;
			read(fp, &c, 1);
			image->pixel[i].pix[j] = c;
		} 
	}	

	close(fp);

	return image;
}





void draw_filled_circle(circle_t *c, int color){
	int x = c->r;
	int y = 0;
	int xchange = 1 - (c->r << 1);
	int ychange = 0;
	int radius_error = 0;


	while(x >= y){
		
		for(int i = c->x - x; i <= c->x + x; i++){
			set_pixel(i, c->y+y, color);
			set_pixel(i, c->y-y, color);
		}

		for(int i = c->x - y; i <= c->x + y; i++){
			set_pixel(i, c->y + x, color);
			set_pixel(i, c->y - x, color);
		}
		
		y++;
		radius_error += ychange;
		ychange += 2;
		
		if(((radius_error << 1) + xchange) > 0){
			x--;
			radius_error += xchange;
			xchange += 2;
		}
		
	}
}

void draw_ball(circle_t *c, int color){
	int x, y, r2;

	r2 = c->r * c->r;

	set_pixel(c->x, c->y + c->r, color);
	set_pixel(c->x, c->y - c->r, color);
	set_pixel(c->x + c->r, c->y, color);
	set_pixel(c->x - c->r, c->y, color);

	y = c->r;
	x = 1;
	y = (int)sqrt(r2 - 1) + 0.5;
	
	while(x < y){
		set_pixel(c->x + x, c->y + y, color);
		set_pixel(c->x + x, c->y - y, color);
		set_pixel(c->x - x, c->y + y, color);
		set_pixel(c->x - x, c->y - y, color);
		
		set_pixel(c->x + y, c->y + x, color);
		set_pixel(c->x + y, c->y - x, color);
		set_pixel(c->x - y, c->y + x, color);
		set_pixel(c->x - y, c->y - x, color);

		x+=1;
		y = (int) sqrt(r2 - x * x) + 0.5; 
	}

	if(x == y){
		set_pixel(c->x + x, c->y + y, color);
		set_pixel(c->x + x, c->y - y, color);
		set_pixel(c->x - x, c->y + y, color);
		set_pixel(c->x - x, c->y - y, color);
	}

//	refresh_screen();
}


void refresh_ball(circle_t *c,int *matrix,  int color){
	return;

}



