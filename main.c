#include <stdio.h>
#include <stdlib.h>
#include "inc.h"

short dispatcher(char* apdu, char* responseBuf, u2* responseLen);
void insertCard(u1* iccid, u1* imsi, u1* ki);
void showFS();
void printReponse(u1* resp, short len);

int main() {
	char* apdu = malloc(256);
	char* reponse = malloc(256);
	short index = 0;
	FileDesc* mf;
	unsigned short sw, resLen;
	
    printf("hello world\n");
	//apdu[1] = 0xA4;
	insertCard("8986201603250104", 
		"234507095700575",
		"3C77B0BBDF8BB39A94175A0D5C9DFE4E"
		);
	/*
	dispatcher(apdu, reponse, &resLen);
	apdu[1] = 0x70;
	dispatcher(apdu, reponse, &resLen);
	apdu[1] = 0x71;
	dispatcher(apdu, reponse, &resLen);
	*/
	
	printf("buildFileSystem\n");
	
	//mf = buildFileSystem();
	//showFileSystem(mf);
	
	showFS();
	
	index = 0;
	apdu[index ++] = 0x00;
	apdu[index ++] = 0xA4;
	apdu[index ++] = 0x00;
	apdu[index ++] = 0x0C;
	apdu[index ++] = 0x02;
	apdu[index ++] = 0x2F;
	apdu[index ++] = 0x05;
	
	sw = dispatcher(apdu, reponse, &resLen);
	
	printf("sw: %02X\n", sw);
	if(resLen > 0) {
		printReponse(reponse, resLen);
	}
	
	
	index = 0;
	apdu[index ++] = 0x00;
	apdu[index ++] = 0xA4;
	apdu[index ++] = 0x08;
	apdu[index ++] = 0x04;
	apdu[index ++] = 0x02;
	apdu[index ++] = 0x2F;
	apdu[index ++] = 0x05;
	
	sw = dispatcher(apdu, reponse, &resLen);
	
	printf("sw: %02X\n", sw);
	if(resLen > 0) {
		printReponse(reponse, resLen);
	}
	
	
	index = 0;
	apdu[index ++] = 0x00;
	apdu[index ++] = 0xA4;
	apdu[index ++] = 0x04;
	apdu[index ++] = 0x00;
	apdu[index ++] = 0x10;
	apdu[index ++] = 0xA0;
	apdu[index ++] = 0x00;
	apdu[index ++] = 0x00;
	apdu[index ++] = 0x00;
	apdu[index ++] = 0x87;
	apdu[index ++] = 0x10;
	apdu[index ++] = 0x02;
	apdu[index ++] = 0xFF;
	apdu[index ++] = 0x86;
	apdu[index ++] = 0xFF;
	apdu[index ++] = 0xFF;
	apdu[index ++] = 0x89;
	apdu[index ++] = 0xFF;
	apdu[index ++] = 0xFF;
	apdu[index ++] = 0xFF;
	apdu[index ++] = 0xFF;
	
	sw = dispatcher(apdu, reponse, &resLen);
	
	printf("sw: %02X\n", sw);
	if(resLen > 0) {
		printReponse(reponse, resLen);
	}

}

void printReponse(u1* resp, short len) {
	u2 i = 0;

	printf("$ ");
	while(len --) {
		printf("%02X",  *(resp + (i ++)));
	}
	printf(" $\n");
}