/* Simulating Digital Certificates by Barrientos, Monica B.*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>

#define TEXT_SIZE 1024

long int encryptedKey[100],decryptedKey[100],uniValue;
int* md5value;
int* md5valueEnc;
int* md5valueDec;
int ctr=0;

typedef union uwb {
	unsigned w;
	unsigned char b[4];
} MD5union;
/* MD5 Functions */
int* GetMD5String(const char *msg, int mlen);
unsigned* Algorithms_Hash_MD5(const char *msg, int mlen);
unsigned rol(unsigned r, short N);
unsigned *calctable(unsigned *k);
unsigned func3(unsigned abcd[]);
unsigned func2(unsigned abcd[]);
unsigned func1(unsigned abcd[]);
unsigned func0(unsigned abcd[]);
void createAnMD5();
char compareArray(int a[],int b[],int size);

/* Printing functions */
void printNumbers(int arr[], int size);
void printKey(char arr[]);
void printMD5(int arr[], int size);

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
char* choosePlainTextFile(char filename[]);
char* encryption(char message[], int key);
void writeEncryptedToFile(char encrypted[]);
void readEncryptedToFile(char filename[]);

/* Decryption Process*/
void endProg();
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
		 printf("2. Create an MD5 Value for your plaintext. \n");
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
		     	createAnMD5();
		     	printMD5(md5value,4);
		     	getch();
		      	system("cls");
		     	break;
		     case 3: 
				startProg();
		      	getch();
		      	system("cls");
		        break;
		     case 4:
		     	endProg();
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

    return 0; 
}

char* choosePlainTextFile(char filename[]){
	char plaintextName[50];
	char* msg = malloc (sizeof (char) * TEXT_SIZE);
    msg=readPlainText(filename);
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

	return msg;
}

char* encryption(char message[], int key){ 
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
void createAnMD5(){
	char filename[50];
	char* msg;
	printf("Input the name of the message file to generate an MD5 checksum.\n");
	fflush(stdin);
	gets(filename);
	msg=readPlainText(filename);
	md5value = GetMD5String(msg, 40);
	
}
char* decryption(char message[], int key){ 
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
   //	printNumbers(buffer,ctr);
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
  // 	printNumbers(buffer,ctr);
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
void printMD5(int arr[], int size){
	int x;
	for(x=0;x<size;x++){
		printf("%x",arr[x]);
	}
}
void getKeys(char msg[], int p, int q, int tot) {
 	printf("\nProducing your keys . . . \n");
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
    return retVal;
}

int getNumberAgain(int first){
	int retVal;
  	printf("Loading . . .\n");
  	srand ( time(NULL) );
    int arrSetTwo[] = {7,11,13};
    int randomIndex = rand() % 3;
    retVal = arrSetTwo[randomIndex];
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
char compareArray(int a[],int b[],int size)	{
	int i;
	for(i=0;i<size;i++){
		if(a[i]!=b[i])
			return 1;
	}
	return 0;
}
void startProg(){
	int p, q;
	long int n,tot;
	int flag,x;
	int y, retValEnc;
	char pltxtName[50];
	char *msg;
	char* encrypted;
 	printf("Input plain text file name you will use.\n");
 	fflush(stdin);
	gets(pltxtName);
	
 	char *msgStore = readPlainText(pltxtName);
 /*	for(y=0;y<4;y++){
		printf("%d",md5value[y]);
	}*/
 	md5valueEnc = GetMD5String(msgStore, 40);
 	printf("\n");
/*	for(y=0;y<4;y++){
		printf("%d",md5valueEnc[y]);
	}*/
 	if(compareArray(md5value, md5valueEnc, 4)==0){
 		p=getNumber();
		q=getNumberAgain(p);	
		n=p*q;
		tot=getTot(p,q);
	 
		getKeys(msgStore, p, q, tot);
		
		writePublicKeyFile();
		writePrivateKeyFile();
		readFile();
		readFilePriv();
		
		retValEnc = readFileCertainKey();
		msg = choosePlainTextFile(pltxtName);
		encrypted = encryption(msg,retValEnc);
		writeEncryptedToFile(encrypted);
 	}else{
 		printf("\nPlain text file has been tampered! Can't proceed with encryption!\n");
	} 
}
void endProg(){
	
	char pltxtName[50];
	int retValDec;
	char* encmsg;
	char* decrypted;
	
	printf("Input file name for data integrity checking.\n");
 	fflush(stdin);
	gets(pltxtName);
	int y;
	char *msgStore = readPlainText(pltxtName);
/*	for(y=0;y<4;y++){
		printf("%d",md5value[y]);
	} */
 	md5valueDec = GetMD5String(msgStore, 40);
 	printf("\n");
/*	for(y=0;y<4;y++){
		printf("%d",md5valueDec[y]);
	} */
	
	if(compareArray(md5value, md5valueDec, 4)==0){
	 	retValDec = readPrivateFileCertainKey();
		encmsg = chooseEncryptedTextFile();
		printf("\n");
	    decrypted = decryption(encmsg, retValDec);
	    printKey(decrypted);
 	}else{
 		printf("\nPlain text file has been tampered! Can't proceed with decryption!\n");
	} 
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



typedef unsigned DigestArray[4];

unsigned func0(unsigned abcd[]) {
	return (abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
}

unsigned func1(unsigned abcd[]) {
	return (abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
}

unsigned func2(unsigned abcd[]) {
	return  abcd[1] ^ abcd[2] ^ abcd[3];
}

unsigned func3(unsigned abcd[]) {
	return abcd[2] ^ (abcd[1] | ~abcd[3]);
}

typedef unsigned(*DgstFctn)(unsigned a[]);

unsigned *calctable(unsigned *k)
{
	double s, pwr;
	int i;

	pwr = pow(2.0, 32);
	for (i = 0; i<64; i++) {
		s = fabs(sin(1.0 + i));
		k[i] = (unsigned)(s * pwr);
	}
	return k;
}

unsigned rol(unsigned r, short N)
{
	unsigned  mask1 = (1 << N) - 1;
	return ((r >> (32 - N)) & mask1) | ((r << N) & ~mask1);
}

unsigned* Algorithms_Hash_MD5(const char *msg, int mlen)
{
	static DigestArray h0 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
	static DgstFctn ff[] = { &func0, &func1, &func2, &func3 };
	static short M[] = { 1, 5, 3, 7 };
	static short O[] = { 0, 1, 5, 0 };
	static short rot0[] = { 7, 12, 17, 22 };
	static short rot1[] = { 5, 9, 14, 20 };
	static short rot2[] = { 4, 11, 16, 23 };
	static short rot3[] = { 6, 10, 15, 21 };
	static short *rots[] = { rot0, rot1, rot2, rot3 };
	static unsigned kspace[64];
	static unsigned *k;

	static DigestArray h;
	DigestArray abcd;
	DgstFctn fctn;
	short m, o, g;
	unsigned f;
	short *rotn;
	union {
		unsigned w[16];
		char     b[64];
	}mm;
	int os = 0;
	int grp, grps, q, p;
	unsigned char *msg2;

	if (k == NULL) k = calctable(kspace);

	for (q = 0; q<4; q++) h[q] = h0[q];

	{
		grps = 1 + (mlen + 8) / 64;
		msg2 = (unsigned char*)malloc(64 * grps);
		memcpy(msg2, msg, mlen);
		msg2[mlen] = (unsigned char)0x80;
		q = mlen + 1;
		while (q < 64 * grps) { msg2[q] = 0; q++; }
		{
			MD5union u;
			u.w = 8 * mlen;
			q -= 8;
			memcpy(msg2 + q, &u.w, 4);
		}
	}

	for (grp = 0; grp<grps; grp++)
	{
		memcpy(mm.b, msg2 + os, 64);
		for (q = 0; q<4; q++) abcd[q] = h[q];
		for (p = 0; p<4; p++) {
			fctn = ff[p];
			rotn = rots[p];
			m = M[p]; o = O[p];
			for (q = 0; q<16; q++) {
				g = (m*q + o) % 16;
				f = abcd[1] + rol(abcd[0] + fctn(abcd) + k[q + 16 * p] + mm.w[g], rotn[q % 4]);

				abcd[0] = abcd[3];
				abcd[3] = abcd[2];
				abcd[2] = abcd[1];
				abcd[1] = f;
			}
		}
		for (p = 0; p<4; p++)
			h[p] += abcd[p];
		os += 64;
	}
	return h;
}

int* GetMD5String(const char *msg, int mlen) {
	char* str = malloc (sizeof (char) * 33);;
	strcpy(str, "");
	int j, k;
	unsigned *d = Algorithms_Hash_MD5(msg, strlen(msg));
	MD5union u;
	int* emd = malloc(sizeof(int)*4);
	for (j = 0; j<4; j++) {
		u.w = d[j];
		emd[j] = u.w;
	}
	return emd;
}
