#include "sounds.h"
#include "efm32gg.h"

int duration=0;
void testNotes(int note){
	int sampling=note/A;
	if(sampling/2>=duration){
		*DAC0_CH0DATA=2000;
		*DAC0_CH1DATA=2000;
	}
	else{
		*DAC0_CH0DATA=-2000;
		*DAC0_CH1DATA=-2000;
	}
	duration++;
	if(duration==100000000){
		*DAC0_CH0DATA=0;
		*DAC0_CH1DATA=0;
	}
//	*DAC0_CH0DATA=duration++;
}
void play(int note){
	
}
void playDuration(int time){

}

