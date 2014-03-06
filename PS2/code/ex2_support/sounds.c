#include "sounds.h"
#include "efm32gg.h"
#include <stdint.h>
#include <stdbool.h>
#include "sound_data.h"
#include "melodies.h"

#define SAMPLING_FREQUENCY 32768

int tone;
int duration=0;
int count=0;
int note_pos=0;
int tone_duration=0;
int notes_pos=0;
int pos=0;

bool iterate=false;
int counter=0;


// Set all variables to zero after reset
void initSound(){
	duration=0;
	note_pos=0;
	tone_duration=0;
	notes_pos=0;
	counter=0;
	pos=0;
	iterate=false;
}
void testNotes(int note, int time){
	int cycles = convert_from_ms(time);

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
	if(duration>=sampling){
		duration=0;
	}
	counter++;	
	if(counter==cycles){
		iterate=true;
	   counter=0;
	}
}

void testSawtooth(int note, int time){

		int sampling=PERIOD/note;
		
		int slope = (1024)/sampling;
		
		int y = (slope*duration);
		
		*DAC0_CH0DATA=y;
		*DAC0_CH1DATA=y;
		
		duration++;

		if(duration>=sampling){
			duration=0;
		}
		counter++;
		
		if(counter==time){
		   iterate=true;
		   counter=0;
		}
}




/*Used in combination with the play music function*/
void play_note(int note){
	int sampling = PERIOD/note;
	int16_t amplitude;
	
	*DAC0_CH0DATA = (note << 2);
	*DAC0_CH1DATA = (note << 2);	
	
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
int convert_from_ms(int millis){
	return millis * 15;
}
void playSong(struct tone melody[], int size){
	testNotes(melody[pos].note, melody[pos].time);
	if(iterate==true){
        pos++;
        iterate=false;
	}
	else if(pos >= size){
//		disableLowEnergyTimer();
		initSound();
	 }
}
void play_melodies(){
	
	switch((*GPIO_PC_DIN)){
		case 0xfe:
			testNotes(A, 10);
			break;
		case 0xfd:
			testNotes(B, 10);
			break;
		case 0xfb:
			testNotes(C, 10);
			break;
		case 0xf7:
			testNotes(D, 10);
			break;
		case 0xef:
			playSong(mario, 215);
			break;
		case 0xdf:
			playSong(mario, 215);
			break;
		case 0xbf:
			playSong(mario, 215);
			break;
		case 0x7f:
			playSong(mario, 215);
			break;
	}
}
