#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int rounds;
int mcu1_score = 0;
int mcu2_score = 0;
int ties = 0;

#ifdef _DEBUG_
	int mcu1_rocks = 0;
	int mcu1_papers = 0;
	int mcu1_scissors = 0;
	int mcu2_rocks = 0;
	int mcu2_papers = 0;
	int mcu2_scissors = 0;
#endif

int main (int argc, char **argv) {
	wiringPiSetup();
	pinMode(3,OUTPUT);
	pinMode(7,OUTPUT);
	for (rounds = 0; rounds < atoi(argv[1]); rounds++) {
		digitalWrite(3,HIGH);
		digitalWrite(7,HIGH);
		
		delay(3);
		#ifndef _DEBUG_
			if (digitalRead(0)) {
				if (digitalRead(4)) {
					ties++;
				}
				if (digitalRead(5)) {
					mcu2_score++;
				}
				if (digitalRead(6)) {
					mcu1_score++;
				}
			}
			if (digitalRead(1)) {
				if (digitalRead(4)) {
					mcu1_score++;
				}
				if (digitalRead(5)) {
					ties++;
				}
				if (digitalRead(6)) {
					mcu2_score++;
				}
			}
			if (digitalRead(2)) {
				if (digitalRead(4)) {
					mcu2_score++;
				}
				if (digitalRead(5)) {
					mcu1_score++;
				}
				if (digitalRead(6)) {
					ties++;
				}
			}
		#endif
		#ifdef _DEBUG_
			if (digitalRead(0)) {
				if (digitalRead(4)) {
					printf("Rock - Rock:         TIE\n");
					ties++;
				}
				if (digitalRead(5)) {
					printf("Rock - Paper:        MCU2 wins\n");
					mcu2_score++;
				}
				if (digitalRead(6)) {
					printf("Rock - Scissors:     MCU1 wins\n");
					mcu1_score++;
				}
			}
			if (digitalRead(1)) {
				if (digitalRead(4)) {
					printf("Paper - Rock:        MCU1 wins\n");
					mcu1_score++;
				}
				if (digitalRead(5)) {
					printf("Paper - Paper:       TIE\n");
					ties++;
				}
				if (digitalRead(6)) {
					printf("Paper - Scissors:    MCU2 wins\n");
					mcu2_score++;
				}
			}
			if (digitalRead(2)) {
				if (digitalRead(4)) {
					printf("Scissors - Rock:     MCU2 wins\n");
					mcu2_score++;
				}
				if (digitalRead(5)) {
					printf("Scissors - Paper:    MCU1 wins\n");
					mcu1_score++;
				}
				if (digitalRead(6)) {
					printf("Scissors - Scissors: TIE\n");
					ties++;
				}
			}		
		#endif
		digitalWrite(3,LOW);
		digitalWrite(7,LOW);
		delay(1);
		#ifndef _DEBUG_
			printf("%d\r",rounds);		
		#endif
	}
	if (mcu1_score > mcu2_score) {
		printf("MCU1 WINS!\n");
		printf("margin:%d\n",mcu1_score - mcu2_score);
	}
	if (mcu1_score < mcu2_score) {
		printf("MCU2 WINS!\n");
		printf("margin:%d\n",mcu2_score - mcu1_score);
	}
	if (mcu1_score == mcu2_score) {
		printf("A TIE!  What are the odds?\n");
	}
	printf("MCU1 Score: %d\n",mcu1_score);
	printf("MCU2 score: %d\n",mcu2_score);
	printf("Ties:       %d\n",ties);
	
	return 0;
}
