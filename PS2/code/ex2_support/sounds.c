#include "sounds.h"
#include "efm32gg.h"
#include "sound_data.h"
#include <stdint.h>

#define SAMPLING_FREQUENCY 48000

int tone;
int duration=0;
int count=0;
int note_pos=0;
int tone_duration=0;
int notes_pos=0; 


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
	
	/*  
	if(duration >= sampling/2){
		amplitude = 2000;
	}
	else{
		amplitude = -2000;
	}
	*/
	*DAC0_CH0DATA = note+1500;
	*DAC0_CH1DATA = note+1500;
	
	
	duration++;
	if(duration == sampling){
		duration = 0;
	}
}



void play_music(int size, int tone_lenght){
	int note = (char)sounddata_data[notes_pos];
	play_note(note);

 	tone_duration++;
	if(tone_duration > tone_lenght){
		notes_pos++;
		tone_duration = 0;
	}
	note_pos++;
	if(notes_pos > size){
		notes_pos = 0;
	}


	


}
	


void silence(int time){
	int i;
	for(i=0; i<time;i++){
		*DAC0_CH0DATA=0;
		*DAC0_CH1DATA=0;
	}
}








