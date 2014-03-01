#include "sounds.h"
#include "efm32gg.h"
#include "sound_data.h"
#include <stdint.h>
#include <stdbool.h>

#define SAMPLING_FREQUENCY 48000

int tone;
int duration=0;
int count=0;
int note_pos=0;
int tone_duration=0;
int notes_pos=0; 

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





/*Used in combination with the play music function*/
void play_note(int note){
	int sampling = PERIOD/note;
	int16_t amplitude;
	
	*DAC0_CH0DATA = (note << 3);
	*DAC0_CH1DATA = (note << 3);
	
	
	duration++;
	if(duration == sampling){
		duration = 0;
	}
}

/*Feed the DAC with already existing samples. With normal use
 * this plays 48000 samples each second*/
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








