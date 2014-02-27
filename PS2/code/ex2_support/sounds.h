#ifndef SOUNDS_H
#define SOUNDS_H

#define A 440
#define B 247
#define C 131
#define D 294
#define E 659
#define F 87
#define SILENCE 0
#define PERIOD 48000

void testNotes(int note, int time);
void silence(int time);
void play_note(int);
void play_music(int lenght, int flag);

#endif
