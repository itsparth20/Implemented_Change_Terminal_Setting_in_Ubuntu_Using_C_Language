// Created by: Parth Patel
#include "stdlib.h"
#include "stdio.h"
#include "termios.h"
#include "unistd.h"
#include "string.h"
#include "stdio.h"

void showStartStop(int);

int main(int count, char* argu[])
{
	struct termios terminosmode;                               
	int temp;                                      

	if(temp = tcgetattr(0, &terminosmode) == -1){
		printf("Problem during showing attribute.\n");
		exit(1);         
	}

	if (count == 3) 
	{
		char* ar = argu[2];
		int asccode = (int)ar[0];     
		if(ar[0]=='^'){
		asccode = ar[1]-'A'+1;
		}
		if(strcmp(argu[1], "start") == 0)          
		terminosmode.c_cc[VSTART] = asccode;
		if(strcmp(argu[1], "stop") == 0)
		terminosmode.c_cc[VSTOP] = asccode;
	}

	else if(count == 1)                                    
	{
		if(!(terminosmode.c_iflag & IUCLC)){
		printf("-iuclc");
		}
		else{
		printf("+iuclc");
		}

		if(!(terminosmode.c_lflag & ECHO)){
		printf(" -echo ");
		}
		else{
		printf(" +echo ");
		}

		printf("start = ");
		showStartStop(terminosmode.c_cc[VSTART]);
		printf(" ");
		printf("stop = ");
		showStartStop(terminosmode.c_cc[VSTOP]);    
		printf(" \n");
	}

	else if (count == 2)
	{		
		if(strcmp(argu[1], "-iuclc") == 0){
			terminosmode.c_iflag &= ~IUCLC;
		}
		else if(strcmp( argu[1], "-echo") == 0){
			terminosmode.c_lflag &= ~ECHO;
		}	
		else if(strcmp( argu[1], "+iuclc") == 0){
			terminosmode.c_iflag |= IUCLC;     
		}	
		else if(strcmp( argu[1], "+echo") == 0){
			terminosmode.c_lflag |= ECHO;
		}
	}
	

	if(temp = tcsetattr(0, TCSANOW, &terminosmode) == -1){ 
		
		printf("Try again after some time.\n");
		exit(1);
	}
	return 0;
}

void showStartStop(int no)        
{                             
	if(no<27){
	printf("^%c ", (char)(no+'A'-1));
	}
	else{
	printf("%c ",(char)no); 
	}
}
