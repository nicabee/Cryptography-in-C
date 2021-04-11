/* Tranpositional cipher by Barrientos, Monica */
#define MAXROWS 255
#define MAXCOLS 255
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void encrypt();
void decrypt();
void cipher(int i, int c, char arr[MAXROWS][MAXCOLS]);
int arrangeKey(char temp[]);
char* ret2dArray(int rows, int cols, char decrypted2d[MAXROWS][MAXCOLS]);
void printMessage(char msg[]);
void display2dArrayForm(int rows, int cols, char arr[MAXROWS][MAXCOLS]);

int main()
{
	int choice;
		do 
		{
		 printf("\nWelcome to Transpositional Encryption and Decryption\n");
		 printf("\nMenu\n");
		 printf("1. Encrypt\n");
		 printf("2. Decrypt\n");
		 printf("3. Exit\n");
		 scanf("%d",&choice);
		  
		 switch (choice)
		 {
		     case 1: 
		      	encrypt();
		      	getch();
		      	system("cls");
		        break;
		     case 2: 
		      	decrypt();
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

void encrypt(){
	char key[100];
	char message[256];
	char temp[100];
	int x, y, j, m, flag, rows, cols, index;
	char encryptedArray[MAXROWS][MAXCOLS];
	char encrypted[256];

	printf("Enter the key\n");
    fflush(stdin);
    gets(key);
 	
    printf("\nInput message you want to encrypt:\n");
    fflush(stdin);
    gets(message);
    
    strcpy(temp, key);

    j = 0;
    flag=0;
    for (x = 0; flag != 1; x++){
		if(flag != 1){
		 	for (y = 0; y<strlen(key); y++){
		    	if (message[j] == '\0'){
		            flag = 1;
		            encryptedArray[x][y] = '_';
		        }else{
		        	encryptedArray[x][y] = message[j++];
		    	}
		    }
	 	}
    }
  	rows = x;
 	cols = y;

    display2dArrayForm(x,y, encryptedArray);
    
    static int n=0;
    for (x = 0; x < strlen(key); x++)
    {
        index = arrangeKey(temp);
	    for (m = 0; m < rows; m++)
	    {
	        encrypted[n++] = encryptedArray[m][index];
	    }
	}
	n=0;
	
    printf("\nEncryption successful. This is your encrypted message:\n");
	printMessage(encrypted);
	
	memset(encrypted, 0, strlen(encrypted));
}


void decrypt(){
	char key[100];
	char decrypted[256];
	char temp[100];
	char temp2[100];
	int x, y, j, i, flag,rows,cols,index, encryptedRows;
	char store2d[MAXROWS][MAXCOLS];
	char decryptedArray[MAXROWS][MAXCOLS];
	char* decrpytedMsg;
	
	printf("Enter the key\n");
    fflush(stdin);
    gets(key);
 	
    printf("\nInput message you want to decrypt:\n");
    fflush(stdin);
    gets(decrypted);

    j = 0;
    flag=0;
    for (x = 0; flag != 1; x++)
    {
		if(flag != 1){
		 	for (y = 0; y<strlen(key); y++){
		    	if (decrypted[j] == '\0' ){
		            flag = 1;
		            store2d[x][y] = '_';
		        }else{
		        	store2d[x][y] = decrypted[j++];
		    	}
		    }
	 	}
    }
    
  	rows = x;
 	cols = y;
 	encryptedRows = strlen(decrypted) / strlen(key);
	strcpy(temp, key);
	
    for (x = 0, j = 1, y=0;x < strlen(decrypted); x++, j++)
    {
        temp2[y++] = decrypted[x]; //temp2[1] = o

        if ((j % encryptedRows) == 0) // 0%2 = 0
        {
            temp2[y] = '\0';
            index = arrangeKey(temp); // key -- e < k so, 1
            for (i = 0; i < encryptedRows; i++)
		    {
		    
		        decryptedArray[i][index] = temp2[i]; //darr[0][1] = 
		    }
            y = 0;
        }
    }
    printf("\nArray Retrieved is\n");
 	decrpytedMsg = ret2dArray(rows,cols, decryptedArray);
 	printf("\nDecryption successful. This is your decrypted message:\n");
 	printMessage(decrpytedMsg);
}

void printMessage(char msg[]){
	int x;
	for (x = 0; msg[x] != '\0'; x++){
		printf("%c", msg[x]);
	}
}

char* ret2dArray(int rows, int cols, char decrypted2d[MAXROWS][MAXCOLS]){
	int x,y,k = 0;
	char *ret2d = malloc (sizeof (char) * 256);
    for (x = 0; x < rows; x++)
    {
        for (y = 0; y < cols; y++)
        {
            printf("%c ", decrypted2d[x][y]);
            ret2d[k++] = decrypted2d[x][y];
 
        }
        printf("\n");
    }
    ret2d[k] = '\0';
    return ret2d;
    
}

void display2dArrayForm(int rows, int cols,char arr [MAXROWS][MAXCOLS]){
	int x,y;

	for (x = 0; x < rows; x++)
    {
        for (y = 0; y < cols; y++)
        {
            printf("%c ", arr[x][y]);
        }
        printf("\n");
    }
}

 
int arrangeKey(char temp[])
{
    int x, min, ndx;
 
    min = temp[0]; //min = k
    ndx = 0; 
    for (x = 0; temp[x] != '\0'; x++)
    {
        if (temp[x] < min) 
        {
            min = temp[x]; 
            ndx = x; 
        }
    }
    temp[ndx] = '~'; //modify the character at the least index to be ~ para if statement wont execute (no switching)
    return ndx;
}
