/* Vernam Cipher by Barrientos, Monica */
/* This vernam cipher involves the use of XOR. Any modification of the result after XOR*/
/* will highly affect data integrity and the encrypted message will be unable to be decrypted. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char* generateKey(char msg[]);
void printString(char arr[]);
char* encryptiondecryption(char msg[], char key[]);
void printStringInt(char arr[]);
void encrypt();
void decrypt(int size);
int main () {
	char msg[256];
	int x;
	int size;
		int choice, choice2;
		printf("Welcome!\n");
		printf("This encryption uses ALL ASCII values including special characters\n");
		printf("Which may be unreadable after encryption.\n");
		printf("This is due to the fact that XOR operation is used here to during\n");
		printf("the encryption and decryption process.\n");
		printf("To maintain the integrity of data and readability, the encrypted message will highly\n");
		printf("include numerical values that are included in the ASCII table.\n");
		printf("\n======Do you want to proceed? 1 - Yes, 2 - No======\n");
		scanf("%d", &choice2);
		if(choice2 == 1){
		do 
			{
			 system("cls");
			 printf("\nWelcome to Vernam Encryption and Decryption\n");
			 printf("\nMenu\n");
			 printf("1. Encrypt\n");
			 printf("2. Decrypt\n");
			 printf("3. Exit\n");
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
			     	printf("Enter key length:\n");
			     	scanf("%d", &size);
					decrypt(size);
			      	getch();
			      	system("cls");
			        break;
			     case 3: 
			      	printf("Goodbye!\n"); 
			        break;
			     default: 
				 	printf("Wrong Choice. Enter again\n");
			        break;
			 } //6 18 1 10 26 26 16 15 9 19 4 4 15 23
			 //101 103 117 111 58 105 121 47 110 124 96 115 102 121
			} while (choice != 3);
			
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
	printf("\n\nKey Length:\n");
	printf("%d", strlen(keys));
	printf("\n");
  	printf("\nEncrypted Message\n");
  	enc = encryptiondecryption(msg, keys);
  	printStringInt(enc);
  	printf("\n");
}

void decrypt(int size){
	int x, key, encryptd;
	int keys[size];
	char* dec;
	char keys2[size], msg2[size];
	printf("Enter your key:\n");
	for(x=0;x<size;x++){
		scanf("%d", &key);
		keys[x] = key;
	}
	printf("Your key is:\n");
	for(x=0;x<size;x++){
		printf("%d ", keys[x]);
	}
	
	for(x=0;x<size;x++){
		keys2[x] = keys[x];
	}

	printf("\nInput your encrypted message:\n");
	for(x=0;x<size;x++){
		scanf("%d", &encryptd);
		msg2[x] = encryptd;
	}
	msg2[x]='\0';
	printf("\nDecrypted Message\n");
  	dec = encryptiondecryption(msg2,keys2);
	printString(dec);
	
	printf("\n");
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

void printStringInt(char arr[]){
	int x;
	for(x=0;arr[x]!='\0';x++){
		printf("%d ", arr[x]);
	}
}
char* generateKey(char msg[]){
	srand(time(NULL)); 
	int len = strlen(msg);

	int x,y=0, m=0,a;
	

	printf("\nYour generated key is . . . \n");
	printf("\nDO NOT SHARE WITH ANYONE. THIS WILL BE DESTROYED AFTER EXECUTION OF THE PROGRAM.\n");
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
