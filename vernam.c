#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char* generateKey(char msg[]);
void printString(char arr[]);
char* encryptiondecryption(char msg[], char key[]);

int main () {
	char msg[256];
	char key[256];
	int i,j;
	char *keys;
	char *enc;
	char *dec;

	printf("Enter message to be encrypted\n");
	fflush(stdin);
	gets(msg);

	
//	for (i = 0, j; msg[i] != '\0'; ++i) {
//
//      while (!(msg[i] >= 'a' && msg[i] <= 'z') && !(msg[i] >= 'A' && msg[i] <= 'Z') && !(msg[i] == '\0')) {
//         for (j = i; msg[j] != '\0'; ++j) {
//
//            msg[j] = msg[j + 1];
//         }
//         msg[j] = '\0';
//      }
//   	}	
  	keys = generateKey(msg);
  	printf("\nEncrypted Message\n");
  	enc = encryptiondecryption(msg, keys);
  	printString(enc);
  	printf("\nDecrypted Message\n");
  	dec = encryptiondecryption(enc, keys);
	printString(dec);
}

char* encryptiondecryption(char msg[], char key[]){
	char *encrypted =(char*) malloc (sizeof (char)* 255);
	int i;
	for(i = 0; msg[i]!='\0' ; i++){
		encrypted[i] = msg[i] ^ key[i];
	}
	encrypted[i]= '\0';
	return encrypted;
}


void printString(char arr[]){
	int x;
	for(x=0;arr[x]!='\0';x++){
		printf("%c", arr[x]);
	}
}
char* generateKey(char msg[]){
	srand(time(NULL)); 
	int len = strlen(msg);

	int x,y=0, m=0,a;
	

	printf("Your generated key is . . .\n");

	int getOTP[len];
	for(x=0;x<len;x++){
		getOTP[x] = (rand() % (122 + 1 - 97)) + 97;
	}
	getOTP[x]='\0';
	for(x=0;x<len;x++){
		printf("%d ", getOTP[x]);
	}
	
	char *letterOTP = malloc (sizeof (char) * len);

	for(x=0;x<len;x++){
	
		letterOTP[x] = getOTP[x];
	}
	letterOTP[x] = '\0';
	return letterOTP;

}
