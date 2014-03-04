#include "sounds.h"
#include "efm32gg.h"
#include <stdint.h>
#include <stdbool.h>
#include "sound_data.h"

#define SAMPLING_FREQUENCY 32768

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
	int cycles = convert_from_ms(time);

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
//	        *GPIO_PA_DOUT = (0xff<<8);

		}
		else{
			*DAC0_CH0DATA=-2000;
			*DAC0_CH1DATA=-2000;
//			*GPIO_PA_DOUT = (0x00<<8);
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
//		if(stop)
		   
//		}
}

void testSawtooth(int note, int time){

//	bool stop=false;
	
//	if(stop==false){
	
//		if(count==time){
//			silence(1000000);
//			counter=0;
//		}
//		else{
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
//		if(stop)
		   
//		}
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
void play_piano(){
	
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
			testNotes(E, 10);
			break;
		case 0xdf:
			testNotes(F, 10);
			break;
		case 0xbf:
			testNotes(G, 10);
			break;
		case 0x7f:
			testNotes(H, 10);
			break;
	}
}
