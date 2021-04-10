/* Shift Cipher by Barrientos, Monica */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
char* encryption();
char* decryption();

int main()
{
      int choice;
      char* encrypted;
	  char* decrypted;
		do 
		{
		 printf("\nWelcome to Monoalphabetic Encryption and Decryption\n");
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
			 	getch();
		      	system("cls");
		        break;
		 } 
		} while (choice != 3);
	return 0;
}
char* encryption(){ //(x+k)mod26
	int x, key;
	char message[256];
	char *enc = malloc (sizeof (char) * 256);
	
	printf("Enter Message to Encrypt: ");
	fflush(stdin);
	scanf ("%[^\n]%*c", message);
	
	printf("Enter Key : ");
	scanf("%d", &key);
      	
    for (x = 0; x < strlen(message); x++) {
	
        if (message[x] >= 'a' && message[x] <= 'z') enc[x] = 'a' + (message[x] - 'a' + key) % 26;
        
        else if (message[x] >= 'A' && message[x] <= 'Z') enc[x] = 'A' + (message[x] - 'A' + key) % 26;
        
        else enc[x]= ' ';	
    }
    
	enc[x]='\0';
	
    return enc;
}

char* decryption(){ //(x-k)mod26
	int x, key;
	char message[256];
	char *dec = malloc (sizeof (char) * 256);
	printf("Enter Message to Decrypt: ");
	fflush(stdin);
	scanf ("%[^\n]%*c", message);

	printf("Enter Key : ");
	scanf("%d", &key);
    for (x = 0; x < strlen(message); x++) {
        if (message[x] >= 'a' && message[x] <= 'z') dec[x] = 'a' + (message[x] - 'a' - key +26) % 26; 
        	
        else if (message[x] >= 'A' && message[x] <= 'Z') dec[x] = 'A' + (message[x] - 'A' - key+26) % 26;
        	
        else dec[x]= ' ';
    }
    
   	dec[x]='\0';
   		
    return dec;
}


