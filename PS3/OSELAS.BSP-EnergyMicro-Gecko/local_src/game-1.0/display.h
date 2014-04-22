#include <stdint.h>


#define MOVE_PIXELS 20
#define PADDLE_HEIGHT 50
#define PADDLE_WIDTH 15
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

typedef struct paddle {
	int x;
	int y;
	int width;
	int height;
	int id;
}paddle_t;


typedef struct vector{
	float x;
	float y;
}vector_t;


typedef struct circle {
	int x;
	int y;
	int r;
	int acc;
	vector_t speed;
}circle_t;


typedef struct pixel{
	uint8_t pix[4];
}pixel_t;

typedef struct image{
	int height;
	int width;
	pixel_t *pixel;

}image_t;


typedef struct {
	unsigned int r : 5;
	unsigned int g : 6;
	unsigned int b : 5;
	unsigned int a : 8;
	
}color_t;

void draw_text(char *matrix);

void draw_image(image_t *image);
image_t *load_image(int fp, int height, int width);
void initDisplay();
void fill_screen(uint16_t);
void refresh_screen();

void draw_paddle(paddle_t *paddle, int new_y, int color);
void draw_ball(circle_t *c, int color);

int *test_draw_ball(circle_t *c, int color);
void refresh_ball(circle_t *c, int *matrix, int color);

void draw_filled_circle(circle_t *c, int color);
