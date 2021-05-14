#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>

#define TEXT_SIZE 1024

long int encryptedKey[100],decryptedKey[100],uniValue;
int ctr=0;

/* Printing functions */
void printNumbers(int arr[], int size);
void printKey(char arr[]);

/* Math Functions for producing private and public keys */
int getNumber();
int getNumberAgain();
void getKeys(char msg[], int p, int q, int tot);
long int doMod(long int value, int tot);
void startProg();
int getTot(int p, int q);
int checkPrime(long int y);

/* File Writing for the Keys */
void readFile();
void readFilePriv();
void writePublicKeyFile();
void writePrivateKeyFile();
int readFileCertainKey();

/* Creation of Plain Text File*/
void createPlainTextFile();

/* Encryption Process*/

void writePlainText(char filename[], char message[]);
char* readPlainText();
char* choosePlainTextFile();
char* encryption(char message[], int key);
void writeEncryptedToFile(char encrypted[]);
void readEncryptedToFile(char filename[]);


/* Decryption Process*/

int readPrivateFileCertainKey();
char* chooseEncryptedTextFile();
char* decryption(char message[], int key);

int main() {
	int retValEnc, retValDec, first,second,choice;
	char plaintext[TEXT_SIZE], encryptedFileName[50];
	char* msg;
	char* encrypted;
	char* encmsg;
	char* decrypted;
	char pltxtName[50];
	do 
		{
		 printf("\nWelcome to Monoalphabetic Encryption and Decryption\n");
		 printf("\nMenu\n");
		 printf("1. Create a Text File for your plaintext. \n");
		 printf("2. Produce your public and private keys. \n");
		 printf("3. Encrypt \n");
		 printf("4. Decrypt \n");
		 printf("5. Exit\n");
		 scanf("%d",&choice);
		  
		 switch (choice)
		 {
		     case 1: 
		      	createPlainTextFile();
		      	getch();
		      	system("cls");
		        break;
		     case 2: 
//		      	printf("Input plain text file name you will use.\n");
//		      	gets(pltxtName);
		      	
				startProg();
				writePublicKeyFile();
				writePrivateKeyFile();
				readFile();
			    readFilePriv();
		      	getch();
		      	system("cls");
		        break;
		     case 3:
		     	retValEnc = readFileCertainKey();
//		     	getch();
		     	msg = choosePlainTextFile();
		     	fflush(stdin);
		     	encrypted = encryption(msg,retValEnc);
		     	fflush(stdin);
		     	writeEncryptedToFile(encrypted);
		     	getch();
		      	system("cls");
		     	break;
		     case 4:
		     	retValDec = readPrivateFileCertainKey();
//		     	getch();
		     	encmsg = chooseEncryptedTextFile();
//		     	fflush(stdin);
		     	printf("\n");
    			decrypted = decryption(encmsg, retValDec);
    			printKey(decrypted);
		     	getch();
		      	system("cls");
		     	break;
		     case 5: 
			 	printf("Goodbye!\n"); 
		        break;
		     default: 
			 	printf("Wrong Choice. Enter again\n");
			 	getch();
		      	system("cls");
		        break;
		 } 
		} while (choice != 5);
	//make a plaintext file
//	first=getNumber();
//	second=getNumberAgain(first);
//	printf("First Number is: %d\n", first);
//	printf("Second Number is: %d\n", second);
	
	//generate keys
//	startProg(first, second);
//	writePublicKeyFile();
//	writePrivateKeyFile();
//	readFile();
//    readFilePriv();
    
//	printf("\nCTR IS: %d",ctr);
//    retValEnc = readFileCertainKey();
    
 //   printf("\nFor Shifting:%d\n", retValEnc);

    //reading plaintext from file
//    msg = choosePlainTextFile();
    //encryption
    encrypted = encryption(msg,retValEnc);
 //   printf("\nencrypted is:\n");
 //   printKey(encrypted);
    writeEncryptedToFile(encrypted);
    
    
//    printf("\nInput filename for encrypted text you want to decrypt:\n");
//    gets(encryptedFileName);
//    readEncryptedToFile(encryptedFileName);
    
    //decryption
//    retValDec = readPrivateFileCertainKey();
  //  printf("\nFor Shifting Back:%d\n", retValDec);
    
//    encmsg = chooseEncryptedTextFile();
   // printKey(encmsg);
//    printf("\n");
//    decrypted = decryption(encmsg, retValDec);
//    printKey(decrypted);
    return 0; 
}

char* choosePlainTextFile(){
	char plaintextName[50];
	char* msg = malloc (sizeof (char) * TEXT_SIZE);
	printf("\nInput filename for the plaintext you want to encrypt:\n");
	fflush(stdin);
    gets(plaintextName);
    msg=readPlainText(plaintextName);
    printf("\nplaintext is:\n");
    printKey(msg);
	return msg;
}

char* chooseEncryptedTextFile(){
	char encryptedTextName[50];
	char* msg = malloc (sizeof (char) * TEXT_SIZE);
	printf("\nInput filename for the encrypted text you want to decrypt:\n");
	fflush(stdin);
    gets(encryptedTextName);
    msg=readPlainText(encryptedTextName);
//    printf("\nEncrypted is:\n");
//    printKey(msg);
	return msg;
}

char* encryption(char message[], int key){ //(x+k)mod26
	int x;
	char *enc = malloc (sizeof (char) * strlen(message));
	char *enc2 = malloc (sizeof (char) * strlen(message));
    for (x = 0; x < strlen(message); x++) {
        if (message[x] >= 'a' && message[x] <= 'z') enc[x] = 'a' + (message[x] - 'a' + key) % 26;
        else if (message[x] >= 'A' && message[x] <= 'Z') enc[x] = 'A' + (message[x] - 'A' + key) % 26;
        else enc[x]= ' ';	
    }
	enc[x]='\0';
	
	for(x = 0; enc[x]!='\0'; x++){
		enc2[x] = enc[x] ^ key;
	}
	
	enc2[x]='\0';
	printf("\nMessage successfully encrypted!\n");
    printf("\nEncrypted Message is:\n");
    printKey(enc2);
    return enc2;
}

char* decryption(char message[], int key){ //(x+k)mod26
	int x;
	char *dec = malloc (sizeof (char) * strlen(message));
	char *dec2 = malloc (sizeof (char) * strlen(message));
	
	for(x = 0; message[x]!='\0'; x++){
		dec2[x] = message[x] ^ key;
	}
	
	dec2[x]='\0';
	
	for (x = 0; dec2[x]!='\0'; x++) {
        if (dec2[x] >= 'a' && dec2[x] <= 'z') dec[x] = 'a' + (dec2[x] - 'a' - key +26) % 26; 
        	
        else if (dec2[x] >= 'A' && dec2[x] <= 'Z') dec[x] = 'A' + (dec2[x] - 'A' - key+26) % 26;
        	
        else dec[x]= ' ';
    }
	dec[x]='\0';
//    for (x = 0; x < strlen(message); x++) {
//        if (message[x] >= 'a' && message[x] <= 'z') dec[x] = 'a' + (message[x] - 'a' - key +26) % 26; 
//        	
//        else if (message[x] >= 'A' && message[x] <= 'Z') dec[x] = 'A' + (message[x] - 'A' - key+26) % 26;
//        	
//        else dec[x]= ' ';
//    }
//	dec[x]='\0';
	printf("\nMessage successfully decrypted!\n");
    return dec;
}


void writePlainText(char filename[], char message[]){
	
	FILE *fp;    
  
	fp=fopen(filename,"w");  
	fputs(message,fp);  
  
	fclose(fp); 
}
char* readPlainText(char filename[]){
	int x;
	char* buff = malloc (sizeof (char) * TEXT_SIZE);
    FILE *f = fopen(filename, "r");
    fgets(buff, TEXT_SIZE, f);

    fclose(f);
    return buff;
}
void writeEncryptedToFile(char encrypted[]){
	FILE * fptr;

    fptr = fopen("encrypted.txt", "w");
    fwrite(encrypted, sizeof(char), strlen(encrypted), fptr);
    fclose(fptr);
    printf("\nYour file has been written to encrypted.txt\n");
}

void readEncryptedToFile(char filename[]){
    FILE *fptr;
	char buffer[256];
    if ((fptr = fopen(filename,"r")) == NULL){
       printf("Error! opening file");
       exit(1);
    }
	printf("\n");

	do
    {
      
        char c = fgetc(fptr);
 
   
        if (feof(fptr))
            break ;
 
        printf("%c", c);
    }  while(1);
 
    fclose(fptr);
}


void writePublicKeyFile(){
	FILE * fptr;

    fptr = fopen("publickey.txt", "w");
    fwrite(encryptedKey, sizeof(int), ctr, fptr);
    fclose(fptr);
    
    FILE * fptr2;
    fptr2 = fopen("publickey.txt", "a");
    fwrite(decryptedKey, sizeof(int), ctr, fptr);
    fclose(fptr2);
}
void writePrivateKeyFile(){
	FILE * fptr;

    fptr = fopen("privatekey.txt", "w");
    fwrite(decryptedKey, sizeof(int), ctr, fptr);
    fclose(fptr);
    
    FILE * fptr2;
    fptr2 = fopen("privatekey.txt", "a");
    fwrite(encryptedKey, sizeof(int), ctr, fptr2);
    fclose(fptr2);
}

int readFileCertainKey(){
	int num;
    FILE *fptr;
	int buffer[256];
    if ((fptr = fopen("publickey.txt","r")) == NULL){
       printf("Error! opening file");
       exit(1);
    }
	printf("\n");
	fread(buffer,  sizeof(int), ctr*2, fptr);
   //	printNumbers(buffer,ctr);
   	num = buffer[ctr];
   	fclose(fptr); 
   	
   	return num;
}

int readPrivateFileCertainKey(){
	int num;
    FILE *fptr;
	int buffer[256];
    if ((fptr = fopen("privatekey.txt","r")) == NULL){
       printf("Error! opening file");
       exit(1);
    }
	printf("\n");
	fread(buffer,  sizeof(int), ctr*2, fptr);
   //	printNumbers(buffer,ctr);
   	num = buffer[0];
   	fclose(fptr); 
   	
   	return num;
}
void readFile(){
	int num;
    FILE *fptr;
	int buffer[1024];
    if ((fptr = fopen("publickey.txt","r")) == NULL){
       printf("Error! opening file public key");
       exit(1);
    }
	printf("\n");
	fread(buffer,  sizeof(int), ctr*2, fptr);
   	printNumbers(buffer,ctr);
   	fclose(fptr); 
}
void readFilePriv(){
	int num;
    FILE *fptr;
	int buffer[1024];
    if ((fptr = fopen("privatekey.txt","r")) == NULL){
       printf("Error! opening file private key");
       exit(1);
    }
	printf("\n");
	fread(buffer,  sizeof(int), ctr*2, fptr);
   	printNumbers(buffer,ctr);
   	fclose(fptr); 
}



void printKey(char arr[]){
	int x;
	for(x=0;arr[x]!='\0';x++){
		printf("%c", arr[x]);
	}
}

void printNumbers(int arr[], int size){
	int x;
	for(x=0;x<size*2;x++){
		printf("%d ", arr[x]);
	}
}

void getKeys(char msg[], int p, int q, int tot) {
 
	int x;
 	int flg,flg2=0;
	for (x=2;x<tot;x++) {
		if(tot%x!=0){
			flg=checkPrime(x);
			if(flg == 1 && x != p && x != q && flg2!=1) {
				encryptedKey[ctr]=x;
				
				flg=doMod(encryptedKey[ctr], tot);

				if(flg>0) {
					decryptedKey[ctr]=flg;
				//	printf("enc%lld ", encryptedKey[ctr]);
				//	printf("dec%lld ", decryptedKey[ctr]);
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

int getNumber(){
	int retVal;
	srand ( time(NULL) );
    int arrSetOne[] = {2,3,5};
    int randomIndex = rand() % 3;
    retVal = arrSetOne[randomIndex];
 //   printf("First Number is: %d\n", randomValue);
    return retVal;
}

int getNumberAgain(int first){
	int retVal;
//	srand ( time(NULL) );
//    int arrSetTwo[] = {2,3,5,7,11};
//    int randomIndex = rand() % 5;
//    retVal = arrSetTwo[randomIndex];
  //  printf("Second Number is: %d\n", randomValue);
  	printf("Loading . . .\n");
  //	do{
  		
  	   	srand ( time(NULL) );
       	int arrSetTwo[] = {7,11,13};
       	int randomIndex = rand() % 3;
       	retVal = arrSetTwo[randomIndex];
//	}while(first >= retVal);
  //	printf("Keys produced! \n");
    return retVal;
}

void createPlainTextFile(){
	char msg[256], fileName[50]; 
	printf("\nInput filename for plaintext. (Format: name.txt)\n");
	fflush(stdin);
 	gets(fileName); 

	printf("\nInput message to be encrypted\n");
	fflush(stdin);
 	gets(msg); 
 	writePlainText(fileName, msg);
}
void startProg(){
	int p, q;
	long int n,tot;
	int flag,x;
	char pltxtName[50];
 	printf("Input plain text file name you will use.\n");
 	fflush(stdin);
	gets(pltxtName);
 	char *msgStore = readPlainText(pltxtName);
 	//long int* retTemp;
	p=getNumber();
	q=getNumberAgain(p);	
	n=p*q;
	tot=getTot(p,q);
 
	getKeys(msgStore, p, q, tot);

//	getch();
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

