/* AES - RSA Cipher by Barrientos, Monica */
/* This cipher involves resulting data to include special characters*/
/* This will highly affect the readability, that is why encrypted messages are displayed in terms of integers */

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
 
/* Mathematical Functions*/
int checkPrime(long int);
void getKeys(char msg[], int p, int q, int tot);
long int doMod(long int x, int tot);
int getTot(int p, int q);

/* Encryption and Decryption Functions*/
long int* encrypt(int n, char msgStore[]);
void decrypt(int n, long int temp[]);

/* Utility Funcs*/
/* Print Functions*/
void printMessage(char arr[]);
void displayInInt(long int arr[]);
/* Storing Functions*/
char* storeInArray(char arr[]);

void startProg();
long int encryptedKey[100],decryptedKey[100],uniValue,encrypted[100];

int main(){

 	int choice,choice2;
		printf("Welcome!\n");
		printf("This encryption uses ALL ASCII values including special characters\n");
		printf("Which may be unreadable after encryption.\n");
		printf("To maintain the integrity of data and readability, the encrypted message will highly\n");
		printf("include numerical values that are included in the ASCII table.\n");
		printf("\n======Do you want to proceed? 1 - Yes, 2 - No======\n");
		scanf("%d", &choice2);
		if(choice2 == 1){
		do 
			{
			 system("cls");
			 printf("\nWelcome to AES-RSA Encryption and Decryption\n");
			 printf("\nMenu\n");
			 printf("1. Start\n");
			 printf("2. Exit\n");
			 scanf("%d",&choice);
			  
			 switch (choice)
			 {
			     case 1: 
			      	startProg();
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
}

void startProg(){
	
	long int p,q,n,tot;
	int flag,x;
 	char msg[256]; 
 	char *msgStore;
 	long int* retTemp;
	do{
 		printf("\nInput first prime number\n");
		scanf("%d",&p);
	 
		flag=checkPrime(p);
		if(flag==0) {
			printf("\n%d is not a prime number!\n", p);
			getch();
	 		system("cls");
		}
	}while(flag!=1);
	
	do{
 		printf("\nInput second prime number\n");
		scanf("%d",&q);
	 
		flag=checkPrime(q);
		if(flag==0) {
			printf("\n%d is not a prime number!\n", q);
			getch();
	 		system("cls");
		}
		if(p==q){
			printf("\n%d is the same number as %d!\n", q,p);
			flag=0;
			getch();
	 		system("cls");
		}
	}while(flag!=1);

	printf("\nInput message to be encrypted\n");
	fflush(stdin);
 	gets(msg); 
 	msgStore=storeInArray(msg);

	n=p*q;
	tot=getTot(p,q);
 
	getKeys(msgStore, p, q, tot);

	retTemp = encrypt(n, msgStore); 
	printf("\n");
	decrypt(n, retTemp);
 
	getch();
}

int getTot(int p, int q){
	int retVal;
	retVal = (p-1)*(q-1);
	return retVal;
}

int checkPrime(long int y) {
 
	int x;
	uniValue=sqrt(y);
  
	for (x=2;x<=uniValue;x++) {
		if(y%x==0)
		    return 0;
	}
	return 1;
}
 
void getKeys(char msg[], int p, int q, int tot) {
 
	int ctr=0,x;
 	int flg,flg2=0;
	for (x=2;x<tot;x++) {
		if(tot%x!=0){
			flg=checkPrime(x);
			if(flg == 1 && x != p && x != q && flg2!=1) {
				encryptedKey[ctr]=x;
				flg=doMod(encryptedKey[ctr], tot);
				if(flg>0) {
					decryptedKey[ctr]=flg;
					ctr++;
				}
				if(ctr==99)
				    flg2 =1;
			}
		}
	}
}
 
long int doMod(long int value, int tot) {
	long int num=1;
	while(num%value!=0) {
		num=num+tot;
	}
	return(num/value);
}

long int* encrypt(int n, char msgStore[]){ 
	long int storeOne,storeTwo,keys,value;
	int len,x=0, i;
 	long int* temp=(long int*)malloc(256 * sizeof(long int));
	len=strlen(msgStore);
 
 	keys = encryptedKey[0];
	while(x!=len) {
		storeOne=msgStore[x];
		storeOne=storeOne-96;
		value=1;
		for (i=0;i<keys;i++) {
			value=value*storeOne;
			value=value%n;
		}
		temp[x]=value;
		storeTwo=value+96;
		encrypted[x]=storeTwo;
		x++;
	}
 
	encrypted[x]=-1;

	printf("\nSuccessfully Encrypted! Message is\n");
 	displayInInt(encrypted);

 	return temp;
}

 
void decrypt(int n, long int temp[]) {
 
	long int storeOne,storeTwo,keys,value;
 	char msgStore[256];
	int x=0,i;
 	keys=decryptedKey[0];
	while(encrypted[x]!=-1) {
		storeTwo=temp[x];
		value=1;
		for (i=0;i<keys;i++) {
			value=value*storeTwo;
			value=value%n;
		}
		storeOne=value+96;
		msgStore[x]=storeOne;
		x++;
	}
	msgStore[x]='\0';
 
	printf("\nSuccesfully Decrypted! Message is\n");
 	printMessage(msgStore);
}

/*Utility Funcs*/
char* storeInArray(char arr[]){
	
	int x;
	char* retArray = (char*)malloc(256 * sizeof(char));
	
	for(x=0;arr[x]!='\0';x++){
		retArray[x]=arr[x];
	}
	retArray[x]='\0';
	
	return retArray;
}
void printMessage(char arr[]){
	int x;
	
	for(x=0;arr[x]!='\0';x++){
		printf("%c",arr[x]);
	}
}

void printString(long int arr[], int size){
	int x;
	
	for(x=0;x<size-1;x++){
		printf("%ld\n",arr[x]);
	}
}


void displayInInt(long int arr[]){
	int x;
	
	for(x=0;arr[x]!=-1;x++){
		printf("%d ",arr[x]);
	}
}
