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
int convert_from_ms(int millis);
void changeTopCounter(int sampleRate);
void setupDAC();
void disableDAC();



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
int runBattlefield;

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
	songlength=0;
	iterate=false;
	runBattlefield = 0;
	changeTopCounter(SAMPLING_FREQUENCY);
}

/*
Function to play a note for a specified amount of milliseconds
*/
void playNotes(int note, int time){
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


/* Function for creating discrete samples
 * from sawtooth waves. Not actually used 
 * in the main program. Decided on square waves
 * because the sound was better. 
 */

void sawtoothWave(int note, int time){

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



/* Function for playing samples at 8000Hz.
 * The function pushes a sample every time it 
 * is called. The samples are staticially 
 * linked in sound_data.h. At the end of
 * the sample array the timer and DAC 
 * are disabled. 
 *
 */
void play_music(int size){
	int note = (char)sounddata_data[notes_pos];
	
	
	*DAC0_CH0DATA = (note << 1);
	*DAC0_CH1DATA = (note << 1);
	
	if(notes_pos > size){
		notes_pos = 0;
		disableLowEnergyTimer();
		disableDAC();
		initSound();
	}
	
	notes_pos++;

}

/* The function converts milliseconds 
 * to the corresponding number of cycles.
 *
 */

int convert_from_ms(int millis){
	return millis * 15;
}

/* Function for playing samples.
 * Based on the sample array, and 
 * the current postion in the sample
 * it calls the playNotes() function. 
 * When end of the samples are reached
 * the function disables the timer 
 * and the DAC.
 *
 */

void playSong(struct tone melody[], int size){
	
	playNotes(melody[pos].note, melody[pos].time);
	
	if(iterate==true){
        pos++;
        iterate=false;
	}
	else if(pos >= size){	
		disableLowEnergyTimer();
		disableDAC();
		timer_running = false;
		initSound();
	 }
}

/* Test function. 
 * Tests the mario into.
 * Not used in the final 
 * version
 */

void playMario(){
	sampleArray = mario;
	songlength = 215;
}



/* Function to select melodies.
 * The function selects melodies based
 * on the button pushed. For selected
 * song the timer and DAC is enabled.
 * If a song is already playing. It 
 * interrupt the song by disabling the
 * timer and DAC before it continues
 * selecting the new song.
 *
 */

void select_melodies(){
	
	switch((*GPIO_PC_DIN)){
		case 0xfe:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			setupDAC();
			setupLowEnergyTimer();
			sampleArray=mario;
			songlength=215;
			break;
		case 0xfd:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			setupDAC();
			setupLowEnergyTimer();
			sampleArray=hit_received;
			songlength=36;			
			break;
		case 0xfb:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC(); 
				initSound();
			}
			timer_running = true;
			setupDAC();
			setupLowEnergyTimer();
			sampleArray=hit_dealt;
			songlength=41;
			break;
		case 0xf7:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true; 
			setupDAC();
			setupLowEnergyTimer();
			sampleArray=shoot;
			songlength=15;
			break;
		case 0xef:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();			
			}
			timer_running = true;
			runBattlefield = 1;
			setupDAC();
			setupLowEnergyTimer();
			changeTopCounter(8000);
			songlength=396000;
			break;
		case 0xdf:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();			
			}
			timer_running = true;
			setupDAC();
			setupLowEnergyTimer();
			sampleArray=beep1;
			songlength=1;
			break;
		case 0xbf:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();			
			}
			timer_running = true;
			setupDAC();
			setupLowEnergyTimer();
			sampleArray=beep2;
			songlength=1;
			break;
		case 0x7f:
			if(timer_running){
				disableLowEnergyTimer();
				disableDAC();
				initSound();
			}
			timer_running = true;
			setupDAC();
			setupLowEnergyTimer();
			sampleArray=beep3;
			songlength=1;
			break;
	}
}
