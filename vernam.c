/* Vernam Cipher by Barrientos, Monica */
/* This vernam cipher involves the use of XOR. Any modification of the result after XOR*/
/* will highly affect data integrity and the encrypted message will be unable to be decrypted. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char* generateKey(char msg[]);
void printString(char arr[]);
char* encryptiondecryption(char msg[], char key[]);
void encrypt();
int main () {
	char msg[256];


		int choice, choice2;
		printf("Welcome!\n");
		printf("This encryption uses ALL ASCII values including special characters\n");
		printf("Which may be unreadable after encryption.\n");
		printf("This is due to the fact that XOR operation is used here to during\n");
		printf("the encryption and decryption process.\n");
		printf("To maintain the integrity of data, the encrypted message will highly\n");
		printf("include special characters that are included in the ASCII table.\n");
		printf("\n======Do you want to proceed? 1 - Yes, 2 - No======\n");
		scanf("%d", &choice2);
		if(choice2 == 1){
		do 
			{
			 system("cls");
			 printf("\nWelcome to Vernam Encryption and Decryption\n");
			 printf("\nMenu\n");
			 printf("1. Start\n");
			 printf("2. Exit\n");
			 scanf("%d",&choice);
			  
			 switch (choice)
			 {
			     case 1: 
			      	printf("Enter message to be encrypted\n");
					fflush(stdin);
					gets(msg);
					encrypt(msg);
			      	getch();
			      	system("cls");
			        break;
			     case 2: 
			      	printf("Goodbye!\n"); 
			        break;
			     default: 
				 	printf("Wrong Choice. Enter again\n");
			        break;
			 } 
			} while (choice != 2);
			
		}else{
			printf("Okay goodbye!\n");
		}
		
    return 0;
    
}

void encrypt(char msg[]){
	char key[256];
	int i,j;
	char *keys;
	char *enc;
	char *dec;
	
	keys = generateKey(msg);
	printf("\n");
  	printf("\nEncrypted Message\n");
  	enc = encryptiondecryption(msg, keys);
  	printString(enc);
  	printf("\n");
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
	

	printf("Your generated key is . . . \n");
	printf("DO NOT SHARE WITH ANYONE. THIS WILL BE DESTROYED AFTER EXECUTION OF THE PROGRAM.\n");
	int getOTP[len];
	for(x=0;x<len;x++){
		getOTP[x] = (rand() % (26 + 1 - 1)) + 1;
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
