#include <stdio.h>
#include <stdlib.h>
#include "inc.h"

void dispatcher(char* apdu);

int main() {
	char* apdu = malloc(10);
	FileDesc* mf;
	
    printf("hello world\n");
	apdu[1] = 0xA4;
	dispatcher(apdu);
	apdu[1] = 0x70;
	dispatcher(apdu);
	apdu[1] = 0x71;
	dispatcher(apdu);
	
	printf("buildFileSystem\n");
	
	mf = buildFileSystem();
	showFileSystem(mf);
}
