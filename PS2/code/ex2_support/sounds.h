#ifndef SOUNDS_H
#define SOUNDS_H
#include <stdbool.h>
//#include "melodies.h"

#define A 200
#define B 400
#define C 600
#define D 800
#define E 1000
#define F 1200
#define G 1400
#define H 1600
#define I 1800
#define J 2000
#define K 2200
#define L 2400
#define M 2600
#define N 2800
#define O 3000

#define SILENCE 0
#define PERIOD 32768

extern bool iterate;
extern int pos;

struct tone{
	int note, time;
};

void testNotes(int note, int time);
void silence(int time);
void play_note(int);
void play_music(int lenght, int flag);
void testSawtooth(int note, int time);
void select_melodies();
void initSound();
void initPos();
void playSong(struct tone melody[], int size);

#endif
