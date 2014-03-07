#include "sounds.h"
#include "efm32gg.h"
#include <stdint.h>
#include <stdbool.h>
#include "sound_data.h"
#include "melodies.h"

#define SAMPLING_FREQUENCY 32768


/*Function prototypes*/
void setupLowEnergyTimer();
void disableLowEnergyTimer();



/*Global variables*/
bool timer_running;

int tone;
int duration; //Keeps track of wave length
int count;
int note_pos;
int tone_duration;
int notes_pos;
int pos;

struct tone *sampleArray;
int songlength;

bool iterate=false; //Set to true if tone has been played for a specified amount of time
int counter=0; //Keeps track of time duration of tone 


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

/*
Function to play a note for a specified amount of milliseconds
*/
void testNotes(int note, int time){
	int cycles = convert_from_ms(time); //Cycle variable corresponds to amount of milliseconds specified in time-variable

	int sampling=PERIOD/note; //Create correct number of samples per waveform based on the number of samples per second 
	
	
	/* if-else to transition between high and low */
	if(sampling/2>=duration){
		*DAC0_CH0DATA=2000;
		*DAC0_CH1DATA=2000;
	}
	else{
		*DAC0_CH0DATA=-2000;
		*DAC0_CH1DATA=-2000;
	}
	duration++;
	
	/* Reset duration if end of period */
	if(duration>=sampling){
		duration=0;
	}
	counter++;
	if(counter==cycles){
		iterate=true; //Iterate to next note if the current note has played for specified amount of time
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
 * this plays 8000 samples per second*/
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
		disableLowEnergyTimer();
		timer_running = false;
		initSound();
	 }
}
void select_melodies(){
	
	switch((*GPIO_PC_DIN)){
		case 0xfe:
			if(timer_running){
				disableLowEnergyTimer();
			}
			timer_running = true;
			setupLowEnergyTimer();
			sampleArray=mario;
			songlength=215;
			break;
		case 0xfd:
			if(timer_running){
				disableLowEnergyTimer();
			}
			timer_running = true;
			setupLowEnergyTimer();
			sampleArray=mario;
			songlength=215;			
			break;
		case 0xfb:
			if(timer_running){
				disableLowEnergyTimer();
			}
			timer_running = true;
			setupLowEnergyTimer();
			sampleArray=mario;
			songlength=215;
			break;
		case 0xf7:
			if(timer_running){
				diableLowEnergyTimer();
			}
			timer_running = true; 
			setupLowEnergyTimer();
			sampleArray=mario;
			songlength=215;
			break;
		case 0xef:
			if(timer_running){
				disableLowEnergyTimer();
			}
			timer_running = true;
			setupLowEnergyTimer();
			sampleArray=mario;
			songlength=215;
			break;
		case 0xdf:
			if(timer_running){
				disableLowEnergyTimer();
			}
			timer_running = true; 
			setupLowEnergyTimer();
			sampleArray=mario;
			songlength=215;
			break;
		case 0xbf:
			if(timer_running){
				disableLowEnergyTimer();
			}
			timer_running = true;
			setupLowEnergyTimer();
			sampleArray=mario;
			songlength=215;
			break;
		case 0x7f:
			if(timer_running){
				disableLowEnergyTimer();
			}
			timer_running = true;
			setupLowEnergyTimer();
			sampleArray=mario;
			songlength=215;
			break;
	}
}
