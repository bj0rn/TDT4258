
#define MOVE_PIXELS 5
#define PADDLE_HEIGHT 50
#define PADDLE_WIDTH 15
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

typedef struct paddle {
	int x;
	int y;
	int width;
	int height;
}paddle_t;




void initDisplay();
void fill_screen(uint16_t);
void refresh_screen();

void draw_paddle(paddle_t *paddle, int new_y);
void draw_ball(int x, int y);
