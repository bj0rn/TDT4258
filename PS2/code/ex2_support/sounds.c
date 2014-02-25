#include "sounds.h"
#include "efm32gg.h"
#include <stdint.h>

#define SAMPLING_FREQUENCY 48000

int tone;
int duration=0;
int count=0;




void testNotes(int note, int time){

	if(count==time){
		silence(1000000);
		count=0;
	}
	else{
		int sampling=PERIOD/note;
		if(sampling/2>=duration){
			*DAC0_CH0DATA=2000;
			*DAC0_CH1DATA=2000;
		}
		else{
			*DAC0_CH0DATA=-2000;
			*DAC0_CH1DATA=-2000;
		}
		duration++;
		if(duration==sampling){
			duration=0;
		}
		time++;
		count++;
	}
}

void play_note(int note){
	int sampling = PERIOD/note;
	int16_t amplitude;
	
	if(duration >= sampling/2){
		amplitude = 2000;
	}
	else{
		amplitude = -2000;
	}
	*DAC0_CH0DATA = amplitude;
	*DAC0_CH0DATA = amplitude;
	
	
	duration++;
	if(duration == sampling){
		duration = 0;
	}
}



void play_music(int notes[], int song_length, int duration_time){
			

}
	


void silence(int time){
	int i;
	for(i=0; i<time;i++){
		*DAC0_CH0DATA=0;
		*DAC0_CH1DATA=0;
	}
}








