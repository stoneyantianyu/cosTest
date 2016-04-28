#include <stdio.h>
#include <stdlib.h>
#include "inc.h"

short dispatcher(char* apdu, char* responseBuf, u2* responseLen);
extern void insertCard(	u1* imsi,
						u1* ki,
						u1* opc,
						u1* iccid,
						u1* acc,
						u1* spn,
						u1* apn,
						u1* hplmn,
						u1* ehplmn,
						u1* loci,
						u1* psloci,
						u1* fplmn );
void showFS();
void printReponse(u1* resp, short len);
u1* aidString2Buffertmp(u1* aid, u2* aidlen);
u1 hexToDectmp(u1 c);

#define MAX_LINE 1024

int main() {
	char* apdu = malloc(256);
	char* reponse = malloc(256);
	short index = 0;
	FileDesc* mf;
	unsigned short sw, resLen;
	char buf[MAX_LINE];  /*缓冲区*/
	FILE *fp;            /*文件指针*/
	short len;             /*行字符个数*/ 
	char *apdubuf;
	
    printf("hello world\n");
	//apdu[1] = 0xA4;
	insertCard(
				"234507095700575",//"460010300000001",//imsi,
				"",//ki,
				"",//opc,
				"123456789",//iccid,
				"0404",//acc,
				"00hhhhhhh",//spn,
				"",//apn,
				"",//hplmn,
				"",//ehplmn
				"",//loci,
				"",//psloci
				""//fplmn
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
	
	if((fp = fopen("apdu.txt","r")) == NULL)
	{
		perror("fail to read");
		exit (1) ;
	}
	while(fgets(buf,MAX_LINE,fp) != NULL)
	{
		len = strlen(buf);
		if(len < 5) {
			continue;
		}
		//printf("%s\n",buf);
		apdubuf = aidString2Buffertmp(buf, &len);
		//printReponse(apdubuf, len - 1);
		sw = dispatcher(apdubuf, reponse, &resLen);
		printf("										[SW]: %02X\n", sw);
		if(resLen > 0) {
			printReponse(reponse, resLen);
		}
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

u1 hexToDectmp(u1 c) {
	if ('0' <= c && c <= '9') {
		return c - '0';
	}
	if ('A' <= c && c <= 'F') {
		return c - 'A' + 10;
	}
	if ('a' <= c && c <= 'f') {
		return c - 'a' + 10;
	}
	return -1;
}

u1* aidString2Buffertmp(u1* aid, u2* aidlen) {
	u1* buf, left, right, i;
	u1 strlength  = strlen(aid);
	u1 buflen = strlength / 2;

	//printf("aid[%s], len[%02X]\n", aid, buflen);
	
	buf = malloc(buflen);

	for(i = 0; i < strlength; i += 2) {
		left = hexToDectmp(*(aid + i));
		right = hexToDectmp(*(aid + i + 1));
		buf[i /2] = (left << 4) + right;
	}
	*aidlen = buflen;
	return buf;
}