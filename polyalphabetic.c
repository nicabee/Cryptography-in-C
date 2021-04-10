/* Polyalphabetic Cipher by Barrientos, Monica */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* storeKeyVal(char message[], char secretkey[]);
char* encryption();
char* decryption();


int main()
{
      int choice;
      char* encrypted;
	  char* decrypted;
		do 
		{
		 printf("\nWelcome to Polyalphabetic Encryption and Decryption\n");
		 printf("\nMenu\n");
		 printf("1. Encrypt\n");
		 printf("2. Decrypt\n");
		 printf("3. Exit\n");
		 scanf("%d",&choice);
		  
		 switch (choice)
		 {
		     case 1: 
		      	encrypted = encryption();
		      	printf("\nEncrypted Text : %s", encrypted);
		      	getch();
		      	system("cls");
		        break;
		     case 2: 
		      	decrypted = decryption();
		      	printf("\nDecrypted Text : %s", decrypted);
		      	getch();
		      	system("cls");
		        break;
		     case 3: 
			 	printf("Goodbye!\n"); 
		        break;
		     default: 
			 	printf("Wrong Choice. Enter again\n");
		        break;
		 } 
		} while (choice != 3);
	return 0;
}

char* storeKeyVal(char message[], char secretkey[]){
	char *k = malloc (sizeof (char) * 50);
	int x,y=0;
	for(x=0;x<strlen(message);x++){
    	if(y==strlen(secretkey)) y=0;
        k[x]=secretkey[y];
        y++;
    } 
    return k;
}

char* encryption(){
	int x;
	char *enc = malloc (sizeof (char) * 50);
	char message[50], secretkey[50];
	
	printf("Enter Message to Encrypt: ");
	fflush(stdin);
	gets(message);
	strupr(message);
	
	printf("Enter Key : ");
	fflush(stdin);
	gets(secretkey);
	strupr(secretkey);
	
	char* key = storeKeyVal(message, secretkey);
    for(x=0;x<strlen(message);x++){ 
    	enc[x]=((message[x] + key[x]) % 26) + 'A';
    }
      	enc[x]='\0'; 
    return enc;
}

char* decryption(){
	int x;
	char *dec = malloc (sizeof (char) * 50);
	char message[50], secretkey[50];
	
	printf("Enter Message to Decrypt: ");
	fflush(stdin);
	gets(message);
	strupr(message);
	
	printf("Enter Key : ");
	fflush(stdin);
	gets(secretkey);
	strupr(secretkey);
	char* key = storeKeyVal(message, secretkey);
    for(x=0;x<strlen(message);x++){
        dec[x]=(((message[x] - key[x]) + 26) % 26) + 'A';
    }
      	dec[x]='\0';
    return dec;
}

