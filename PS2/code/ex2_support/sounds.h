#ifndef SOUNDS_H
#define SOUNDS_H
#include <stdbool.h>


#define A 200
#define B 400
#define C 600
#define D 800
#define E 1000
#define F 1200
#define G 1400
#define H 1600

#define SILENCE 0
#define PERIOD 48000

extern bool iterate;
extern int pos;
extern int test[];

void testNotes(int note, int time);
void silence(int time);
void play_note(int);
void play_music(int lenght, int flag);
void testSawtooth(int note, int time);
void play_piano();

#endif
