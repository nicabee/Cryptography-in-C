/* Atbash by Barrientos, Monica */
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void doAtbash (char plaintxt);

int main () {
    int x,i;
    char choice;
    char message[50];
	printf("Input plaintext:\n");
	scanf("%[^\n]%*c", message);
	for(i=0;i<strlen(message);i++){
		doAtbash(message[i]);
	}
    return 0;
}

void doAtbash (char plaintxt) {
    int ans;
    if (plaintxt >= 65 && plaintxt <= 90) ans = 90 - (plaintxt - 65); /* 65-90 Capital A-Z */
	else if (plaintxt >= 97 && plaintxt <= 122) ans = 122 - (plaintxt - 97); /* 97-122 Lowercase a-z */
    else {
    	printf("\n");
       	return;
    }
   printf("%c", ans);

}
