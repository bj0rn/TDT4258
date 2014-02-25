#include "sounds.h"
#include "efm32gg.h"

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
//	*DAC0_CH0DATA=duration++;
}
void play(int note){
	
}
void playDuration(int time){

}
void silence(int time){
	int i;
	for(i=0; i<time;i++){
		*DAC0_CH0DATA=0;
		*DAC0_CH1DATA=0;
	}
}
