#include "sounds.h"
#include "efm32gg.h"
#include <stdint.h>

#define SAMPLING_FEEQUENCY 48000

int duration=0;
int play_duration;
int tone;

int test[] = {A, B, C, D, E, F};

void play_note(int note){
	int sampling = SAMPLING_FREQUENCY/note;
	int16_t amplitude;
	
	if(duration >= sampling/2){
		amplitude = 2000;
	}
	else{
		amplitude = -2000;
	}
	*DAC_CH0DATA = amplitude;
	*DAC_CH0DATA = amplitude;
	
	
	duration++;
	if(duration >= sampling){
		duration = 0;
	}
}



void play_music(int notes[], int song_lenght, int duration_time){
	for(int i = 0; i < song_length; i++){
		for(int j = 0; j < 4000000; j++); /* Wait */
		tone = notes[i];
	}
	
}









