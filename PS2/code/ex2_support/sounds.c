#include "sounds.h"
#include "efm32gg.h"
#include <stdint.h>
#include <stdbool.h>

#define SAMPLING_FREQUENCY 48000

int tone;
int duration=0;
bool iterate=false;
int counter=0;
//int pos=0;

//bool stop=false;
void testNotes(int note, int time){

//	bool stop=false;
	
//	if(stop==false){
	
//		if(count==time){
//			silence(1000000);
//			counter=0;
//		}
//		else{
		int sampling=PERIOD/note;
		if(sampling/2>=duration){
			*DAC0_CH0DATA=2000;
			*DAC0_CH1DATA=2000;
	        *GPIO_PA_DOUT = (0xff<<8);

		}
		else{
			*DAC0_CH0DATA=-2000;
			*DAC0_CH1DATA=-2000;
			*GPIO_PA_DOUT = (0x00<<8);
		}
		duration++;
		if(duration>=sampling){
			duration=0;
		}
		counter++;
		
		if(counter==time){
		   iterate=true;
		   counter=0;
		}
//		if(stop)
		   
//		}
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

void play_music(int notes[], int song_length, int i){
	testNotes(notes[i], 100000);
}
	


void silence(int time){
	int i;
	for(i=0; i<time;i++){
		*DAC0_CH0DATA=0;
		*DAC0_CH1DATA=0;
	}
}








